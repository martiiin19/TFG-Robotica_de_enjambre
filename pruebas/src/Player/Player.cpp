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

void Player::moveEntity() noexcept{
    if(arraySeleccion[0] != nullptr){
        Vector2 aux = {mouse.getCoord().x - W_SOLDIER/2,mouse.getCoord().y -H_SOLDIER/2};
        arraySeleccion[0]->setDestination(aux);
    }
}

void Player::moveAndFormation() noexcept{
    ESTANDAR(mouse.getCoord());
}

void Player::cambiarFormacion(Formaciones form) noexcept{
    //Cuando este hecha la seleccion pasamos a esta funcion
    //En un principio hay que hacer un switch para que llame a las funciones en protected
    //Hay que hacer algo para sacar la cantidad de entidades que contiene el array aunque sea un array con capacidad limitada
    switch (form)
    {
    case Formaciones::ESTANDAR:
        //ESTANDAR();
        break;
    case Formaciones::CIRCULO:
        //CIRCULO();
        break;
    case Formaciones::TRIANGULO:
        //TRIANGULO();
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

    float radius = 100;

    for (int i = 0; i < numeroEntidades; i++) {
        double angle = 2 * M_PI * i / numeroEntidades; // Ángulo igualmente espaciado entre las entidades.
        Vector2 dest;
        dest.x = coord.x + radius * cos(angle);
        dest.y = coord.y + radius * sin(angle);
        arraySeleccion[i]->setDestination(dest);
    }
}

void Player::TRIANGULO(Vector2 coord) noexcept{
    //int numeroEntidades = anyEntitySelected();


}