#pragma once 

#include <raylib.h>

struct Sprite
{
    explicit Sprite(){
        tex = LoadTexture("assets/Characters/Civilian1_Idle.png");
        source = { 0.0f, 0.0f, (float)tex.width/4, (float)tex.height/2 };
    }

    void drawSprite(Vector2 vec){
        DrawTextureRec(tex,source,vec,WHITE);
    }

    private:
        Texture2D tex {};
        Rectangle source{};
};
