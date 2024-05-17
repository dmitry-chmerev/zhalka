#pragma once

#include "renderer.h"

#include <stdint.h>
#include <stddef.h>
#include "string.h"

extern "C" {
    void printn(const char* name, int val);
    void printnn(const char* name, int a, int b);
}

inline void debug_print(const char* name, int val) {
    printn(name, val);
}

inline void debug_print(const char* name, int a, int b) {
    printnn(name, a, b);
}

namespace Zhalka {
    constexpr int TOP_MARGIN = 10;
    constexpr int LEFT_MARGIN = 10;
    constexpr int RIGHT_MARGIN = 10;
    constexpr int BOTTOM_MARGIN = 10;

    constexpr int FIELD_WIDTH = 10;
    constexpr int FIELD_HEIGHT = 20;
    constexpr size_t FIELD_MARGIN = 3;
    constexpr size_t FIELD_BUFFER_ZONE = 3;

    struct Well {
        static constexpr size_t FullWidth = FIELD_MARGIN + FIELD_WIDTH + FIELD_MARGIN;
        static constexpr size_t FullHeight = FIELD_MARGIN + FIELD_HEIGHT + FIELD_BUFFER_ZONE;
        Graphics::Color CellColors[FIELD_WIDTH][FIELD_HEIGHT];
        char Cells[FullWidth * FullHeight];
    };

    struct GameState {
        Graphics::Color Well[FIELD_WIDTH][FIELD_HEIGHT];
    };

    class Game {
    public:
        enum class Key {
            None,
            Pause,
            Left,
            Right,
            Up,
            Down,
            Space,
        };
        void SetRenderer(Graphics::Renderer& r);

        void SetSize(Graphics::Size size);
        void RenderField();

        void Update(float dt);
        void NextTick(float dt);
        void Render(float dt);

        void KeyUp(Key key);
        void KeyDown(Key key);
        void Tick();

        void MouseDown(int x, int y);
        void MouseUp(int x, int y);

    private:
        Graphics::Renderer* R_;
        Graphics::Rect WellArea;
        Graphics::Rect Border;
        Graphics::Rect Cell;

        Graphics::RectF rect;

        float xvel = 40.0;
        float yvel = 40.0;
        Graphics::Color Color_;

        float time;
        float NextTick_;

        bool Paused;
        GameState State;
    };
}
