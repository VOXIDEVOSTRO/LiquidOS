#include <__LCONF.h>

#include <Externals/Console.h>
#include <Externals/Fonts.h>

CONSOLE Console = {0};

void
KickStartConsole(uint32_t* Framebuffer, uint32_t ConsoleWidth, uint32_t ConsoleHeight)
{
    Console.FrameBuffer = Framebuffer;
    Console.FramebufferWidth = ConsoleWidth;
    Console.FramebufferHeight = ConsoleHeight;
    Console.ConsoleColumn = ConsoleWidth / FontW;
    Console.ConsoleRow = ConsoleHeight / FontH;
    Console.CursorX = 0;
    Console.CursorY = 0;
    Console.TextColor = 0xFFFFFF; /* White text */
    Console.BackgroundColor = 0x000000; /* Black background */
}

void
ClearConsole(void)
{
    for (uint32_t Iteration = 0; Iteration < Console.FramebufferWidth * Console.FramebufferHeight; Iteration++)
    {
        Console.FrameBuffer[Iteration] = Console.BackgroundColor;
    }

    Console.CursorX = 0;
    Console.CursorY = 0;
}

void
PutChar2Console(char Character)
{
    if (Character == '\n')
    {
        Console.CursorX = 0;
        Console.CursorY++;
    }
    else if (Character == '\r')
    {
        Console.CursorX = 0;
    }
    else
    {
        uint32_t PixelX = Console.CursorX * FontW;
        uint32_t PixelY = Console.CursorY * FontH;
        DisplayChar(Console.FrameBuffer, Console.FramebufferWidth, PixelX, PixelY, Character, Console.TextColor);
        Console.CursorX++;
    }
    /* Wrap horizontally */
    if (Console.CursorX >= Console.ConsoleColumn)
    {
        Console.CursorX = 0;
        Console.CursorY++;
    }
    /* This is way faster then the wrap pix-to-pix copy*/
    if (Console.CursorY >= Console.ConsoleRow)
    {
        ClearConsole();
    }
}

void
PutPrint2Console(const char* String)
{
    while (*String)
    {
        PutChar2Console(*String);
        String++;
    }
}

void
SetBackgroundColor(uint32_t Foreground, uint32_t Background)
{
    Console.TextColor = Foreground;
    Console.BackgroundColor = Background;
}

void
SetCursor(uint32_t CursorXCoordinate, uint32_t CursorYCoordinate)
{
    if (CursorXCoordinate < Console.ConsoleColumn)
    {
        Console.CursorX = CursorXCoordinate;
    }
    if (CursorYCoordinate < Console.ConsoleRow)
    {
        Console.CursorY = CursorYCoordinate;
    }
}