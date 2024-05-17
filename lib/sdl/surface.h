#pragma once

#include <SDL2/SDL.h>

#include "exception.h"

namespace SDL {
    class WindowSurface {
      public:
        WindowSurface()
            : H_(nullptr)
        {
        }
        explicit WindowSurface(SDL_Surface* h)
            : H_(h)
        {
        }
        ~WindowSurface() {
        }
        auto Format() const {
            return H_->format;
        }
        auto Handle() { return H_; }
      private:
        SDL_Surface* H_;
    };

    class Surface {
      public:
        explicit Surface(const char* fileName) {
            H_ = SDL_LoadBMP("./image.bmp");
        }

        Surface(const Surface&) = delete;

        ~Surface() {
            if (H_) {
                SDL_FreeSurface(H_);
            }
        }

        void ConvertTo(const WindowSurface& surface) {
            auto tmp = SDL_ConvertSurface(H_, surface.Format(), 0);
            SDL_FreeSurface(H_);
            H_ = tmp;
        }
        auto Handle() { return H_; }
        void BlitTo(WindowSurface& s) {
            SDL_BlitSurface(H_, nullptr, s.Handle(), nullptr);
        }
      private:
        SDL_Surface* H_;
    };
}
