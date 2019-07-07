#include "debugger/annotations.hpp"

#include <gameboycore/memorymap.h>

#include <fmt/format.h>

#include <array>
#include <sstream>


namespace utils
{
    IoAnnotation annotateSingleValue(const std::string& name, uint8_t value)
    {
        std::stringstream ss;
        ss << (int)value;

        return IoAnnotation{ name, {
            Annotation{{0,7}, "Value", ss.str()}
        } };
    }

    IoAnnotation annotateJoyPad(uint8_t value)
    {
        return IoAnnotation{};
    }

    IoAnnotation annotateInterruptFlags(uint8_t value)
    {
        std::stringstream ss;
        static const std::array<std::string, 5> interrupt_name = { "Vblank", "H-Blank", "Timer", "Serial", "Joypad" };

        std::vector<Annotation> annotations;

        for (auto i = 0; i < 8; ++i)
        {
            const auto mask = 1 << i;
            
            if (value & mask)
            {
                annotations.push_back(Annotation{ {i}, {}, interrupt_name[i] });
            }
        }

        IoAnnotation annotation;
        annotation.io_description = "Interrupt Flags";
        annotation.annotations = annotations;

        return annotation;
    }

    IoAnnotation annotateInterruptEnable(uint8_t value)
    {
        std::stringstream ss;
        static const std::array<std::string, 5> interrupt_name = { "Vblank", "H-Blank", "Timer", "Serial", "Joypad" };

        std::vector<Annotation> annotations;

        for (auto i = 0; i < 8; ++i)
        {
            const auto mask = 1 << i;

            if (value & mask)
            {
                annotations.push_back(Annotation{ {i}, {}, interrupt_name[i] });
            }
        }

        IoAnnotation annotation;
        annotation.io_description = "Interrupt Enable";
        annotation.annotations = annotations;

        return annotation;
    }

    IoAnnotation annotateTAC(uint8_t value)
    {
        IoAnnotation annotation;
        annotation.io_description = "Timer Controller";
        
        std::string clock_select;

        switch (value & 0x03)
        {
        case 0x00:
            clock_select = "4.096 KHz";
            break;
        case 0b01:
            clock_select = "262.144 KHz";
            break;
        case 0b10:
            clock_select = "65.536 KHz";
            break;
        case 0b11:
            clock_select = "16.384 KHz";
            break;
        default:
            break;
        }

        annotation.annotations = { Annotation{{0,1}, "Clock Select", clock_select} };

        return annotation;
    }

    IoAnnotation annotateSC(uint8_t value)
    {
        return IoAnnotation{ "Serial Control", {
                Annotation{ {0}, "Clock Select", (value & 0b01) ? "Internal" : "External" },
                Annotation{{1}, "Internal Shift Clock Switching Flag (CGB)", (value & 0b10) ? "256 Khz" : "8 KHz"},
                Annotation{{7}, "Serial Transfer Start", (value & 0x80) ? "Started" : "Idle"}
            }
        };
    }

    IoAnnotation annotateSVBK(uint8_t value)
    {
        if (value == 0)
            value = 1;

        std::stringstream ss;
        ss << (int)value;

        return IoAnnotation{ "Working RAM Selection", {
            Annotation{{0, 2}, "Selection", ss.str()}
        } };
    }

    IoAnnotation annotateKey1(uint8_t value)
    {
        return IoAnnotation{ "Speed Switch", {
            Annotation{{0}, "Enable speed switch", (value & 0b01) ? "Switching" : "Not switching"},
            Annotation{{7}, "Speed Flag", (value & 0x80) ? "Double Speed" : "Normal Speed"}
        } };
    }

    IoAnnotation annotateVBK(uint8_t value)
    {
        return IoAnnotation{ "LCD Display RAM Select", {
            Annotation{{0}, "Select", (value & 0x01) ? "Bank 1" : "Bank 0"}
        } };
    }

    IoAnnotation annotateLCDC(uint8_t value)
    {
        return IoAnnotation{ "LCD Controller", {
            Annotation{{0}, "BG Display", (value & 0x01) ? "ON" : "OFF"},
            Annotation{{1}, "OBJ Flag", (value & 0x02) ? "ON" : "OFF"},
            Annotation{{2}, "Sprite Dimensions", (value & 0x04) ? "8x8" : "8x16"},
            Annotation{{3}, "BG Code Area", (value & 0x08) ? "$9C00-$9FFF" : "$9800-$9BFF"},
            Annotation{{4}, "BG Charater Data", (value & 0x10) ? "$8000-$8FFF" : "$8800-$97FF"},
            Annotation{{5}, "Windowing", (value & 0x20) ? "ON" : "OFF"},
            Annotation{{6}, "Window Code Area", (value & 0x40) ? "$9C00-$9FFF" : "$9800-$9BFF"},
            Annotation{{7}, "LCD Enable", (value & 0x80) ? "ON" : "OFF"}
        } };
    }

    IoAnnotation annotateSTAT(uint8_t value)
    {
        std::string mode;
        switch (value & 0x03)
        {
        case 0:
            mode = "enable CPU access to display RAM";
            break;
        case 1:
            mode = "vertical blanking";
            break;
        case 2:
            mode = "searching OAM RAM";
            break;
        case 3:
            mode = "transferring data to LCD";
        default:
            break;
        }

        std::string interrupt_select;
        switch (((value & 0xE0) >> 4))
        {
        case 0:
            interrupt_select = "00 selection";
            break;
        case 1:
            interrupt_select = "01 selection 0: not selected";
            break;
        case 2:
            interrupt_select = "10 selection 1: selected";
        case 3:
            interrupt_select = "LYC = LY";
        default:
            break;
        }

        return IoAnnotation{ "STAT", {
            Annotation{{0,1}, "Mode", mode},
            Annotation{{3}, "Match", (value & 0x04) ? "1": "0"},
            Annotation{{3,7}, "Interrupt", interrupt_select}
        } };
    }

    IoAnnotation annotateIO(uint16_t address, uint8_t value)
    {
        switch (address)
        {
        case gb::memorymap::JOYPAD_REGISTER:
            return annotateJoyPad(value);
        case gb::memorymap::INTERRUPT_FLAG:
            return annotateInterruptFlags(value);
        case gb::memorymap::INTERRUPT_ENABLE:
            return annotateInterruptEnable(value);
        case gb::memorymap::TIMER_CONTROLLER_REGISTER:
            return annotateTAC(value);
        case gb::memorymap::SC_REGISTER:
            return annotateSC(value);
        case gb::memorymap::SVBK_REGISTER:
            return annotateSVBK(value);
        case gb::memorymap::KEY1_REGISER:
            return annotateKey1(value);
        case gb::memorymap::VBK_REGISTER:
            return annotateVBK(value);
        case gb::memorymap::LCDC_REGISTER:
            return annotateLCDC(value);
        case gb::memorymap::LCD_STAT_REGISTER:
            return annotateSTAT(value);
        case gb::memorymap::SCY_REGISTER:
            return annotateSingleValue("Scroll Y", value);
        case gb::memorymap::SCX_REGISTER:
            return annotateSingleValue("Scroll X", value);
        case gb::memorymap::LY_REGISTER:
            return annotateSingleValue("Scanline Position", value);
        case gb::memorymap::LYC_REGISTER:
            return annotateSingleValue("LY Compare", value);
        case gb::memorymap::WY_REGISTER:
            return annotateSingleValue("Window Y", value);
        case gb::memorymap::WX_REGISTER:
            return annotateSingleValue("Window X", value);
        default:
            return IoAnnotation{};
        }
    }
}