#pragma once 

#include <raylib.h>

#include "TypeEntity.hpp"

#include <cmath>

#include "Sprite.hpp"

#include "../Macros.hpp"

#include <stdlib.h>

#include <iostream>

#define MAGNITUD_REPULSION 1.0f
#define MAGNITUD_VELOCIDAD 1.0f

struct Entity
{
    explicit Entity(int pID, TypeEntity pTYPE = TypeEntity::SOLDIER, Vector2 pPOS = {0.0, 0.0}, Vector2 pDEST = {0.0, 0.0}, Vector2 pVEL = {0.0, 0.0}, Vector2 pSIZE = {25,25}) : 
    id(pID), type(pTYPE), destination(pDEST), velocities(pVEL), position(pPOS) {
        setDestination(pDEST);
        if(type == TypeEntity::SOLDIER){
            color = RED;
        }else{
            color = MAROON;
        }
        rect = {position.x, position.y, pSIZE.x, pSIZE.y};
    }

    int getID(){
        return id;
    }
    
    //Funciones para modificar los vectores

    
    Vector2 getPosition(){
        Vector2 pos;
        pos.x = rect.x + rect.width / 2;
        pos.y = rect.y + rect.height / 2;
        return pos;
    }

    Vector2& getVelocity(){
        return velocities;
    }

    Vector2 getDestination(){
        return destination;
    }

    void setVelocity(Vector2 vel){
        velocities.x += vel.x;
        velocities.y += vel.y;
    }

    void setRepulsion(float aux){
        repulsion = {static_cast<float>((velocities.x*MAGNITUD_REPULSION) + MAGNITUD_REPULSION*cos(aux)), // X
                    static_cast<float>((velocities.y*MAGNITUD_REPULSION) + MAGNITUD_REPULSION*sin(aux))}; // Y
    }

    bool getSTC(){
        return stc;
    }

    void setSTC(bool aux){
        stc = aux;
    }

    void setDestination(Vector2 dest){
        destination.x = dest.x;
        destination.y = dest.y;
        
        float deltaX = destination.x - position.x;
        float deltaY = destination.y - position.y;
        float distancia = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    
        if (distancia > 0) {
            velocities.x = (deltaX / distancia) * VEL_SOLDIER;
            velocities.y = (deltaY / distancia) * VEL_SOLDIER;
        }else{
            velocities.x = 0.f;
            velocities.y = 0.f;
        }   
        
        
    }
   
    void Update(){
        // Ángulo y magnitud de la repulsión
        if(std::abs(position.x - destination.x) > VEL_SOLDIER || std::abs(position.y - destination.y) > VEL_SOLDIER){
            if(stc){
                position = {position.x + repulsion.x, position.y + repulsion.y};
            }else{
                position = {position.x + velocities.x, position.y + velocities.y};
            }
            rect.x = position.x;
            rect.y = position.y;
        }
        
    }

    void UpdateCollision(Vector2 mouse){
        colision = false;
        if(CheckCollisionPointRec(mouse,rect)){
            colision = true;
        }
    }

    void UpdateRecColision(Rectangle& rec){
        colision = false;
        if(CheckCollisionRecs(rec,rect)){
            colision = true;
        }
    }

    bool getColision(){
        return colision;
    }

    void drawEntity(){
        //DrawRectangleRec(rect,color);
        spr.drawSprite(position);
    }

    Rectangle& getRectangle(){
        return rect;
    }

    TypeEntity& getType(){
        return type;
        // Antes de poner Spri
    }

    bool isSelected(){
        return selected;
    }

    void changeSelected(bool state){
        selected = state;
        if(state){
            color = GREEN;
        }else{
            color = RED;
        }
        
    }

    private:
        int id;
        TypeEntity type;
        Vector2 destination {0.0, 0.0};
        Vector2 velocities {0.0, 0.0};  // Probablemente hay que cambiarlo a un vector de la libreria raylib
        Vector2 repulsion {0.0, 0.0};
        Vector2 position {0.0, 0.0};  // Probablemente hay que cambiarlo a un vector de la libreria raylib
        bool selected {false};
        bool colision {false};
        bool stc {false};

        Sprite spr {};

        // Antes de poner Sprite
        Rectangle rect {0,0,0,0};
        Color color { RED };
};


