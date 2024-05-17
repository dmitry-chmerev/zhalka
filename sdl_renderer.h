#pragma once

#include "renderer.h"
#include "lib/sdl/renderer.h"

class Renderer : public Graphics::Renderer {
public:
    Renderer(SDL::Renderer& r);
    void SetColor(Graphics::Color c) override;
    void DrawLine(Graphics::Point a, Graphics::Point b) override;
    void DrawRect(Graphics::Rect r) override;
    void FillRect(Graphics::Rect r) override;
    void Clear() override;
private:
    SDL::Renderer R_;
};
