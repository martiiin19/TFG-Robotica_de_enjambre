#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"


struct Input_System
{

    void Update(GameEntities& entities, Player& player){
        player.getMouse().Update();

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
            if(player.anyEntitySelected() == 1){
                player.moveEntity();
            }else if(player.anyEntitySelected() > 1){
                player.moveAndFormation();
            }
        }
        // Seleccionar varias entidades
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && currentGesture == GESTURE_DRAG){
            if (!player.isDrawing) {
                // Comienza a dibujar el rectángulo cuando se presiona el botón izquierdo del ratón
                player.rectSelection.x = player.getMouse().getCoord().x;
                player.rectSelection.y = player.getMouse().getCoord().y;
                player.isDrawing = true;
            }
            else {
                // Actualiza el tamaño del rectángulo mientras se arrastra el ratón
                player.rectSelection.width = player.getMouse().getCoord().x - player.rectSelection.x;
                player.rectSelection.height = player.getMouse().getCoord().y - player.rectSelection.y;
            }
        }else if (player.isDrawing){
            player.selectEntities(entities.getCollisionEntity());
            player.isDrawing = false;
            player.rectSelection.width = 0;
            player.rectSelection.height = 0;
        }


    }

    private:
        int currentGesture { GESTURE_NONE };
        int lastGesture { GESTURE_NONE };
        
};
