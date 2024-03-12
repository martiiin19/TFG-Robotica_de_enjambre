#pragma once

#include "Entity.hpp"

struct Structure : public Entity
{
    explicit Structure(int pID,TypeEntity pTYPE = TypeEntity::STRUCTURE, Vector2 pPOS = {0.0, 0.0}, Vector2 pSIZE = {25,25},int bando = 0) : Entity(pID,pTYPE,pPOS,pSIZE,bando) {

    }

    void Update(Camera2D& camera) override{

    }

    private:

};
