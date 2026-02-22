/*CONFIG*/
#include <__KCONF.h> /*Global Config, Modularus local*/
#include <__LCONF.h> /*Local Config*/

/*CORE INCLUDES*/
#include <VirtualFileSystem.h>
#include <Errors.h>

/*LOCAL INCLUDES*/
#include <Modules.h>
#include <Init.h>
#include <Framebuffer.h>
#include <Logging.h>

/*LIB INCLUDES*/
#include <Externals/Formatter.h>
#include <Externals/Emmiter.h>
#include <Externals/Console.h>

/*THIS IS A MODULARUS CORE STANDARD FILE WITH A STANDARD NAME OF "STANDARD_Init"
  The job of this file is to handle ITS own modules and init sequence.*/

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;

const ERROR_KEYS* InitContext;

static const char* Init_TraceMapper(int ID)
{
    static const char* TraceTable[] =
    {
        "Modules/Init/Modules.c->KickStartModule",
    };

    if (ID < 0 || ID >= Max_Init_Traces)
    {
        return "Unknown";
    }

    return TraceTable[ID];
}

int _start(void) /*STANDARD NAME "_start"*/
{
	InitContext = RegisterErrorKeys("STANDARD_Init", Init_TraceMapper, Max_Init_Traces, Error);
	Emitter_KickStart(Error);

	/*Kickstart Framebuffer*/
	KickStartModule("Framebuffer.ko", Error);

    /*Kickstart Console*/
    FILE* FramebufferFile = VFS_Open("/framebuffer", VFS_OpenFlag_WRITEONLY, Error);
    FRAMEBUFFER_DEVICE FramebufferInformation;
    VFS_IOControl(FramebufferFile, Request_FramebufferData, &FramebufferInformation, Error);
    VFS_Close(FramebufferFile, Error);
	KickStartConsole((uint32_t*)FramebufferInformation.Address, (uint32_t)FramebufferInformation.Width, (uint32_t)FramebufferInformation.Height);
	
    /*Log test*/
    M_PInfo("This is a Information log\n");
    M_PSuccess("This is a Success log\n");
    M_PWarn("This is a Warning log\n");
    M_PError("This is a Error log\n");
    M_PDebug("This is a Debug log\n");

    return GeneralOK;
}

int _exit(void) /*STANDARD NAME "_exit"*/
{
    return GeneralOK;
}