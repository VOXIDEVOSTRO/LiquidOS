#pragma once

#include <Types.h>

typedef struct
{
    uint32_t* FrameBuffer;
    uint32_t  FramebufferWidth;
    uint32_t  FramebufferHeight;
    uint32_t  ConsoleColumn;
    uint32_t  ConsoleRow;
    uint32_t  CursorX;
    uint32_t  CursorY;
    uint32_t  TextColor;
    uint32_t  BackgroundColor;
} CONSOLE;

extern CONSOLE Console;

void KickStartConsole(uint32_t*, uint32_t, uint32_t);
void ClearConsole(void);
void PutChar2Console(char);
void PutPrint2Console(const char*);
void SetBackgroundColor(uint32_t, uint32_t);
void SetCursor(uint32_t, uint32_t);