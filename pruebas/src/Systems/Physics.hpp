#pragma once 

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Handler/GameEntities.hpp"

struct Physics_System
{
    
    void Update(GameEntities& game,Camera2D& camera){
        for(auto& ent : game.getEntities(TypeEntity::SOLDIER)){
            
            ent->Update(camera);
        }
    }

};
