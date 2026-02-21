/*CONFIG*/
#include <__KCONF.h>

/*CORE INCLUDES*/
#include <VirtualFileSystem.h>
#include <Errors.h>

/*LOCAL INCLUDES*/
#include <Modules.h>
#include <Init.h>

/*LIB INCLUDES*/
#include <Formatter.h>
#include <Emmiter.h>

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
	PInfo("Kickstarting Early Framebuffer...\n");
	KickStartModule("Framebuffer.ko", Error);
	PSuccess("Early Framebuffer OK\n");

    return GeneralOK;
}

int _exit(void) /*STANDARD NAME "_exit"*/
{
    return GeneralOK;
}