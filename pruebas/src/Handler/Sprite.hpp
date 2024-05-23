#pragma once 

#include <raylib.h>

struct Sprite
{
    explicit Sprite(){
        tex = LoadTexture("assets/animaciones/barracon.png");
    }

    void drawSprite(Vector2 vec){
        vec.x = vec.x -328/2;
        vec.y = vec.y -273/2 -15;
        DrawTexture(tex,vec.x,vec.y,WHITE);
    }

    Rectangle& getSprite(){
        return source;
    }

    private:
        Texture2D tex {};
        Rectangle source{};
};
