#include "wasm_renderer.h"

#include "algorithm.h"

void Renderer::SetCanvas(Graphics::Color* data, int width, int height)
{
    Canvas_ = data;

    Width = width;
    Height = height;
}

void Renderer::SetColor(Graphics::Color c) {
    Color = c;
}

void Renderer::DrawLine(Graphics::Point a, Graphics::Point b) {
    if (a.x == b.x) {
        auto x = a.x;
        auto [miny, maxy] = minmax(a.y, b.y);
        for (int y = miny; y <= maxy; ++y) {
            Canvas_[y*Width + x] = Color;
        }
    } else if (a.y == b.y) {
        auto y = a.y;
        auto [minx, maxx] = minmax(a.x, b.x);
        for (int x = minx; x <= maxx; ++x) {
            Canvas_[y*Width + x] = Color;
        }
    }
}

void Renderer::DrawRect(Graphics::Rect r) {
    using Graphics::Point;
    Point a = {r.x, r.y};
    Point b = {r.x, r.y + r.h};
    Point c = {r.x + r.w, r.y + r.h};
    Point d = {r.x + r.w, r.y};
    DrawLine(a, b);
    DrawLine(b, c);
    DrawLine(c, d);
    DrawLine(d, a);
}

void Renderer::FillRect(Graphics::Rect r) {
    for (int y = r.y; y < r.y + r.h; ++y) {
        for (int x = r.x; x < r.x + r.w; ++x) {
            Canvas_[y*Width + x] = Color;
        }
    }
}

void Renderer::Clear() {
    for (int i = 0; i < Width * Height; ++i) {
        Canvas_[i] = Color;
    }
}
