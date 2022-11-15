#include "display.hpp"

Display::Display(const char* title, int w, int h) : window(nullptr), renderer(nullptr)
{
    window = SDL_CreateWindow(title, 20, 20, w, h, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        // std::cout << "Window failed to init" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
}

Display::~Display()
{
    destroyRenderer();
}

void Display::drawGrid(SDL_Rect& cell, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y)
{
    for (uint8_t i = 0; i < cell_x.size(); ++i)
    {
        if (i == 0) cell_x[i] = START_POINT;
        else cell_x[i] = cell_x[i-1] + WIDTH + CELL_GAP;

        for (uint8_t j = 0; j < cell_y.size(); ++j)
        {
            if (j == 0) cell_y[j] = START_POINT;
            else cell_y[j] = cell_y[j-1] + WIDTH + CELL_GAP;
            drawColor(22,22,22);
            fillRectangle(cell, cell_x[i], cell_y[j]);
        }
    }
}

uint16_t Display::getCellLocationX(std::vector<uint16_t>& cell_x, Vector2& mouse)
{
    auto mouse_cell_x = std::lower_bound(cell_x.begin(), cell_x.end(), mouse.x);
    --mouse_cell_x;
    uint16_t x;
    x = *mouse_cell_x;
    return x;
}

uint16_t Display::getCellLocationY(std::vector<uint16_t>& cell_y, Vector2& mouse)
{
    auto mouse_cell_y = std::lower_bound(cell_y.begin(), cell_y.end(), mouse.y);
    --mouse_cell_y;
    uint16_t y;
    y = *mouse_cell_y;
    return y;
}

void Display::setStart(Vector2& start, Vector2& goal, SDL_bool& s_pressed, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse)
{
    auto pos_x = getCellLocationX(cell_x, mouse);
    auto pos_y = getCellLocationY(cell_y, mouse);

    if (goal.x == pos_x && goal.y == pos_y)
    {
        std::cout << "Goal and Start cannot be in the same cell" << std::endl;
    }
    else
    {
        start.x = pos_x;
        start.y = pos_y;
        std::cout << "Start at: " << start.x << ", " << start.y << std::endl;
    }
    s_pressed = SDL_FALSE;
    mouse_clicked = SDL_FALSE;
}

void Display::setGoal(Vector2& goal, Vector2& start, SDL_bool& g_pressed, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse)
{
    auto pos_x = getCellLocationX(cell_x, mouse);
    auto pos_y = getCellLocationY(cell_y, mouse);

    if (start.x == pos_x && start.y == pos_y)
    {
        std::cout << "Goal and Start cannot be in the same cell" << std::endl;
    }
    else
    {
        goal.x = pos_x;
        goal.y = pos_y;
        std::cout << "Goal at: " << goal.x << ", " << goal.y << std::endl;
    }
    g_pressed = SDL_FALSE;
    mouse_clicked = SDL_FALSE;
}

void Display::setObstacle(std::vector<Vector2>& obs, Vector2& goal, Vector2& start, SDL_bool& mouse_clicked, std::vector<uint16_t>& cell_x, std::vector<uint16_t>& cell_y, Vector2& mouse)
{
    auto pos_x = getCellLocationX(cell_x, mouse);
    auto pos_y = getCellLocationY(cell_y, mouse);

    if ((start.x == pos_x && start.y == pos_y) || (goal.x == pos_x && goal.y == pos_y))
    {
        std::cout << "Cannot place obstacle here, cell occupied" << std::endl;
    }
    else if (obs.empty())
    {
        obs.push_back({pos_x, pos_y});
    }
    else
    {
        for (uint16_t i = 0; i < obs.size(); ++i)
        {
            if (obs[i].x == pos_x && obs[i].y == pos_y)
            {
                auto itr = obs.begin();
                obs.erase(itr+i);
                obs.shrink_to_fit();
                break;
            }
            if ((i==obs.size()-1) && (obs[i].x != pos_x || obs[i].y != pos_y))
            {
                obs.push_back({pos_x, pos_y});
                break;
            }
        }
    }

    mouse_clicked = SDL_FALSE;
}

void Display::fillObstacle(SDL_Rect& cell, std::vector<Vector2>& obs)
{
    for (uint16_t i = 0; i < obs.size(); ++i)
    {
        drawColor(44,44,44);
        fillRectangle(cell, obs[i].x, obs[i].y);
    }
}

void Display::fillRectangle(SDL_Rect& rect, uint16_t& rect_x, uint16_t& rect_y)
{
    rect.x = rect_x;
    rect.y = rect_y;
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_RenderFillRect(renderer, &rect);
}

void Display::drawLine(Vector2& start, Vector2& goal)
{
    SDL_RenderDrawLine(renderer, start.x, start.y, goal.x, goal.y);
}

void Display::clearScreen()
{
    SDL_RenderClear(renderer);
}

void Display::updateScreen()
{
    SDL_RenderPresent(renderer);
}

void Display::destroyRenderer()
{
    // Destroy Renderer
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    // Destroy Window
    if(window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Display::drawColor(const uint8_t& r, const uint8_t& g, const uint8_t& b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}
