#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

struct Colisions_System
{

    float calculateDistanceBetweenPoints(Vector2 p1,Vector2 p2){
        return std::sqrt(std::pow(p2.x-p1.x,2) + std::pow(p2.y-p1.y,2));
    }

    void updateColisionsToSelectEntities(Entity* ent,Player& player) noexcept{
         ent->UpdateCollision(player.getMouse().getCoord());
            if(player.rectSelection.width != 0 && player.rectSelection.height != 0){
                ent->UpdateRecColision(player.rectSelection);
            }   
    }

    

    void updateColisionsWithStructures(Entity* ent,GameEntities& game){
        for(auto& stc : game.getEntities(TypeEntity::STRUCTURE)){
            if(calculateDistanceBetweenPoints(ent->getPosition(),stc->getPosition()) < 70){
                float angulo_repulsion = atan2(ent->getPosition().y - stc->getPosition().y, ent->getPosition().x - stc->getPosition().x);
                ent->setRepulsion(angulo_repulsion);
                ent->setSTC(true);
            }else if(ent->getSTC()){
                ent->setSTC(false);
                ent->setDestination(ent->getDestination());
            }
        }
    }
    
    void Update(GameEntities& game, Player& player){
        for(auto& ent : game.getEntities(TypeEntity::SOLDIER)){
            updateColisionsToSelectEntities(ent,player); 
            updateColisionsWithStructures(ent,game);
        }
    }
};
