#include <iostream>
#include <vector>

#include "lib/sdl/window.h"

#include "sdl_renderer.h"

#include "game.h"

constexpr size_t WIDTH = 800;
constexpr size_t HEIGHT = 600;

using Zhalka::Game;

void printn(const char* name, int val) {
    std::cout << name << ": " << val << std::endl;
}

void printnn(const char* name, int a, int b) {
    std::cout << name << ": " << a << ", " << b << std::endl;
}

Game::Key Translate(SDL_Keycode key) {
    if (key == SDLK_p) {
        return Game::Key::Pause;
    } else if (key == SDLK_LEFT) {
        return Game::Key::Left;
    } else if (key == SDLK_RIGHT) {
        return Game::Key::Right;
    } else if (key == SDLK_UP) {
        return Game::Key::Up;
    } else if (key == SDLK_DOWN) {
        return Game::Key::Down;
    } else if (key == SDLK_SPACE) {
        return Game::Key::Space;
    }
    return Game::Key::None;
}

int main() {
    using SDL::Window;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    Window window("Zhalka", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    auto renderer = window.CreateRenderer();

    SDL_Event ev;

    Renderer r(renderer);
    Game game;
    game.SetRenderer(r);
    game.SetSize({WIDTH, HEIGHT});

    bool isRunning = true;

    auto prevTs = SDL_GetTicks64();

    while (isRunning) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            } else if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
                    auto w = ev.window.data1;
                    auto h = ev.window.data2;
                    game.SetSize({w, h});
                }
            } else if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else {
                    game.KeyDown(Translate(ev.key.keysym.sym));
                }
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                game.MouseDown(ev.button.x, ev.button.y);
            } else if (ev.type == SDL_MOUSEBUTTONUP) {
                game.MouseUp(ev.button.x, ev.button.y);
            } else if (ev.type == SDL_KEYUP) {
                game.KeyUp(Translate(ev.key.keysym.sym));
            }
        }

        auto now = SDL_GetTicks64();
        float dt = (now - prevTs) / 1000.0;
        prevTs = now;

        game.Update(dt);

        renderer.Present();
        window.Update();
    }

    return 0;
}

