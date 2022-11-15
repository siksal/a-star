// #include <cmath>
#include "unordered_map"
#include "astar.hpp"

Astar::Astar(Vector2& start, Vector2& goal, std::vector<Vector2>& obs, SDL_Rect& rect, Display& disp)
{
    std::forward_list<Node> open_list;
    std::forward_list<Node> closed_list;
    Node current_node;
    std::unordered_map<Path<uint16_t, uint16_t>, Path<uint16_t, uint16_t>, hash_fn> parents;
    const int WEIGHT = 10;
    const int D_WEIGHT = 14;

    Node start_;
    start_.x = start.x;
    start_.y = start.y;
    start_.H = sqrt(pow((goal.y - start_.y),2) + pow((goal.x - start_.x),2));
    // start_.H = abs(int(goal.y - start_.y)) + abs(int(goal.x - start_.x));
    start_.G = 0;
    start_.F = start_.G + start_.H;

    open_list.push_front(start_);
    while (true)
    {
        open_list.sort([](const Node& lhs, const Node& rhs) {return lhs.F < rhs.F;});
        current_node = open_list.front();
        open_list.pop_front();
        closed_list.push_front(current_node);
        uint8_t neighbours = 8;
        if (current_node.x == goal.x && current_node.y == goal.y)
        {
            // std::cout << "goal found" << std::endl;
            break;
        }
        for (uint8_t i = 0; i <= neighbours-1; ++i)
        {
            Node neighbour;
            int kx, ky, WGHT;
            double F_;

            if (i==0)
            {
                kx = 41; ky = 0;// WGHT = WEIGHT; // right
            }
            if (i==1)
            {
                kx = -41; ky = 0;// WGHT = WEIGHT; // left
            }
            if (i==2)
            {
                kx = 0; ky = 41;// WGHT = WEIGHT; // up
            }
            if (i==3)
            {
                kx = 0; ky = -41;// WGHT = WEIGHT; // down
            }
            if (i==4)
            {
                kx = -41; ky = 41;// WGHT = D_WEIGHT; // diagonal up left
            }
            if (i==5)
            {
                kx = +41; ky = -41;// WGHT = D_WEIGHT; // diagonal down right
            }
            if (i==6)
            {
                kx = 41; ky = 41;// WGHT = D_WEIGHT; // diagonal up right
            }
            if (i==7)
            {
                kx = -41; ky = -41;// WGHT = D_WEIGHT; // diagonal down left
            }

            neighbour.x = current_node.x+kx;
            neighbour.y = current_node.y+ky;
            neighbour.H = sqrt(pow((goal.y - neighbour.y),2) + pow((goal.x - neighbour.x),2));
            // neighbour.H = abs(int(goal.y - neighbour.y)) + abs(int(goal.x - neighbour.x));
            // neighbour.G = current_node.G + WGHT;
            neighbour.G = current_node.G + (sqrt(pow((current_node.y - neighbour.y),2) + pow((current_node.x - neighbour.x),2)));
            F_ = neighbour.G + neighbour.H;

            if (isNeighbourInObstacle(obs, neighbour) or isNeighbourInList(closed_list, neighbour) or isOutsideGrid(neighbour))
            {
                continue;
            }

            if (isNeighbourFShorter(open_list, neighbour, F_) or !isNeighbourInList(open_list, neighbour))
            {
                neighbour.F = F_;
                auto it = parents.find({neighbour.x, neighbour.y});
                if (it != parents.end())
                {
                    parents.erase({neighbour.x, neighbour.y});
                    parents.insert({{neighbour.x, neighbour.y}, {current_node.x, current_node.y}});
                }
                else
                {
                    parents.insert({{neighbour.x, neighbour.y}, {current_node.x, current_node.y}});
                }

                if (!isNeighbourInList(open_list, neighbour))
                {
                    open_list.push_front(neighbour);
                }

            }
        }
    }

    // for (const auto& parent : parents)
    // {
    //     std::cout << parent.first.x <<"," << parent.first.y <<" : " << parent.second.x <<"," << parent.second.y << std::endl;
    // }
    // std::cout << "parent done" << std::endl;

    if (current_node.x == goal.x && current_node.y == goal.y)
    {
        // std::cout << "val" << std::endl;
        auto val = parents.find({current_node.x, current_node.y});
        // std::cout << val->first.x <<"," << val->first.y <<" : " << val->second.x <<"," << val->second.y << std::endl;
        // std::cout << "val end" << std::endl;
        disp.drawColor(0,0,255);
        disp.fillRectangle(rect, val->second.x, val->second.y);
        while (val->second.x != start.x or val->second.y != start.y)
        {
            // std::cout << "here" << std::endl;
            val = parents.find({val->second.x, val->second.y});
            if (val->second.x == start.x and val->second.y == start.y)
            {
                // Display::fillRectangle(rect, val->second.x, val->second.y);
                // std::cout << "Path found" << std::endl;
                return;
            }
            disp.drawColor(0,0,255);
            disp.fillRectangle(rect, val->second.x, val->second.y);
        }
        
    }
}
Astar::~Astar(){}

// void Astar::astar(Vector2& start, Vector2& goal, std::vector<Vector2>& obs, SDL_Rect& rect, Display& disp)
// {
//     std::forward_list<Node> open_list;
//     std::forward_list<Node> closed_list;
//     Node current_node;
//     std::unordered_map<Path<uint16_t, uint16_t>, Path<uint16_t, uint16_t>, hash_fn> parents;
//     const int WEIGHT = 10;
//     const int D_WEIGHT = 14;

//     Node start_;
//     start_.x = start.x;
//     start_.y = start.y;
//     // start_.H = sqrt(pow((goal.y - start_.y),2) + pow((goal.x - start_.x),2));
//     start_.H = abs(int(goal.y - start_.y)) + abs(int(goal.x - start_.x));
//     start_.G = 0;
//     start_.F = start_.G + start_.H;

//     open_list.push_front(start_);
//     while (true)
//     {
//         open_list.sort([](const Node& lhs, const Node& rhs) {return lhs.F < rhs.F;});
//         current_node = open_list.front();
//         open_list.pop_front();
//         closed_list.push_front(current_node);
//         uint8_t neighbours = 8;
//         if (current_node.x == goal.x && current_node.y == goal.y)
//         {
//             // std::cout << "goal found" << std::endl;
//             break;
//         }
//         for (uint8_t i = 0; i <= neighbours-1; ++i)
//         {
//             Node neighbour;
//             int kx, ky, WGHT;
//             double F_;

//             if (i==0)
//             {
//                 kx = 41; ky = 0; WGHT = WEIGHT; // right
//             }
//             if (i==1)
//             {
//                 kx = -41; ky = 0; WGHT = WEIGHT; // left
//             }
//             if (i==2)
//             {
//                 kx = 0; ky = 41; WGHT = WEIGHT; // up
//             }
//             if (i==3)
//             {
//                 kx = 0; ky = -41; WGHT = WEIGHT; // down
//             }
//             if (i==4)
//             {
//                 kx = -41; ky = 41; WGHT = D_WEIGHT; // diagonal up left
//             }
//             if (i==5)
//             {
//                 kx = +41; ky = -41; WGHT = D_WEIGHT; // diagonal down right
//             }
//             if (i==6)
//             {
//                 kx = 41; ky = 41; WGHT = D_WEIGHT; // diagonal up right
//             }
//             if (i==7)
//             {
//                 kx = -41; ky = -41; WGHT = D_WEIGHT; // diagonal down left
//             }

//             neighbour.x = current_node.x+kx;
//             neighbour.y = current_node.y+ky;
//             // neighbour.H = sqrt(pow((goal.y - neighbour.y),2) + pow((goal.x - neighbour.x),2));
//             neighbour.H = abs(int(goal.y - neighbour.y)) + abs(int(goal.x - neighbour.x));
//             neighbour.G = current_node.G + WGHT;
//             F_ = neighbour.G + neighbour.H;

//             if (isNeighbourInObstacle(obs, neighbour) or isNeighbourInList(closed_list, neighbour) or isOutsideGrid(neighbour))
//             {
//                 continue;
//             }

//             if (isNeighbourFShorter(open_list, neighbour, F_) or !isNeighbourInList(open_list, neighbour))
//             {
//                 neighbour.F = F_;
//                 auto it = parents.find({neighbour.x, neighbour.y});
//                 if (it != parents.end())
//                 {
//                     parents.erase({neighbour.x, neighbour.y});
//                     parents.insert({{neighbour.x, neighbour.y}, {current_node.x, current_node.y}});
//                 }
//                 else
//                 {
//                     parents.insert({{neighbour.x, neighbour.y}, {current_node.x, current_node.y}});
//                 }

//                 if (!isNeighbourInList(open_list, neighbour))
//                 {
//                     open_list.push_front(neighbour);
//                 }

//             }
//         }
//     }

//     // for (const auto& parent : parents)
//     // {
//     //     std::cout << parent.first.x <<"," << parent.first.y <<" : " << parent.second.x <<"," << parent.second.y << std::endl;
//     // }
//     // std::cout << "parent done" << std::endl;

//     if (current_node.x == goal.x && current_node.y == goal.y)
//     {
//         // std::cout << "val" << std::endl;
//         auto val = parents.find({current_node.x, current_node.y});
//         // std::cout << val->first.x <<"," << val->first.y <<" : " << val->second.x <<"," << val->second.y << std::endl;
//         // std::cout << "val end" << std::endl;
//         disp.drawColor(0,0,255);
//         disp.fillRectangle(rect, val->second.x, val->second.y);
//         while (val->second.x != start.x or val->second.y != start.y)
//         {
//             std::cout << "here" << std::endl;
//             val = parents.find({val->second.x, val->second.y});
//             if (val->second.x == start.x and val->second.y == start.y)
//             {
//                 // Display::fillRectangle(rect, val->second.x, val->second.y);
//                 std::cout << "Path found" << std::endl;
//                 return;
//             }
//             disp.drawColor(0,0,255);
//             disp.fillRectangle(rect, val->second.x, val->second.y);
//         }
        
//     }
// }

bool Astar::isNeighbourInObstacle(std::vector<Vector2>& obs, Node& neighbour_)
{
    bool inObs = false;

    for (uint16_t i = 0; i < obs.size() && !obs.empty(); ++i)
    {
        if (obs.at(i).x == neighbour_.x and obs.at(i).y == neighbour_.y)
        {
            // std::cout << "Cell cannot be accessed" << std::endl;
            inObs = true;
            break;
        }
    }

    return inObs;
}

bool Astar::isNeighbourInList(std::forward_list<Node>& lists, Node& neighbour_)
{
    bool inList = false;
    for (auto& list : lists)
    {
        if (list.x == neighbour_.x and list.y == neighbour_.y) 
        {
            inList = true;
            return inList;
        }
    }
    return inList;
}

bool Astar::isOutsideGrid(Node& neighbour_)
{
    if (neighbour_.x < 100 or neighbour_.x > 879 or neighbour_.y < 100 or neighbour_.y > 879)
    {
        return true;
    }
    return false;
}

bool Astar::isNeighbourFShorter(std::forward_list<Node>& lists, Node& neighbour_, double& F)
{
    bool isShorter = false;
    for (auto& list : lists)
    {
        if (list.x == neighbour_.x and list.y == neighbour_.y and F < list.F)
        {
            list.F = F;
            isShorter = true;
            return isShorter;
        }
    }
    
    return isShorter;
}