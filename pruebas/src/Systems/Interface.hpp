#pragma once 

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

struct Interface_System
{
     explicit Interface_System(){
        hudDown = LoadTexture("assets/interfaz/hudDown.png");
    }

    void Update(GameEntities& game,Camera2D& camera,Player& player){
        DrawTextureRec(hudDown,source,{0,GetScreenHeight()-200.f},WHITE);
        
    }

    private:
        Texture2D hudDown;
        Rectangle source {0,GetScreenHeight()-200,GetScreenWidth(),200};
};
