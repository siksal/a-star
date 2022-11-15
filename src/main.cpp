#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <iostream>
#include <vector>
#include <algorithm>
#include "display.hpp"
#include "astar.hpp"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout <<"SDL_Init HAS FAILED." << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init HAS FAILED" << SDL_GetError() << std::endl;

    Display window("A-Star Algorithm", 1010, 1200);
    // Astar aStar;

    SDL_bool is_running = SDL_TRUE;
    SDL_Event event;
    constexpr static uint8_t MAX_SIZE = 20;

    SDL_Rect rect_;
    std::vector<uint16_t> _cell_x(MAX_SIZE);
    std::vector<uint16_t> _cell_y(MAX_SIZE);

    std::vector<Vector2> obs;

    Vector2 start;
    Vector2 goal;

    start.x = 305;
    start.y = 469;
    goal.x = 674;
    goal.y = 469;

    Vector2 mouse;    

    SDL_bool s_pressed = SDL_FALSE;
    SDL_bool g_pressed = SDL_FALSE;
    SDL_bool o_pressed = SDL_FALSE;
    SDL_bool active = SDL_FALSE;
    SDL_bool mouse_clicked = SDL_FALSE;

    while (is_running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_s:
                        s_pressed = SDL_TRUE;
                        break;
                    case SDLK_g:
                        g_pressed = SDL_TRUE;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                mouse.x = event.motion.x;
                mouse.y = event.motion.y;
                mouse_clicked = SDL_TRUE;
                break;

            case SDL_QUIT:
                is_running = SDL_FALSE;
                break;
            
            default:
                break;
            }
            
        }

        window.drawColor(0,0,0);
        window.clearScreen();

        window.drawGrid(rect_, _cell_x, _cell_y);

        if (s_pressed && mouse_clicked)
        {
            window.setStart(start, goal, s_pressed, mouse_clicked, _cell_x, _cell_y, mouse);
        }

        window.drawColor(255,255,0);
        window.fillRectangle(rect_, start.x, start.y);

        if (g_pressed && mouse_clicked)
        {
            window.setGoal(goal, start, g_pressed, mouse_clicked, _cell_x, _cell_y, mouse);
        }

        window.drawColor(0,255,0);
        window.fillRectangle(rect_, goal.x, goal.y);

        if (mouse_clicked && !s_pressed && !g_pressed)
        {
            window.setObstacle(obs, goal, start, mouse_clicked, _cell_x, _cell_y, mouse);
        }
        window.fillObstacle(rect_, obs);
        Astar astar(start, goal, obs, rect_, window);
        window.updateScreen();
        astar.~Astar();
        // window.~Display();
        // aStar.~Astar();

    }

    window.destroyRenderer();
    SDL_Quit();

    return 0;
}