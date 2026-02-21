/*CONFIG*/
#include <__KCONF.h>

/*CORE INCLUDES*/
#include <VirtualFileSystem.h>
#include <Errors.h>

/*BUILTIN INCLUDES*/
#ifdef BUILTINS
    #ifdef BUILTIN_UART
        #include <BuiltIns/Device/UART.h>
    #endif

    #ifdef BUILTIN_Formatter
        #include <BuiltIns/Logger/Emitter.h>
        #include <BuiltIns/Logger/Formatter.h>
    #endif

    #ifdef BUILTIN_Linker
        #include <BuiltIns/Linker/LinkerELF.h>
    #endif

    #ifdef BUILTIN_Loader
        #include <BuiltIns/Loader/Loader.h>
    #endif
#endif

/*LOCAL INCLUDES*/
#include <Init.h>

/*Wrap up the load an link calls*/
int KickStartModule(const char *ModuleName, SYSTEM_ERROR* Error)
{
    #define ErrorOut_KickStartModule(Code) \
        ErrorOut(Error, InitContext, Code, FUNC_KickStartModule)

    if (Probe4Error(ModuleName) || !ModuleName)
    {
        ErrorOut_KickStartModule(-EINVAL);
        return Error->ErrorCode;
    }

    #ifdef BUILTIN_Loader
        FILE* LoaderFile = VFS_Open("/loader", VFS_OpenFlag_WRITEONLY, Error);
        if (Probe4Error(LoaderFile) || !LoaderFile)
        {
            ErrorOut_KickStartModule(-EBADF);
            return Error->ErrorCode;
        }

        LOADED_MODULE Module;
        LOADER_COMMAND_GET_ARGUMENTS ModuleRequest =
        {
            .Name = ModuleName,
            .Out = &Module
        };

        if (VFS_IOControl(LoaderFile, LoaderCommand_GET, &ModuleRequest, Error) != GeneralOK)
        {
            ErrorOut_KickStartModule(Error->ErrorCode);
            return Error->ErrorCode;
        }
    #endif

    #ifdef BUILTIN_Linker
        #ifdef BUILTIN_Loader
            FILE* LinkerFile = VFS_Open("/linker", VFS_OpenFlag_WRITEONLY, Error);
            if (Probe4Error(LinkerFile) || !LinkerFile)
            {
                ErrorOut_KickStartModule(-EBADF);
                return Error->ErrorCode;
            }

            if (Probe4Error(Module.Address) || !Module.Address)
            {
                ErrorOut_KickStartModule(-EFAULT);
                return Error->ErrorCode;
            }

            if (VFS_IOControl(LinkerFile, LinkerCommand_LINK, Module.Address, Error) != GeneralOK)
            {
                ErrorOut_KickStartModule(Error->ErrorCode);
                return Error->ErrorCode;
            }
        #endif
        if (VFS_IOControl(LinkerFile, LinkerCommand_RUN, NULL, Error) != GeneralOK)
        {
            ErrorOut_KickStartModule(Error->ErrorCode);
            return Error->ErrorCode; 
        }
    #endif
    return GeneralOK;
}