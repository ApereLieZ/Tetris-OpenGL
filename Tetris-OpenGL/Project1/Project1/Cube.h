#ifndef Board_h
#define Board_h

#include "Shape.h"

namespace TetrisGame
{
    // Клас, який відповідає за малювання дошки (поля гри)
    class Cube : public Shape
    {
    public:
        Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { }
        virtual void draw();
    };

}
#endif

