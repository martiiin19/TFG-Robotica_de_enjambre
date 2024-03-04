#pragma once 

#include <raylib.h>

struct Mouse
{
    
    explicit Mouse(){}

    void Update(){
        Coord = GetMousePosition();
        DrawCircleV(Coord,10,PURPLE);
        //if(ent != nullptr){
        //    std::cout << colision<< " : "<< ent->getID() << std::endl;
        //}  
    }

    Vector2& getCoord(){
        return Coord;
    }

    void setColision(bool flag, Entity* e){
        colision =flag;
        ent = e;
       
    }

    bool getColision(){
        return colision;
    }

    Entity* getEnt(){
        return ent;
    }

    private:
        bool colision{false};
        Entity* ent{nullptr};
        Vector2 Coord {-100.f, -100.f};
};
