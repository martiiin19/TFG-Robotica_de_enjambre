#pragma once 

#include <raylib.h>

#include "TypeEntity.hpp"

#include "Attitude.hpp"

#include <cmath>

#include "Sprite.hpp"

#include "../Macros.hpp"

#include <stdlib.h>

#include <iostream>

#include <array>

#define FACTOR_DESTINO 2.4
#define FACTOR_REPULSION 2.2
#define DISTANCIA_DE_ATAQUE 20



struct Entity
{
    explicit Entity(int pID, TypeEntity pTYPE = TypeEntity::SOLDIER, Vector2 pPOS = {0.0, 0.0},Vector2 pSIZE = {25,25}, int bando = 0,int v = 100,int d = 25) : 
    id(pID), type(pTYPE), position(pPOS),tipo(bando),vida(v),daño(d) {
         
        
        rect = {position.x-W_SOLDIER/2, position.y-H_SOLDIER/2, pSIZE.x, pSIZE.y};
    }

    virtual void Update(Camera2D& camera) = 0;
    virtual void drawEntity() = 0;
    //virtual ~Entity() = default;

    int getID(){
        return id;
    }
    
    //Funciones para modificar los vectores
    Vector2 getPosition(){
        return position;
    }

    void setPosition(std::array<Vector2,2>& fuerzas){
        position.x += fuerzas[0].x + fuerzas[1].x;
        position.y += fuerzas[0].y + fuerzas[1].y;
    }

    void setRectangle(){
        rect.x = position.x-W_SOLDIER/2;
        rect.y = position.y-H_SOLDIER/2;
    }

   

    bool UpdateCollision(Vector2 mouse){
        colision = false;
        if(CheckCollisionPointRec(mouse,getRectangle())){
            colision = true;
        }
        return colision;
    }

    void UpdateRecColision(Rectangle& rec){
        colision = false;
        if(CheckCollisionRecs(rec,getRectangle())){
            colision = true;
        }
    }

    bool getColision(){
        return colision;
    }

    Rectangle& getRectangle(){
        return rect;
    }

    TypeEntity& getType(){
        return type;
        // Antes de poner Spri
    }

    int getBando(){
        return tipo;
    }

    Sprite getSprite(){
        return spr;
    }
   
    int vida{100};
    int daño;
    bool markForDie{false};

    private:
        int id;
        int tipo{0};//si es del jugador o de la maquina si es 0 player
        TypeEntity type;
        Vector2 position {0.0, 0.0};
        bool colision {false};
        Sprite spr {};
        

        // Antes de poner Sprite
        Rectangle rect {0,0,0,0};
        Color color { RED };
};


