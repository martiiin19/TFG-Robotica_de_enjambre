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

#define FACTOR_DESTINO 3
#define FACTOR_REPULSION 1.5

struct Entity
{
    explicit Entity(int pID, TypeEntity pTYPE = TypeEntity::SOLDIER, Vector2 pPOS = {0.0, 0.0}, Vector2 pDEST = {0.0, 0.0}, Vector2 pVEL = {0.0, 0.0}, Vector2 pSIZE = {25,25}) : 
    id(pID), type(pTYPE), position(pPOS) {
        setDestination(pDEST);
        setRepulsion({0,0});
        if(type == TypeEntity::SOLDIER){
            //color = RED;
            att = Attitude::PASIVA;
        }else{
            //color = MAROON;
            att = Attitude::INDEFINIDA;
        }
        for(auto& fuerza : fuerzas){
            fuerza.x = 0;
            fuerza.y = 0;
        }
        rect = {position.x, position.y, pSIZE.x, pSIZE.y};
    }

    int getID(){
        return id;
    }
    
    //Funciones para modificar los vectores
    Vector2 getPosition(){
        Vector2 pos;
        pos.x = position.x;
        pos.y = position.y;
        return pos;
    }

    Vector2& getVelocity(){
        return fuerzas[0];
    }

    Vector2 getDestination(){
        return destination[0];
    }

    void setVelocity(Vector2 f){
        fuerzas[0].x += f.x;
        fuerzas[0].y += f.y;
    }

    void setDestination(Vector2 dest){
        destination[0].x = dest.x;
        destination[0].y = dest.y;
    }

    void setRepulsion(Vector2 rep){
        destination[1].x = rep.x;
        destination[1].y = rep.y;
    }

    void mover(){
        position.x += fuerzas[0].x + fuerzas[1].x;
        position.y += fuerzas[0].y + fuerzas[1].y;
    }

    void calcularFuerzas(Camera2D& camera){
        for(int i = 0; i<fuerzas.size(); i++){
             // Calcula el vector de dirección hacia el destino
            float direccion_x = destination[i].x - position.x;
            float direccion_y = destination[i].y - position.y;

            // Calcula la magnitud del vector de dirección
            float magnitud = std::sqrt(direccion_x * direccion_x + direccion_y * direccion_y);

            // Calcula el vector de fuerza basado en la dirección y el factor
            switch (i){
                case 0:
                    fuerzas[i].x = direccion_x / magnitud * FACTOR_DESTINO;
                    fuerzas[i].y = direccion_y / magnitud * FACTOR_DESTINO;
                    
                    break;
                case 1:
                    if(destination[i].x == 0 && destination[i].y ==0){
                        fuerzas[i].x = 0;
                        fuerzas[i].y = 0;
                    }else{
                        fuerzas[i].x = direccion_x / magnitud * FACTOR_REPULSION;
                        fuerzas[i].y = direccion_y / magnitud * FACTOR_REPULSION;
                        
                    }
                    break;
            }
        }
       
    }
   
    void Update(Camera2D& camera){
        if(std::abs(position.x - destination[0].x) > VEL_SOLDIER || std::abs(position.y - destination[0].y) > VEL_SOLDIER){
            calcularFuerzas(camera);
            mover();
            rect.x = position.x;
            rect.y = position.y;
        }
        DrawLineV(GetWorldToScreen2D(getPosition(),camera),GetWorldToScreen2D(destination[0],camera),RED);
        if(destination[1].x!=0 && destination[1].y!=0){
            DrawLineV(GetWorldToScreen2D(getPosition(),camera),GetWorldToScreen2D(destination[1],camera),BLUE);
        }
        //std::cout << position.x << "<=>" << position.y << std::endl;
        
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
        
        if(type == TypeEntity::STRUCTURE){
            DrawPixelV(position,WHITE);
            DrawCircleLines(position.x,position.y,70,GREEN);
        }else{
            spr.drawSprite(position);
        }
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
    }

    private:
        int id;
        TypeEntity type;
        std::array<Vector2,2> destination;
        std::array<Vector2,2> fuerzas;
        Vector2 position {0.0, 0.0};  // Probablemente hay que cambiarlo a un vector de la libreria raylib
        bool selected {false};
        bool colision {false};
        Attitude att { Attitude::INDEFINIDA };

        Sprite spr {};

        // Antes de poner Sprite
        Rectangle rect {0,0,0,0};
        Color color { RED };
};


