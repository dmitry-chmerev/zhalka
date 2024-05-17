#pragma once

#include <SDL2/SDL.h>
#include "exception.h"

#include <vector>

namespace SDL {
    class Renderer {
    public:
        Renderer(SDL_Renderer* handle)
            : Handle_(handle)
        {
        }

        ~Renderer() {
            SDL_DestroyRenderer(Handle_);
        }

        void SetColor(SDL_Color c) {
            SDL_SetRenderDrawColor(Handle_, c.r, c.g, c.b, c.a);
        }

        void Clear() {
            SDL_RenderClear(Handle_);
        }

        void DrawRect(SDL_Rect* rect) {
            SDL_RenderDrawRect(Handle_, rect);
        }

        void FillRect(SDL_Rect* rect) {
            SDL_RenderFillRect(Handle_, rect);
        }

        void DrawLines(const std::vector<SDL_Point>& points) {
            if (!points.empty()) {
                SDL_RenderDrawLines(Handle_, &points.front(), points.size());
            }
        }

        void DrawLine(SDL_Point a, SDL_Point b) {
            SDL_RenderDrawLine(Handle_, a.x, a.y, b.x, b.y);
        }

        void Present() {
            SDL_RenderPresent(Handle_);
        }

    private:
        SDL_Renderer* Handle_;
    };
}
