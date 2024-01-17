#include "EntityGenerator.hpp"

//Functions{
    Vector2 EntityGenerator::randomPosition() noexcept{
        Vector2 aux = {static_cast<float>(std::rand() % 1500 + 200), static_cast<float>(std::rand() % 700 + 100)};
        return aux;
    }
//}

EntityGenerator::EntityGenerator(GameEntities& game,Camera2D& cam) : ents{game},camera{cam} {}

void EntityGenerator::CreateEntity(Vector2 pos = {0.0,0.0},Vector2 vel = {0.0,0.0}, TypeEntity type = TypeEntity::SOLDIER) noexcept{
    Entity* ent = new Entity(id_iteration,type,pos,pos,vel,{W_SOLDIER,H_SOLDIER});
    ents.InsertEntity(ent);
    id_iteration++;
}


void EntityGenerator::CreateEntities(int n) noexcept{

    for(int i = 0; i<n; i++){
        Vector2 pos {randomPosition()};
        Entity* ent = new Entity(id_iteration,TypeEntity::SOLDIER,pos,pos,{0.0,0.0},{W_SOLDIER,H_SOLDIER});
        ents.InsertEntity(ent);
        id_iteration++;
    }
}
