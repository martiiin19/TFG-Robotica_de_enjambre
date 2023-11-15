#pragma once 

#include "../Handler/Entity.hpp"

#include <array>
#include <vector>
#include <iostream>

#include "Input/Mouse.hpp"

//#include "Input/Keyboard.hpp"

#include "Formaciones.hpp"

struct Player
{
    explicit Player();

    void selectEntities(std::vector<Entity*> selecteds) noexcept;

    void deseleccionarEntidades() noexcept;
    
    void cambiarFormacion(Formaciones form) noexcept;

    int anyEntitySelected() noexcept;

    void moveEntity() noexcept;

    void moveAndFormation() noexcept;

    Mouse& getMouse(){
        return mouse;
    }

    int getSize(){
        return arraySeleccion.size();
    }

    bool isDrawing { false };
    Rectangle rectSelection {0,0,0,0};
    Vector2 startPos {0, 0};

    protected:
        //Functions
        void ESTANDAR(Vector2 coord) noexcept;
        void CIRCULO(Vector2 coord) noexcept;
        void TRIANGULO(Vector2 coord) noexcept;

    private:
        std::array<Entity*,20> arraySeleccion;
        Mouse mouse;
        
        
        
};