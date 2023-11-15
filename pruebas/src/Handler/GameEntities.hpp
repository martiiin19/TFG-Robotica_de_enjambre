#pragma once 

//OWN CLASSES
#include "Entity.hpp"


#include <vector>
#include <unordered_map>

#define MAX_ENTITIES_GAME 200

struct GameEntities
{
    GameEntities(){
        entities.reserve(MAX_ENTITIES_GAME);
    }

    std::vector<Entity*> getEntities(TypeEntity type){
        std::vector<Entity*> aux;
        for(auto& ent : entities){
            if(ent.getType() == type){
                aux.push_back(&(ent));
            }
        }
        return aux;
    }

   std::vector<Entity*> getCollisionEntity(){
        std::vector<Entity*> aux;
        for(auto& ent : entities){
            if(ent.getColision() == true){
                aux.push_back(&(ent));
            }
        }
        return aux;
    }

    std::vector<Entity>& getAllEntities(){
        return entities;
    }

    void InsertEntity(Entity&& ent){
        entities.emplace_back(ent);
    }

    void DeleteEntity(Entity ent){

    }

    private:
        std::vector<Entity> entities; // cambiarlo por un unordered_map y poneos por id el tipo de entidad
};