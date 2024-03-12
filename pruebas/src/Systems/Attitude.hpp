#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

#define DISTANCIA_DETECCION_OFENSIVA 100
#define DISTANCIA_DETECCION_DEFENSIVA 40


struct Attitude_System
{

    float calculateDistanceBetweenPoints(Vector2 p1,Vector2 p2){
        return std::sqrt(std::pow(p2.x-p1.x,2) + std::pow(p2.y-p1.y,2));
    }

    void actitudOfensiva(GameEntities& game,Entity* ent){
        for(auto* e :game.getEntities(TypeEntity::SOLDIER)){
            if(e != ent){
                if(e->getBando() != ent->getBando() && calculateDistanceBetweenPoints(e->getPosition(),ent->getPosition()) < DISTANCIA_DETECCION_OFENSIVA && static_cast<Soldier*>(ent)->getEnemigo()==nullptr){
                    static_cast<Soldier*>(ent)->Atacar(e,true);
                }
            }
        }
    }

    void actitudDefensiva(GameEntities& game, Entity* ent){
        for(auto* e : game.getEntities(TypeEntity::SOLDIER)){
            if(e != ent){
                if(e->getBando() != ent->getBando() && static_cast<Soldier*>(e)->getEnemigo() == ent && calculateDistanceBetweenPoints(e->getPosition(),ent->getPosition()) < DISTANCIA_DETECCION_DEFENSIVA){
                    static_cast<Soldier*>(ent)->Atacar(e,true);
                }
            }
        }
    }

    void Update(GameEntities& game, Player& player,Camera2D& camera){
        for(auto* ent : game.getEntities(TypeEntity::SOLDIER)){
            switch (static_cast<Soldier*>(ent)->getAttitude())
            {
            case Attitude::OFENSIVA:
                actitudOfensiva(game,ent);
                break;
            case Attitude::DEFENSIVA:
                actitudDefensiva(game, ent);
                break;
            case Attitude::PASIVA:
                break;
            default:
                break;
            }
        }
    }
};
