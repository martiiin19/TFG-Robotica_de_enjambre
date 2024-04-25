#include "Player.hpp"


Player::Player(Camera2D& camera) : cam{camera} {
    for(unsigned int i = 0; i<arraySeleccion.size(); i++){
        arraySeleccion[i] = nullptr;
    }
}

void Player::selectEntities(std::vector<Entity*> selecteds) noexcept{
    //Hacer cuadrado de seleccion y seleccionar las entidades
    deseleccionarEntidades();
    unsigned int i = 0;
    for(auto& ent : selecteds){
        if(i < arraySeleccion.size()){
            static_cast<Soldier*>(ent)->changeSelected(true);
            arraySeleccion[i] = ent;
            i++;
        }
    }
}

void Player::deseleccionarEntidades() noexcept{
    for(unsigned int i = 0; i<arraySeleccion.size(); i++){
        if(arraySeleccion[i] != nullptr){
            static_cast<Soldier*>(arraySeleccion[i])->changeSelected(false);
            arraySeleccion[i] = nullptr;
        }
        
    }
}

int Player::anyEntitySelected() noexcept{
    int aux = 0;
    for (auto* elemento : arraySeleccion) {
        if (elemento != nullptr) {
            aux++;  // Al menos un elemento no es nullptr
        }
    }
    return aux;
}

void Player::atacar() noexcept{
    for(auto* ent : arraySeleccion){
        if(ent!=nullptr){
            static_cast<Soldier*>(ent)->Atacar(mouse.getEnt());
        }   
    }
}

void Player::moveEntity(Vector2 coords) noexcept{
    if(arraySeleccion[0] != nullptr){
        //Vector2 aux = {coords.x - W_SOLDIER/2,coords.y -H_SOLDIER/2};
        static_cast<Soldier*>(arraySeleccion[0])->setDestination(coords);
        static_cast<Soldier*>(arraySeleccion[0])->setEnemigo();
    }
}

void Player::moveAndFormation(Vector2 coords) noexcept{
    for(auto* ent : arraySeleccion){
        if(ent != nullptr){
            static_cast<Soldier*>(ent)->setEnemigo();
        }
    }
    positionFormationAux = positionFormation;
    positionFormation = coords;
    hacerFormacion();
}

void Player::cambiarActitud(Attitude att) noexcept{
    for(auto* ent : arraySeleccion){
        if(ent != nullptr){
            static_cast<Soldier*>(ent)->setAttitude(att);
        }
    }
}


void Player::cambiarFormacion(Formaciones form) noexcept{
    formation = form;
    hacerFormacion();
}


void Player::hacerFormacion() noexcept{
    
    switch (formation)
    {
    case Formaciones::ESTANDAR:
        ESTANDAR(positionFormation);
        break;
    case Formaciones::CIRCULO:
        CIRCULO(positionFormation);
        break;
    case Formaciones::TRIANGULO:
        TRIANGULO(positionFormation);
        break;
    case Formaciones::LINEA:
        LINEA(positionFormation);
        break;
    default:
        std::cout << "Formacion no disponible" << std::endl;
        break;
    }
}

void Player::ESTANDAR(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();


    float cos = std::cos(angleOfFormation);
    float sin = std::sin(angleOfFormation);

    int num_filas = 4;
    int num_columnas = 5;

    float h_rect = 2* H_SOLDIER;
    float w_rect = 3* W_SOLDIER;

    int i = 0;
    for (int fila = 0; fila < num_filas; fila++) {
        for (int columna = 0; columna < num_columnas; columna++) {
            float x = (coord.x-w_rect) + columna * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float y = (coord.y-h_rect) + fila * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float relX = x - positionFormation.x;
            float relY = y - positionFormation.y;
            if(i < numeroEntidades){
                float rotated_relX = relX * cos - relY * sin;
                float rotated_relY = relX * sin + relY * cos;
                static_cast<Soldier*>(arraySeleccion[i])->setDestination({positionFormation.x + rotated_relX, positionFormation.y + rotated_relY});
                i++;
            }
     
        }
    }

    inFormation = true;
}

void Player::CIRCULO(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();

    float radius = 70;

    for (int i = 0; i < numeroEntidades; i++) {
        double angle = 2 * M_PI * i / numeroEntidades; // Ángulo igualmente espaciado entre las entidades.
        Vector2 dest;
        dest.x = coord.x + radius * cos(angle);
        dest.y = coord.y + radius * sin(angle);
        static_cast<Soldier*>(arraySeleccion[i])->setDestination(dest);
    }

    inFormation = true;
}

void Player::TRIANGULO(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();


    float cos = std::cos(angleOfFormation);
    float sin = std::sin(angleOfFormation);

    int numFilas = 6;

    Vector2 center;
    center.x = positionFormation.x + 8;
    center.y = positionFormation.y + 75;

    int prog = 0;
    int ent = 0;
    for(int i=0;i<numFilas;i++){
        prog++;
        for(int j = 0; j<prog;j++){
            float x = coord.x+j*(W_SOLDIER) -i*12;
            float y = coord.y +i*(H_SOLDIER);
            float relX = x - center.x;
            float relY = y - center.y;
            //std::cout << dest.x << " : " << dest.y << std::endl;
            if(ent < numeroEntidades){
                float rotated_relX = relX * cos - relY * sin;
                float rotated_relY = relX * sin + relY * cos;
                static_cast<Soldier*>(arraySeleccion[ent])->setDestination({positionFormation.x + rotated_relX, positionFormation.y + rotated_relY});
                ent++;
            }
        }
        
    }



    inFormation = true;
}

void Player::LINEA(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();


    float cos = std::cos(angleOfFormation);
    float sin = std::sin(angleOfFormation);

    int num_filas = 10;
    int num_columnas = 2;

    float h_rect = 5* H_SOLDIER;
    float w_rect = W_SOLDIER;

    int i = 0;
    for (int fila = 0; fila < num_filas; fila++) {
        for (int columna = 0; columna < num_columnas; columna++) {
            float x = (coord.x-w_rect) + columna * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float y = (coord.y-h_rect) + fila * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float relX = x - positionFormation.x;
            float relY = y - positionFormation.y;
            if(i < numeroEntidades){
                float rotated_relX = relX * cos - relY * sin;
                float rotated_relY = relX * sin + relY * cos;
                static_cast<Soldier*>(arraySeleccion[i])->setDestination({positionFormation.x + rotated_relX, positionFormation.y + rotated_relY});
                i++;
            }
     
        }
    }

    inFormation = true;
}