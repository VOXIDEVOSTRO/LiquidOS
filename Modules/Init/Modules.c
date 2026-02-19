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

/*Wrap up the load an link calls*/
int KickStartModule(const char* ModuleName, SYSTEM_ERROR* Error)
{
    #ifdef BUILTIN_Loader
        FILE* LoaderFile = VFS_Open("/loader", VFS_OpenFlag_WRITEONLY, Error);
        LOADED_MODULE Module;
        LOADER_COMMAND_GET_ARGUMENTS ModuleRequest =
        {
            .Name = ModuleName,
            .Out = &Module
        };
        VFS_IOControl(LoaderFile, LoaderCommand_GET, &ModuleRequest, Error);
    #endif

    #ifdef BUILTIN_Linker
        #ifdef BUILTIN_Loader
            FILE* LinkerFile = VFS_Open("/linker", VFS_OpenFlag_WRITEONLY, Error);
            VFS_IOControl(LinkerFile, LinkerCommand_LINK, Module.Address, Error);
        #endif
        VFS_IOControl(LinkerFile, LinkerCommand_RUN, NULL, Error);
    #endif
    return GeneralOK;
}