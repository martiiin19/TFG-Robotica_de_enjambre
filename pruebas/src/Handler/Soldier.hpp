#pragma once 

#include "Entity.hpp"

struct Soldier : public Entity {

    explicit Soldier (int pID,TypeEntity pTYPE = TypeEntity::STRUCTURE, Vector2 pPOS = {0.0, 0.0}, Vector2 pDEST = {0.0, 0.0}, Vector2 pVEL = {0.0, 0.0}, Vector2 pSIZE = {25,25}, int bando = 0) : Entity(pID,pTYPE,pPOS,pSIZE,bando) {
        setDestination(pDEST);
        setRepulsion({0,0});
        if(bando == 1){
            att = Attitude::DEFENSIVA;
        }
        
        daño = 20;

        for(auto& fuerza : fuerzas){
            fuerza.x = 0;
            fuerza.y = 0;
        }
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
        //SetPosition
        setPosition(fuerzas);
    }

    void calcularFuerzas(Camera2D& camera){
        for(int i = 0; i<fuerzas.size(); i++){
             // Calcula el vector de dirección hacia el destino
            float direccion_x = destination[i].x - getPosition().x;
            float direccion_y = destination[i].y - getPosition().y;

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
                case 2:

                    break;
            }
        }
       
    }


    void actualizarAtaque(Camera2D& camera){
        
        float m = (getPosition().y - enemigo->getPosition().y)/(getPosition().x-enemigo->getPosition().x);
        float b = getPosition().y - m*getPosition().x;

        float h = enemigo->getPosition().x;
        float k = enemigo->getPosition().y;

        Vector2 pos1,pos2;

        float A = 1+m*m;
        float B = (2*m*(b-k)-2*h);
        float C = h*h+(b-k)*(b-k)-DISTANCIA_DE_ATAQUE*DISTANCIA_DE_ATAQUE;


        float discriminante = B*B-4*A*C;

        pos1.x = (-B+std::sqrt(discriminante))/(2*A);
        pos1.y = m*pos1.x + b;

        pos2.x = (-B-std::sqrt(discriminante))/(2*A);
        pos2.y = m*pos2.x + b;

        DrawCircleV(GetWorldToScreen2D(pos1,camera),3,WHITE);
        DrawCircleV(GetWorldToScreen2D(pos2,camera),3,WHITE);
        DrawCircleV(GetWorldToScreen2D(enemigo->getPosition(),camera),10,GREEN);

        if(getPosition().y > enemigo->getPosition().y && getPosition().x > enemigo->getPosition().x){
            setDestination(pos1);
        }else if(getPosition().y > enemigo->getPosition().y && getPosition().x < enemigo->getPosition().x){
            setDestination(pos2);
        }else if(getPosition().y < enemigo->getPosition().y && getPosition().x > enemigo->getPosition().x){
            setDestination(pos1);
        }else{
            setDestination(pos2);
        }
    }

    void Atacar(Entity* e, bool o = false){
        if(o == false){
            att = Attitude::OFENSIVA;
            enemigo = e;
        }else if(o == true && std::abs(getPosition().x - destination[0].x) < VEL_SOLDIER && std::abs(getPosition().y - destination[0].y) < VEL_SOLDIER){
            att = Attitude::OFENSIVA;
            enemigo = e;
        }
        
    }
   
    void Update(Camera2D& camera) override{
        if(enemigo != nullptr){
            actualizarAtaque(camera);
        }
        if(std::abs(getPosition().x - destination[0].x) > VEL_SOLDIER || std::abs(getPosition().y - destination[0].y) > VEL_SOLDIER){
            
            calcularFuerzas(camera);
            mover();
            setRectangle();
            
        }else if(destination[1].x!=0 && destination[1].y!=0){
            DrawLineV(GetWorldToScreen2D(getPosition(),camera),GetWorldToScreen2D(destination[1],camera),BLUE);
            setDestination(destination[1]);
        }
           
        DrawLineV(GetWorldToScreen2D(getPosition(),camera),GetWorldToScreen2D(destination[0],camera),RED);
        //std::cout << position.x << "<=>" << position.y << std::endl;
        
    }

   


    Attitude getAttitude(){
        return att;
    }

    void setAttitude(Attitude a){
        att = a;
    }

    bool isSelected(){
        return selected;
    }

    void changeSelected(bool state){
        selected = state;
    }

    

    void setEnemigo(){
        enemigo = nullptr;
    }

    Entity* getEnemigo(){
        return enemigo;
    }


    private:
        std::array<Vector2,3> destination;
        std::array<Vector2,3> fuerzas;
        bool selected {false};
       
        Attitude att { Attitude::INDEFINIDA };
        Entity* enemigo{nullptr};

        int vida{100};
        int daño;
};