#pragma once

#include "renderer.h"
#include <stdint.h>

class Renderer : public Graphics::Renderer {
public:
    void SetCanvas(Graphics::Color* data, int width, int height);

    void SetColor(Graphics::Color c) override;
    void DrawLine(Graphics::Point a, Graphics::Point b) override;
    void DrawRect(Graphics::Rect r) override;
    void FillRect(Graphics::Rect r) override;
    void Clear() override;
private:
    Graphics::Color* Canvas_;
    int Width;
    int Height;
    Graphics::Color Color;
};

