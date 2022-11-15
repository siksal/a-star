# AStar Algorithm
This is an AStar algorithm that finds the shortest path from a start position to goal position. It was implemented in C++ using the SDL library for graphic display.

# Setup
Install dependencies
```
sudo apt install libeigen3-dev libsdl2-dev libsdl2-ttf-dev
```
Clone the repository
```
git clone https://github.com/siksal/a-star.git
```
Build the code
```
cd a-star/build
cmake ../
```
Compile the code
```
make
```
Run the code
```
./a-star
```
![AStar Algorithm](https://github.com/siksal/a-star/blob/master/AStar\picture.png)

# Hint
- ![#2C2C2C](https://placehold.co/15x15/f03c15/2C2C2C.png) `Obstacle`
- ![#FFFF00](https://placehold.co/15x15/f03c15/FFFF00.png) `Start`
- ![#00FF00](https://placehold.co/15x15/f03c15/00FF00.png) `Goal`
- ![#0000FF](https://placehold.co/15x15/f03c15/0000FF.png) `Path`

- Press mouse button to create or remove obstacle.
- Press S and mouse button to change start position.
- Press G and mouse button to change goal position.
- Blue color is the shortest path from Start to Goal.