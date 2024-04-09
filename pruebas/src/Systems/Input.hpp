#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

#include <iostream>

#define VELOCIDAD_CAMARA 1

struct Input_System
{

    void Update(GameEntities& entities, Player& player, Camera2D& camera){
        player.getMouse().Update();
        //std::cout << "X: " << GetScreenToWorld2D(player.getMouse().getCoord(),camera).x << " Y: " << GetScreenToWorld2D(player.getMouse().getCoord(),camera).y << std::endl;

        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();
        // Seleccionar una entidad
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(!entities.getCollisionEntity().empty()){
                player.selectEntities(entities.getCollisionEntity());
            }else{
                player.deseleccionarEntidades();
            }
        }
        // Cambiar el destino de la entidad
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if(player.getMouse().getColision() == true && player.getMouse().getEnt()->getBando()!=0){
                player.atacar();
                
            }else{
                if(player.anyEntitySelected() == 1){
                    player.moveEntity(GetScreenToWorld2D(player.getMouse().getCoord(),camera));
                }else if(player.anyEntitySelected() > 1){
                    player.moveAndFormation(GetScreenToWorld2D(player.getMouse().getCoord(),camera));
                }
            }
            
        }
        // Seleccionar varias entidades
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && currentGesture == GESTURE_DRAG){
            if (!player.isDrawing) {
                // Comienza a dibujar el rectángulo cuando se presiona el botón izquierdo del ratón
                player.rectSelection.x = GetScreenToWorld2D(player.getMouse().getCoord(),camera).x;
                player.rectSelection.y = GetScreenToWorld2D(player.getMouse().getCoord(),camera).y;
                player.isDrawing = true;
            }
            else {
                // Actualiza el tamaño del rectángulo mientras se arrastra el ratón
                player.rectSelection.width = GetScreenToWorld2D(player.getMouse().getCoord(),camera).x- player.rectSelection.x;
                player.rectSelection.height = GetScreenToWorld2D(player.getMouse().getCoord(),camera).y - player.rectSelection.y;
            }
        }else if (player.isDrawing){
            player.selectEntities(entities.getCollisionEntity());
            player.isDrawing = false;
            player.rectSelection.width = 0;
            player.rectSelection.height = 0;
        }
        
        if(IsKeyPressed(KEY_Q)){
            player.cambiarFormacion(Formaciones::ESTANDAR);
        }

        if(IsKeyPressed(KEY_W)){
            player.cambiarFormacion(Formaciones::CIRCULO);
        }

        if(IsKeyPressed(KEY_E)){
            player.cambiarFormacion(Formaciones::TRIANGULO);
        }

        if(IsKeyPressed(KEY_R)){
            player.cambiarFormacion(Formaciones::LINEA);
        }

        if(IsKeyPressed(KEY_A)){
            player.cambiarActitud(Attitude::OFENSIVA);
        }

        if(IsKeyPressed(KEY_S)){
            player.cambiarActitud(Attitude::DEFENSIVA);
        }

        if(IsKeyPressed(KEY_D)){
            player.cambiarActitud(Attitude::PASIVA);
        }

        // esto es para movernos de momento con la camara se cambiara en un futuro 
        if (IsKeyDown(KEY_RIGHT)) {
            camera.target.x += 10.0f;
        }
        if (IsKeyDown(KEY_LEFT)) {
            camera.target.x -= 10.0f;
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera.target.y += 10.0f;
        }
        if (IsKeyDown(KEY_UP)) {
            camera.target.y -= 10.0f;
        }
        //std::cout << camera.target.x << " : " << camera.target.y << std::endl; 
    }

    private:
        int currentGesture { GESTURE_NONE };
        int lastGesture { GESTURE_NONE };
        
};
