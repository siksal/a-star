#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <iostream>
#include <vector>
#include "forward_list"
#include "display.hpp"

struct Node
{
    uint16_t x;
    uint16_t y;
    double F; // cost F = G + H
    double G; // distance from starting node
    double H; // distance from goal node
    Node():x(0),y(0),F(0),G(0),H(0){}; // initial values
};

template<typename T1, typename T2>
struct Path
{
    T1 x;
    T2 y;
 
    // constructor
    Path(T1 x, T2 y)
    {
        this->x = x;
        this->y = y;
    }
 
    // `operator==` is required to compare keys in case of a hash collision
    bool operator==(const Path &p) const {
        return x == p.x && y == p.y;
    }
};
 
// The specialized hash function for `unordered_map` keys
struct hash_fn
{
    template <class T1, class T2>
    std::size_t operator() (const Path<T1, T2> &path) const
    {
        std::size_t h1 = std::hash<T1>()(path.x);
        std::size_t h2 = std::hash<T2>()(path.y);
 
        return h1 ^ h2;
    }
};

class Astar
{
    public:
        Astar(Vector2& start, Vector2& goal, std::vector<Vector2>& obs, SDL_Rect& rect, Display& disp);
        ~Astar();
        bool isNeighbourInObstacle(std::vector<Vector2>& obs, Node& neighbour_);
        bool isNeighbourInList(std::forward_list<Node>& lists, Node& neighbour_);
        bool isOutsideGrid(Node& neighbour_);
        bool isNeighbourFShorter(std::forward_list<Node>& lists, Node& neighbour_, double& F);
};