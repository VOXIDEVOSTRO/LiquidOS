#include <__KCONF.h>
#include <VirtualFileSystem.h>

#include <Externals/Console.h>

static FILE* UARTEmitterDevice;

void Emitter_KickStart(SYSTEM_ERROR* Error)
{
    UARTEmitterDevice = VFS_Open("/uart", VFS_OpenFlag_WRITEONLY, Error);
}

void PutChar(char Character)
{
    SYSTEM_ERROR Err;
    SYSTEM_ERROR* Error = &Err;

    /*Screen*/
    PutChar2Console(Character);
    
    /*UART*/
    VFS_Write(UARTEmitterDevice, &Character, 1, Error);
}

void PutString(const char* String)
{
    while (*String)
    {
        PutChar(*String);
        String++;
    }
}