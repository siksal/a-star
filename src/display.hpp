#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

struct Vector2
{
    uint16_t x;
    uint16_t y;
};

class Display
{
    public:
        Display(const char* title, int w, int h);
        ~Display();
        void destroyRenderer();
        void fillRectangle(SDL_Rect& rect, uint16_t& rect_x, uint16_t& rect_y);
        void drawGrid(SDL_Rect& rect, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y);
        uint16_t getCellLocationX(std::vector<uint16_t>& cell_x, Vector2& mouse);
        uint16_t getCellLocationY(std::vector<uint16_t>& cell_y, Vector2& mouse);
        void setStart(Vector2& start, Vector2& goal, SDL_bool& s_pressed, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse);
        void setGoal(Vector2& goal, Vector2& start, SDL_bool& g_pressed, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse);
        void setObstacle(std::vector<Vector2>& obs, Vector2& goal, Vector2& start, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse);
        void fillObstacle(SDL_Rect& cell, std::vector<Vector2>& obs);
        void drawLine(Vector2& start, Vector2& goal);
        void clearScreen();
        void updateScreen();
        void drawColor(const uint8_t& r, const uint8_t& g, const uint8_t& b);
        // void cleanUp();
        constexpr static uint8_t START_POINT = 100;
        constexpr static uint8_t WIDTH = 40;
        constexpr static uint8_t HEIGHT = 40;
        constexpr static uint8_t CELL_GAP = 1;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};