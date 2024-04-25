#pragma once 

//#include "../Handler/Entity.hpp"
#include "../Handler/Soldier.hpp"

#include <array>
#include <vector>
#include <iostream>

#include "Input/Mouse.hpp"

//#include "Input/Keyboard.hpp"

#include "Formaciones.hpp"

struct Player
{
    explicit Player(Camera2D& camera);

    void selectEntities(std::vector<Entity*> selecteds) noexcept;

    void deseleccionarEntidades() noexcept;

    void cambiarActitud(Attitude att) noexcept;

    void cambiarFormacion(Formaciones form) noexcept;

    void atacar() noexcept;
    
    void hacerFormacion() noexcept;

    int anyEntitySelected() noexcept;

    void moveEntity(Vector2 coords) noexcept;

    void moveAndFormation(Vector2 coords) noexcept;


    Mouse& getMouse(){
        return mouse;
    }

    int getSize(){
        return arraySeleccion.size();
    }

    bool isDrawing { false };
    Rectangle rectSelection {0,0,0,0};
    Vector2 startPos {0, 0};
    float angleOfFormation {0};
    float angleOfFormationAux{0};
    bool inFormation {false};
    Vector2 positionFormation;
    Vector2 positionFormationAux;

    protected:
        //Functions
        void ESTANDAR(Vector2 coord) noexcept;
        void CIRCULO(Vector2 coord) noexcept;
        void TRIANGULO(Vector2 coord) noexcept;
        void LINEA(Vector2 coord) noexcept;

    private:
        std::array<Entity*,20> arraySeleccion;
        Mouse mouse;
        Formaciones formation{Formaciones::ESTANDAR};
        Camera2D& cam;
};
