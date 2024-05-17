#pragma once

#include <stdint.h>

namespace Graphics {
    struct Point
    {
        int x;
        int y;
    };

    struct Size
    {
        int w;
        int h;
    };

    struct Rect {
        int x;
        int y;
        int w;
        int h;
    };

    struct RectF {
        float x;
        float y;
        float w;
        float h;
    };

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        operator uint32_t() const  {
            return (r << 24) + (g << 16) + (b << 8) + a;
        }

        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
            : r(r)
            , g(g)
            , b(b)
            , a(a)
        {
        }

        Color()
            : r(0)
            , g(0)
            , b(0)
            , a(255)
        {
        }

        Color(uint32_t val) {
            r = (val >> 24) & 0xFF;
            g = (val >> 16) & 0xFF;
            b = (val >> 8) & 0xFF;
            a = val & 0xFF;
        }

        static const Color EMPTY;
        static const Color BLACK;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color YELLOW;
    };

    class Renderer {
    public:
        virtual void Clear() = 0;
        virtual void SetColor(Color c) = 0;
        virtual void DrawLine(Point a, Point b) = 0;
        virtual void DrawRect(Rect r) = 0;
        virtual void FillRect(Rect r) = 0;
        virtual void FillRect(RectF r) {
            Rect rect;
            rect.x = r.x;
            rect.y = r.y;
            rect.w = r.w;
            rect.h = r.h;
            FillRect(rect);
        }
    };
}
