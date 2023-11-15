#pragma once 

#include <raylib.h>

struct Mouse
{
    
    explicit Mouse(){}

    void Update(){
        Coord = GetMousePosition();
    }

    Vector2& getCoord(){
        return Coord;
    }

    private:

        Vector2 Coord {-100.f, -100.f};
};
