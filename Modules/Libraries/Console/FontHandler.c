#include <Externals/Fonts.h>

void
DisplayChar(uint32_t* Framebuffer, uint32_t FramebufferWidth, uint32_t PositionX, uint32_t PositionY, char Character, uint32_t Color32)
{
    /* Retrieve the 16-byte bitmap for this character */
    const uint8_t* CharacterBit = TerminusFont[(uint8_t)Character];

    /* Render each row of the 8x16 character */
    for (int MapRow = 0; MapRow < FontH; MapRow++)
    {
        uint8_t Line = CharacterBit[MapRow];

        /* Process each column (bit) in the row */
        for (int Column = 0; Column < FontW; Column++)
        {
            /* Check if bit is set (MSB is leftmost pixel) */

            if (Line & (0x80 >> Column))
            {
                /* Calculate framebuffer offset and set pixel */
                Framebuffer[(PositionY + MapRow) * FramebufferWidth + (PositionX + Column)] = Color32;
            }
        }
    }
}

void
DisplayString(uint32_t* Framebuffer, uint32_t FramebufferWidth, uint32_t PositionX, uint32_t PositionY, const char* String, uint32_t Color32)
{
    uint32_t NewPositionX = PositionX;
    while (*String)
    {
        DisplayChar(Framebuffer, FramebufferWidth, NewPositionX, PositionY, *String, Color32);
        NewPositionX += FontW;
        String++;
    }
}