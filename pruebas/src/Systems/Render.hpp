#pragma once

// CORE C++
#include <vector>

// Graphics library
#include <raylib.h>

//Own CLASSES
#include "../Handler/Entity.hpp"
#include "../Handler/GameEntities.hpp"
#include "../Player/Player.hpp"

#include <iostream>

struct Render_System
{
    
    void Update(GameEntities& game, Player& player){
        //ClearBackground(BLACK);
        
        if(player.isDrawing){
            DrawRectangleRec(player.rectSelection,WHITE);
        }
        for(auto& ent : game.getAllEntities()){
            ent->drawEntity();

        }
    }
};
