#pragma once

#include <exception>
#include <SDL2/SDL.h>

namespace SDL {
    class SdlException : public std::exception {
      public:
        SdlException()
        {
        }

        const char* what() const noexcept override {
            return SDL_GetError();
        }
    };
}
