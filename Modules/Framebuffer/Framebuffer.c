#include <Framebuffer.h>
#include <Boot/PreBoot.h>
#include <String.h>

static FRAMEBUFFER_DEVICE FramebufferDevice;
static SYSTEM_NODE* FramebufferNode = NULL;

const ERROR_KEYS* FramebufferContext;

static const char* Framebuffer_TraceMapper(int ID)
{
    static const char* TraceTable[] =
    {
        "Modules/Framebuffer/*->Framebuffer_PutPixel",
        "Modules/Framebuffer/*->Framebuffer_Write",
        "Modules/Framebuffer/*->Framebuffer_Read",
        "Modules/Framebuffer/*->Framebuffer_GetAttribute",
        "Modules/Framebuffer/*->Framebuffer_Initialize",
    };

    if (ID < 0 || ID >= Max_Framebuffer_Traces)
    {
        return "Unknown";
    }

    return TraceTable[ID];
}

static inline void Framebuffer_PutPixel(uint32_t XCoordinate, uint32_t YCoordinate, uint32_t Color, SYSTEM_ERROR* Error)
{
    #define ErrorOut_Framebuffer_PutPixel(Code) \
        ErrorOut(Error, FramebufferContext, Code, FUNC_Framebuffer_PutPixel)

    if (XCoordinate >= FramebufferDevice.Width || YCoordinate >= FramebufferDevice.Height)
    {
        ErrorOut_Framebuffer_PutPixel(-EINVAL);
        return;
    }

    uint8_t* Base = (uint8_t*)FramebufferDevice.Address;
    uint64_t Offset = YCoordinate * FramebufferDevice.Pitch + XCoordinate * (FramebufferDevice.Bpp / 8);
    *(uint32_t*)(Base + Offset) = Color;
}

int Framebuffer_Open(SYSTEM_NODE* Node __unused, SYSTEM_FILE* File __unused, SYSTEM_ERROR* Error __unused)
{
    return GeneralOK;
}

int Framebuffer_Close(SYSTEM_FILE* File __unused, SYSTEM_ERROR* Error __unused)
{
    return GeneralOK;
}

static long Framebuffer_Write(SYSTEM_FILE* File, const void* Buffer, uint64_t Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_Framebuffer_Write(Code) \
        ErrorOut(Error, FramebufferContext, Code, FUNC_Framebuffer_Write)

    if (Probe4Error(Buffer) || !Buffer)
    {
        ErrorOut_Framebuffer_Write(-EINVAL);
        return Error->ErrorCode;
    }

    if (File->Offset >= FramebufferDevice.Size)
    {
        return 0;/*Wrote nothing*/
    }

    uint64_t Remaining = FramebufferDevice.Size - File->Offset;
    if (Length > Remaining)
    {
        Length = Remaining;
    }

    memcpy((uint8_t*)FramebufferDevice.Address + File->Offset, Buffer, Length);

    File->Offset += Length;
    return (long)Length;
}

static long Framebuffer_Read(SYSTEM_FILE* File, void* Buffer, uint64_t Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_Framebuffer_Read(Code) \
        ErrorOut(Error, FramebufferContext, Code, FUNC_Framebuffer_Read)

    if (Probe4Error(Buffer) || !Buffer)
    {
        ErrorOut_Framebuffer_Read(-EINVAL);
        return Error->ErrorCode;
    }

    if (File->Offset >= FramebufferDevice.Size)
    {
        return 0;/*Read nothing*/
    }

    uint64_t Remaining = FramebufferDevice.Size - File->Offset;
    if (Length > Remaining)
    {
        Length = Remaining;
    }

    memcpy(Buffer, (uint8_t*)FramebufferDevice.Address + File->Offset, Length);

    File->Offset += Length;
    return (long)Length;
}

static int Framebuffer_GetAttribute(SYSTEM_NODE* Node, VFS_STAT* Stat, SYSTEM_ERROR* Error)
{
    #define ErrorOut_Framebuffer_GetAttribute(Code) \
        ErrorOut(Error, FramebufferContext, Code, FUNC_Framebuffer_GetAttribute)

    if (Probe4Error(Stat) || !Stat)
    {
        ErrorOut_Framebuffer_GetAttribute(-EINVAL);
        return Error->ErrorCode;
    }

    memset(Stat, 0, sizeof(VFS_STAT));
    Stat->Type = VFSNode_DEVICE;
    Stat->Size = FramebufferDevice.Size;
    Stat->BlockSize = FramebufferDevice.Pitch;
    return GeneralOK;
}

static SYSTEM_OPERATIONS Framebuffer_Operations =
{
    .Open    = Framebuffer_Open,
    .Close   = Framebuffer_Close,
    .Read    = Framebuffer_Read,
    .Write   = Framebuffer_Write,
    .Ioctl   = NULL,
    .Getattr = Framebuffer_GetAttribute,
    .Setattr = NULL
};

int Framebuffer_Initialize(SYSTEM_ERROR* Error)
{
    #define ErrorOut_Framebuffer_Initialize(Code) \
        ErrorOut(Error, FramebufferContext, Code, FUNC_Framebuffer_Initialize)

    FramebufferContext = RegisterErrorKeys("Framebuffer", Framebuffer_TraceMapper, Max_Framebuffer_Traces, Error);

    BOOT_REQUEST RequestFramebuffer = RequestBootService(RequestFRAMEBUFFER, Error);

    if (Probe4Error(RequestFramebuffer.Pointer) || !RequestFramebuffer.Pointer)
    {
        ErrorOut_Framebuffer_Initialize(-ENODEV);
        return Error->ErrorCode;
    }
    
    struct limine_framebuffer_request* Request = (struct limine_framebuffer_request*)RequestFramebuffer.Pointer;

    if (!Request->response || Request->response->framebuffer_count == 0)
    {
        ErrorOut_Framebuffer_Initialize(-ENODEV);
        return Error->ErrorCode;
    }

    struct limine_framebuffer* Framebuffer = Request->response->framebuffers[0];

    if (!Framebuffer || !Framebuffer->address)
    {
        ErrorOut_Framebuffer_Initialize(-EFAULT);
        return Error->ErrorCode;
    }

    FramebufferDevice.Address = Framebuffer->address;
    FramebufferDevice.Width   = Framebuffer->width;
    FramebufferDevice.Height  = Framebuffer->height;
    FramebufferDevice.Pitch   = Framebuffer->pitch;
    FramebufferDevice.Bpp     = Framebuffer->bpp;
    FramebufferDevice.Size    = Framebuffer->pitch * Framebuffer->height;

    FramebufferNode = System_CreateFile("framebuffer", &Framebuffer_Operations, &FramebufferDevice, sizeof(FRAMEBUFFER_DEVICE), Error);

    if (Probe4Error(FramebufferNode) || !FramebufferNode)
    {
        ErrorOut_Framebuffer_Initialize(Error->ErrorCode);
        return Error->ErrorCode;
    }

    SYSTEM_NODE* Root = System_GetRoot(Error);
    if (Probe4Error(Root) || !Root)
    {
        ErrorOut_Framebuffer_Initialize(Error->ErrorCode);
        return Error->ErrorCode;
    }

    if (System_AttachNode(Root, FramebufferNode, Error) < 0)
    {
        ErrorOut_Framebuffer_Initialize(Error->ErrorCode);
        return Error->ErrorCode;
    }

    return GeneralOK;
}

int _start(void) /*STANDARD NAME "_start"*/
{
    SYSTEM_ERROR Err;
    SYSTEM_ERROR* Error = &Err;
    return Framebuffer_Initialize(Error);
}

int _exit(void) /*STANDARD NAME "_exit"*/
{
    return GeneralOK;
}