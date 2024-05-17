#include "sdl_renderer.h"

Renderer::Renderer(SDL::Renderer& r)
    : R_(r)
{
}

void Renderer::SetColor(Graphics::Color c) {
    R_.SetColor({c.r, c.g, c.b, c.a});
}

void Renderer::DrawLine(Graphics::Point a, Graphics::Point b) {
    R_.DrawLine({a.x, a.y}, {b.x, b.y});
}

void Renderer::DrawRect(Graphics::Rect r) {
    SDL_Rect rect{r.x, r.y, r.w, r.h};
    R_.DrawRect(&rect);
}

void Renderer::Clear() {
    R_.Clear();
}

void Renderer::FillRect(Graphics::Rect r) {
    SDL_Rect rect{r.x, r.y, r.w, r.h};
    R_.FillRect(&rect);
}
