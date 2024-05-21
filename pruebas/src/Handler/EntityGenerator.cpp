#include "EntityGenerator.hpp"


//Functions{
    Vector2 EntityGenerator::randomPosition() noexcept{
        Vector2 aux = {static_cast<float>(std::rand() % 1500 + 200), static_cast<float>(std::rand() % 700 + 100)};
        return aux;
    }
//}

EntityGenerator::EntityGenerator(GameEntities& game,Camera2D& cam) : ents{game},camera{cam} {}

void EntityGenerator::CreateEntity(Vector2 pos = {0.0,0.0},Vector2 vel = {0.0,0.0}, TypeEntity type = TypeEntity::SOLDIER, int bando = 0 ) noexcept{
    Entity* ent = new Soldier(id_iteration,type,pos,pos,vel,{W_SOLDIER,H_SOLDIER},bando);
    if(bando != 0){
        static_cast<Soldier*>(ent)->setAttitude(Attitude::OFENSIVA);
    }
    ents.InsertEntity(ent);
    id_iteration++;
}

void EntityGenerator::CreateStructure(float x, float y) noexcept{
    Entity* ent = new Structure(id_iteration,TypeEntity::STRUCTURE,{x,y},{W_SOLDIER,H_SOLDIER});
    ents.InsertEntity(ent);
    id_iteration++;
}

void EntityGenerator::CreateEntities(int n) noexcept{

    for(int i = 0; i<n; i++){
        Vector2 pos {randomPosition()};
        Entity* ent = new Soldier(id_iteration,TypeEntity::SOLDIER,pos,pos,{0.0,0.0},{W_SOLDIER,H_SOLDIER});
        ents.InsertEntity(ent);
        id_iteration++;
    }
}

void EntityGenerator::CreateEnemigos(int n) noexcept{

    for(int i = 0; i<n; i++){
        Vector2 pos {randomPosition()};
        Entity* ent = new Soldier(id_iteration,TypeEntity::SOLDIER,pos,pos,{0.0,0.0},{W_SOLDIER,H_SOLDIER},1);
        ents.InsertEntity(ent);
        id_iteration++;
    }
}

void EntityGenerator::CreateFormacionEnemigos(float x, float y,float rotacion, Formaciones form, int bando = 1) noexcept{
    switch (form)
    {
        case Formaciones::ESTANDAR:
            ESTANDAR({x,y}, rotacion, bando);
            break;
        case Formaciones::CIRCULO:
            CIRCULO({x,y}, rotacion, bando);
            break;
        case Formaciones::TRIANGULO:
            TRIANGULO({x,y}, rotacion, bando);
            break;
        case Formaciones::LINEA:
            LINEA({x,y}, rotacion, bando);
            break;
        default:
            std::cout << "Formacion no disponible" << std::endl;
            break;
    }
}


void EntityGenerator::ESTANDAR(Vector2 coord, float rotacion, int bando) noexcept{
    std::cout << coord.x << " : "<< coord.y << std::endl;
    float cos = std::cos(rotacion);
    float sin = std::sin(rotacion);

    int num_filas = 4;
    int num_columnas = 5;

    float h_rect = 2* H_SOLDIER;
    float w_rect = 3* W_SOLDIER;

    int i = 0;
    for (int fila = 0; fila < num_filas; fila++) {
        for (int columna = 0; columna < num_columnas; columna++) {
            float x = (coord.x-w_rect) + columna * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float y = (coord.y-h_rect) + fila * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            if(i < 20){
                float rotated_relX = x * cos - y * sin;
                float rotated_relY = x * sin + y * cos;
                std::cout << rotated_relX<< " : "<< rotated_relY << std::endl;
                this->CreateEntity({rotated_relX,rotated_relY},{0,0},TypeEntity::SOLDIER,bando);
                i++;
            }
     
        }
    }

}

void EntityGenerator::CIRCULO(Vector2 coord, float rotacion, int bando) noexcept{

    float radius = 70;

    for (int i = 0; i < 20; i++) {
        double angle = 2 * M_PI * i / 20; // Ángulo igualmente espaciado entre las entidades.
        Vector2 dest;
        dest.x = coord.x + radius * cos(angle);
        dest.y = coord.y + radius * sin(angle);
        this->CreateEntity(dest,{0,0},TypeEntity::SOLDIER,bando);
    }

}

void EntityGenerator::TRIANGULO (Vector2 coord, float rotacion, int bando) noexcept{


    float cos = std::cos(rotacion);
    float sin = std::sin(rotacion);

    int numFilas = 6;

    Vector2 center;
    center.x = coord.x + 8;
    center.y = coord.y + 75;

    int prog = 0;
    int ent = 0;
    for(int i=0;i<numFilas;i++){
        prog++;
        for(int j = 0; j<prog;j++){
            float x = coord.x+j*(W_SOLDIER) -i*12;
            float y = coord.y +i*(H_SOLDIER);
            //std::cout << dest.x << " : " << dest.y << std::endl;
            if(ent < 20){
                float rotated_relX = x * cos - y * sin;
                float rotated_relY = x * sin + y * cos;
                this->CreateEntity({rotated_relX,rotated_relY},{0,0},TypeEntity::SOLDIER,bando);
                ent++;
            }
        }
        
    }
}
void EntityGenerator::LINEA (Vector2 coord, float rotacion, int bando) noexcept{

    float cos = std::cos(rotacion);
    float sin = std::sin(rotacion);

    int num_filas = 10;
    int num_columnas = 2;

    float h_rect = 5* H_SOLDIER;
    float w_rect = W_SOLDIER;

    int i = 0;
    for (int fila = 0; fila < num_filas; fila++) {
        for (int columna = 0; columna < num_columnas; columna++) {
            float x = (coord.x-w_rect) + columna * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            float y = (coord.y-h_rect) + fila * std::sqrt(A_SOLDIER+SEPARATION_BETWEEN_ENTITIES);
            
            if(i < 20){
                float rotated_relX = x * cos - y * sin;
                float rotated_relY = x * sin + y * cos;
                this->CreateEntity({rotated_relX,rotated_relY},{0,0},TypeEntity::SOLDIER,bando);
                i++;
            }
     
        }
    }

}