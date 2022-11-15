# AStar Algorithm
This is an AStar algorithm that finds the shortest path from a start position to goal position. It was implemented in C++ using the SDL library for graphic display.

# Setup
Install dependencies
```
sudo apt install libsdl2-dev libsdl2-ttf-dev
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
![AStar Algorithm](https://github.com/siksal/a-star/blob/master/AStar%20picture.png)

# Hint
- ![#2c2c2c](https://placehold.co/15x15/2c2c2c/2c2c2c.png) `Obstacle`
- ![#ffff00](https://placehold.co/15x15/ffff00/ffff00.png) `Start`
- ![#00ff00](https://placehold.co/15x15/00ff00/00ff00.png) `Goal`
- ![#0000ff](https://placehold.co/15x15/0000ff/0000ff.png) `Path`

- Press mouse button to create or remove obstacle.
- Press S and mouse button to change start position.
- Press G and mouse button to change goal position.
- Blue color is the shortest path from Start to Goal.