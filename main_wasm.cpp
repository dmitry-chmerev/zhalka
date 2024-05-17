#include <stdint.h>
#include <stddef.h>

#include "game.h"
#include "wasm_renderer.h"

#include "memory.h"

using Zhalka::Game;

Game game;
Renderer renderer;

Graphics::Color* canvas = nullptr;

extern "C" void* setSize(int w, int h) {
    debug_print("set_size: w = ", w);
    debug_print("set_size: h = ", h);
    game.SetSize({w, h});
    if (canvas) {
        delete[] canvas;
    }
    canvas = new Graphics::Color[w * h];
    renderer.SetCanvas(canvas, w, h);

    game.SetRenderer(renderer);

    return canvas;
}

extern "C" void init() {
    game.SetRenderer(renderer);
    debug_print("__data_end", (int)&__data_end);
    debug_print("__heap_base", (int)&__heap_base);
}

extern "C" {
    void KeyDown(int key) {
        if (key > 0) {
            game.KeyDown(static_cast<Game::Key>(key));
        }
    }
    void KeyUp(int key) {
        if (key > 0) {
            game.KeyUp(static_cast<Game::Key>(key));
        }
    }

    void MouseDown(int x, int y) {
        game.MouseDown(x, y);
    }
    void MouseUp(int x, int y) {
        game.MouseUp(x, y);
    }
    void MouseMove(int x, int y) {
        debug_print("mousemove", x, y);
    }
}


extern "C" void* GetCanvas() {
    return canvas;
}

extern "C" void update(float dt) {
    game.Update(dt);
}
