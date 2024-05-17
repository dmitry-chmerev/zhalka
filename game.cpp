#include "game.h"
#include "memory.h"
#include "algorithm.h"

namespace Zhalka {
    void Game::SetRenderer(Graphics::Renderer& renderer)
    {
        R_ = &renderer;
        rect = {20, 20, 50, 50};
        xvel = 82.0;
        yvel = 37.0;
        Paused = false;
        time = 0;
        NextTick(1.0);
        Color_ = Graphics::Color::GREEN;

        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            for (int i = 0; i < FIELD_WIDTH; ++i) {
                State.Well[i][j] = Graphics::Color::EMPTY;
            }
        }
    }

    void Game::SetSize(Graphics::Size size) {
        WellArea = {
            LEFT_MARGIN + 2,
            TOP_MARGIN + 2,
            size.w - LEFT_MARGIN - RIGHT_MARGIN - 4,
            size.h - TOP_MARGIN - BOTTOM_MARGIN - 4
        };

        int cellSize = min(WellArea.w / FIELD_WIDTH, WellArea.h / FIELD_HEIGHT);
        WellArea.w = cellSize * FIELD_WIDTH;
        WellArea.h = cellSize * FIELD_HEIGHT;
        Border = {WellArea.x - 2, WellArea.y - 2, WellArea.w + 4, WellArea.h + 4};
        Cell = Graphics::Rect{0, 0, cellSize, cellSize};
    }

    void Game::RenderField() {
        using Graphics::Point;

        // draw border
        R_->SetColor(Graphics::Color::GREEN);
        R_->DrawRect(Border);

        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            for (int i = 0; i < FIELD_WIDTH; ++i) {
                const auto cell = State.Well[i][j];
                if (cell != Graphics::Color::EMPTY) {
                    Graphics::Rect rect = Cell;
                    rect.x = WellArea.x + i * Cell.w;
                    rect.y = WellArea.y + (WellArea.h - (j + 1) * Cell.h);

                    R_->SetColor(cell);
                    R_->FillRect(rect);
                }
            }
        }
    }

    void Game::NextTick(float dt) {
        time = 0.0f;
        NextTick_ = dt;
    }

    void Game::Tick() {
        if (Color_ == Graphics::Color::GREEN) {
            Color_ = Graphics::Color::BLUE;
        } else if (Color_ == Graphics::Color::BLUE) {
            Color_ = Graphics::Color::RED;
        } else if (Color_ == Graphics::Color::RED) {
            Color_ = Graphics::Color::GREEN;
        }
        NextTick(1.0);
    }

    void Game::Update(float dt) {
        R_->SetColor(Graphics::Color::BLACK);
        R_->Clear();

        RenderField();

        if (!Paused) {
            time += dt;
            if (NextTick_ <= time) {
                Tick();
            }
            rect.x += xvel * dt;
            rect.y += yvel * dt;

            if (rect.x < WellArea.x) {
                rect.x = WellArea.x;
                xvel *= -1;
            }
            if (rect.y < WellArea.y) {
                rect.y = WellArea.y;
                yvel *= -1;
            }
            if (rect.x + rect.w > WellArea.x + WellArea.w) {
                rect.x = WellArea.x + WellArea.w - rect.w;
                xvel *= -1;
            }
            if (rect.y + rect.h > WellArea.y + WellArea.h) {
                rect.y = WellArea.y + WellArea.h - rect.h;
                yvel *= -1;
            }
        }

        R_->SetColor(Color_);
        R_->FillRect(rect);
    }

    void Game::KeyDown(Key key) {
    }

    void Game::KeyUp(Key key) {
        if (key == Key::Pause) {
            Paused = !Paused;
        }
    }

    void Game::MouseDown(int x, int y) {
        debug_print("mousedown", x, y);
        Paused = !Paused;
    }
    void Game::MouseUp(int x, int y) {
        debug_print("mouseup", x, y);
    }
}
