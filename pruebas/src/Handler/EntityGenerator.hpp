#pragma once 

#include <stdlib.h>

#include <raylib.h>

#include "GameEntities.hpp"

#include <vector>


#include "Soldier.hpp"
#include "Structure.hpp"
#include "../Player/Formaciones.hpp"

struct EntityGenerator
{
    explicit EntityGenerator(GameEntities&,Camera2D&);

    void CreateEntity(Vector2 pos,Vector2 vel,TypeEntity type, int bando) noexcept;

    void CreateEntities(int n) noexcept;

    void CreateEnemigos(int n) noexcept;

    void CreateStructure(float x, float y) noexcept;

    void CreateFormacionEnemigos(float x, float y, float rotacion, Formaciones form, int bando) noexcept;

    protected:
        //Functions
        Vector2 randomPosition() noexcept;

        //Formaciones
        void ESTANDAR(Vector2 coord,float rotacion, int bando) noexcept;
        void CIRCULO(Vector2 coord,float rotacion, int bando) noexcept;
        void TRIANGULO(Vector2 coord,float rotacion, int bando) noexcept;
        void LINEA(Vector2 coord,float rotacion, int bando) noexcept;

        //Variables
        int id_iteration{0};

    private:
        //Variables
        GameEntities& ents;
        Camera2D& camera;
        
};
