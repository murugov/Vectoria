#ifndef COLORS_HPP
#define COLORS_HPP

#include <raylib.h>

namespace Graphic {
    
struct Color {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    operator ::Color() const {
        return {r, g, b, a};
    }
};

struct Colors {
    inline static const Color LightGray  { 200, 200, 200, 255 };
    inline static const Color Gray       { 130, 130, 130, 255 };
    inline static const Color DarkGray   { 80, 80, 80, 255 };
    inline static const Color Yellow     { 253, 249, 0, 255 };
    inline static const Color Gold       { 255, 203, 0, 255 };
    inline static const Color Orange     { 255, 161, 0, 255 };
    inline static const Color Pink       { 255, 109, 194, 255 };
    inline static const Color Red        { 230, 41, 55, 255 };
    inline static const Color Maroon     { 190, 33, 55, 255 };
    inline static const Color Green      { 0, 228, 48, 255 };
    inline static const Color Lime       { 0, 158, 47, 255 };
    inline static const Color DarkGreen  { 0, 117, 44, 255 };
    inline static const Color SkyBlue    { 102, 191, 255, 255 };
    inline static const Color Blue       { 0, 121, 241, 255 };
    inline static const Color DarkBlue   { 0, 82, 172, 255 };
    inline static const Color Purple     { 200, 122, 255, 255 };
    inline static const Color Violet     { 135, 60, 190, 255 };
    inline static const Color DarkPurple { 112, 31, 126, 255 };
    inline static const Color Beige      { 211, 176, 131, 255 };
    inline static const Color Brown      { 127, 106, 79, 255 };
    inline static const Color DarkBrown  { 76, 63, 47, 255 };
    inline static const Color White      { 255, 255, 255, 255 };
    inline static const Color Black      { 0, 0, 0, 255 };
    inline static const Color Blank      { 0, 0, 0, 0 };
    inline static const Color Magenta    { 255, 0, 255, 255 };
};

} // namespace Graphic

#endif
