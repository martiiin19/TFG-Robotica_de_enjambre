#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"


struct Attitude_System
{

    float calculateDistanceBetweenPoints(Vector2 p1,Vector2 p2){
        return std::sqrt(std::pow(p2.x-p1.x,2) + std::pow(p2.y-p1.y,2));
    }

    void actitudOfensiva(GameEntities& game,Entity* ent){
        for(auto* e :game.getEntities(TypeEntity::SOLDIER)){
            if(e != ent){
                if(e->getBando() != ent->getBando() && calculateDistanceBetweenPoints(e->getPosition(),ent->getPosition()) < 40 && ent->getEnemigo()==nullptr){
                    ent->Atacar(e);
                }
            }
        }
    }

    void actitudDefensiva(){
        // si te tiene fijado marcarlo como objetivo
    }

    void Update(GameEntities& game, Player& player,Camera2D& camera){
        for(auto* ent : game.getEntities(TypeEntity::SOLDIER)){
            switch (ent->getAttitude())
            {
            case Attitude::OFENSIVA:
                actitudOfensiva(game,ent);
                break;
            case Attitude::DEFENSIVA:
                actitudDefensiva();
                break;
            case Attitude::PASIVA:
                break;
            default:
                break;
            }
        }
    }
};
