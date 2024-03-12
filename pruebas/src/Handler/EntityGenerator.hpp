#pragma once 

#include <stdlib.h>

#include <raylib.h>

#include "GameEntities.hpp"

#include <vector>

#include "Entity.hpp"

struct EntityGenerator
{
    explicit EntityGenerator(GameEntities&,Camera2D&);

    void CreateEntity(Vector2 pos,Vector2 vel,TypeEntity type) noexcept;

    void CreateEntities(int n) noexcept;

    void CreateEnemigos(int n) noexcept;

    void CreateStructure(float x, float y) noexcept;

    protected:
        //Functions
        Vector2 randomPosition() noexcept;

        //Variables
        int id_iteration{0};

    private:
        //Variables
        GameEntities& ents;
        Camera2D& camera;
        
};
