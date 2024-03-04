#include "Player.hpp"

Player::Player() {
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
            ent->changeSelected(true);
            arraySeleccion[i] = ent;
            i++;
        }
    }
}

void Player::deseleccionarEntidades() noexcept{
    for(unsigned int i = 0; i<arraySeleccion.size(); i++){
        if(arraySeleccion[i] != nullptr){
            arraySeleccion[i]->changeSelected(false);
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
            ent->Atacar(mouse.getEnt());
        }   
    }
}

void Player::moveEntity(Vector2 coords) noexcept{
    if(arraySeleccion[0] != nullptr){
        //Vector2 aux = {coords.x - W_SOLDIER/2,coords.y -H_SOLDIER/2};
        arraySeleccion[0]->setDestination(coords);
        arraySeleccion[0]->setEnemigo();
    }
}

void Player::moveAndFormation(Vector2 coords) noexcept{
    for(auto* ent : arraySeleccion){
        if(ent != nullptr){
            ent->setEnemigo();
        }
    }
    positionFormation = coords;
    hacerFormacion();
}

void Player::cambiarActitud(Attitude att) noexcept{
    for(auto* ent : arraySeleccion){
        if(ent != nullptr){
            ent->setAttitude(att);
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
    default:
        std::cout << "Formacion no disponible" << std::endl;
        break;
    }
}

void Player::ESTANDAR(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();

    int num_filas = 4;
    int num_columnas = 5;

    float h_rect = 2* H_SOLDIER;
    float w_rect = 3* W_SOLDIER;

    int i = 0;
    for (int fila = 0; fila < num_filas; fila++) {
        for (int columna = 0; columna < num_columnas; columna++) {
            float x = (coord.x-w_rect) + columna * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float y = (coord.y-h_rect) + fila * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            if(i < numeroEntidades){
                arraySeleccion[i]->setDestination({x,y});
                i++;
            }
            
        }
    }

}

void Player::CIRCULO(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();

    float radius = 70;

    for (int i = 0; i < numeroEntidades; i++) {
        double angle = 2 * M_PI * i / numeroEntidades; // Ángulo igualmente espaciado entre las entidades.
        Vector2 dest;
        dest.x = coord.x + radius * cos(angle);
        dest.y = coord.y + radius * sin(angle);
        arraySeleccion[i]->setDestination(dest);
    }
}

void Player::TRIANGULO(Vector2 coord) noexcept{
    int numeroEntidades = anyEntitySelected();

    int numFilas = 6;

    int prog = 0;
    int ent = 0;
    for(int i=0;i<numFilas;i++){
        prog++;
        for(int j = 0; j<prog;j++){
            Vector2 dest;
            dest.x = coord.x+j*(W_SOLDIER) -i*12;
            dest.y = coord.y +i*(H_SOLDIER);
            //std::cout << dest.x << " : " << dest.y << std::endl;
            if(ent < numeroEntidades){
                arraySeleccion[ent]->setDestination(dest);
                ent++;
            }
        }
        
    }

}