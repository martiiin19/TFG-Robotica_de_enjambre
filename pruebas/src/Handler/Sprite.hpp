#pragma once 

#include <raylib.h>

struct Sprite
{
    explicit Sprite(){
        tex = LoadTexture("assets/animaciones/Characters/Civilian1_Idle.png");
        source = { 15.0f, 15.0f, (float)tex.width/4, (float)tex.height/2 };
    }

    void drawSprite(Vector2 vec){
        vec.x = vec.x -source.width/4;
        vec.y = vec.y -source.height/4;
        DrawTextureRec(tex,source,vec,WHITE);
    }

    Rectangle& getSprite(){
        return source;
    }

    private:
        Texture2D tex {};
        Rectangle source{};
};
