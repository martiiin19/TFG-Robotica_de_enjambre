#pragma once 

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Handler/GameEntities.hpp"

struct DeadLine_System
{
    void Update(GameEntities& game,Camera2D& camera){
        unsigned int cont = 0;
        int aux = -1;  
        for(auto& ent : game.getAllEntities()){
            if(ent->vida <= 0){
                ent->~Entity();
                aux = cont; 
            }
            cont++;
        }
        if(aux > -1){
            game.getAllEntities().erase(game.getAllEntities().begin() + aux);
        }
    }
};
