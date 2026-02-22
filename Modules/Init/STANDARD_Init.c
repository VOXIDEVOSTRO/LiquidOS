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
	M_PInfo("Kickstarting Early Framebuffer...\n");
	KickStartModule("Framebuffer.ko", Error);
	M_PSuccess("Early Framebuffer OK\n");

    #ifdef LOCALTests
        FILE* FramebufferFile = VFS_Open("/framebuffer", VFS_OpenFlag_WRITEONLY, Error);

        FRAMEBUFFER_DEVICE FramebufferInformation;

        VFS_IOControl(FramebufferFile, Request_FramebufferData, &FramebufferInformation, Error);

        uint32_t /*DEFAULT RGB*/ Color = 0xFF0000; /*Red*/
        long Size = FramebufferInformation.Size;

        for (long Iteration = 0; Iteration < Size; Iteration += sizeof(uint32_t))
        {
            VFS_Write(FramebufferFile, &Color, sizeof(Color), Error);
        }

        VFS_Close(FramebufferFile, Error);
    #endif

    return GeneralOK;
}

int _exit(void) /*STANDARD NAME "_exit"*/
{
    return GeneralOK;
}