#pragma once

#include <__KCONF.h>
#include <Types.h>
#include <Errors.h>
#include <VirtualFileSystem.h>
#include <System.h>

typedef struct FRAMEBUFFER_DEVICE
{
    void* Address;
    uint64_t Width;
    uint64_t Height;
    uint64_t Pitch;
    uint16_t Bpp;
    uint64_t Size;
} FRAMEBUFFER_DEVICE;

extern const ERROR_KEYS* FramebufferContext;

enum
{
	FUNC_Framebuffer_PutPixel,
    FUNC_Framebuffer_Write,
    FUNC_Framebuffer_Read,
    FUNC_Framebuffer_GetAttribute,
    FUNC_Framebuffer_Initialize,

	Max_Framebuffer_Traces,
};

int Framebuffer_Initialize(SYSTEM_ERROR* Error);
