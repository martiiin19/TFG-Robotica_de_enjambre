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
    
    void Update(GameEntities& game, Player& player, int version = 0){
        //ClearBackground(BLACK);
        
        if(player.isDrawing){
            DrawRectangleRec(player.rectSelection,Fade(WHITE,0.5f));
        }
        
        for(auto& ent : game.getAllEntities()){
            if(version == 0){
                ent->drawEntity();
            }else{
                
                DrawRectangleV(ent->getPosition(),{60,60},RED);
            }
            

        }
    }
};
