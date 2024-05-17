#pragma once

#include <SDL2/SDL.h>

#include "exception.h"
#include "surface.h"
#include "renderer.h"

namespace SDL {
    class Window {
      public:
        Window()
          : W_(nullptr)
        {
        }
        Window(const char *title, int x, int y, int w, int h, Uint32 flags)
        {
            W_ = SDL_CreateWindow(title, x, y, w, h, flags);
            if (!W_) {
                throw SdlException();
            }
        }

        ~Window()
        {
            if (W_) {
                SDL_DestroyWindow(W_);
            }
        }

        Renderer CreateRenderer() {
            SDL_Renderer* ret = SDL_CreateRenderer(W_, -1, SDL_RENDERER_ACCELERATED);
            if (!ret) {
                throw SdlException();
            }
            return Renderer(ret);
        }

        WindowSurface GetSurface() {
            SDL_Surface* s = SDL_GetWindowSurface(W_);
            if (!s) {
                throw SdlException();
            }
            return WindowSurface(s);
        }

        void Update() {
            SDL_UpdateWindowSurface(W_);
        }

        auto Handle() { return W_; }
      private:
        SDL_Window* W_;
    };
}
