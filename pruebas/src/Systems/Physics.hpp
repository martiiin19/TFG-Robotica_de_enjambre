#pragma once 

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Handler/GameEntities.hpp"

struct Physics_System
{
    
    void Update(GameEntities& game){
        for(auto& ent : game.getEntities(TypeEntity::SOLDIER)){
            
            ent->Update();
        }
    }

};
