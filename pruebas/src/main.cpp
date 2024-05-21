#include <raylib.h>


//Systems
#include "Systems/Physics.hpp"
#include "Systems/Render.hpp"
#include "Systems/Colisions.hpp"
#include "Systems/Input.hpp"
#include "Systems/Attitude.hpp"
#include "Systems/Animation.hpp"
#include "Systems/DeadLine.hpp"
#include "Systems/Interface.hpp"

//Handler
#include "Handler/GameEntities.hpp"
#include "Handler/EntityGenerator.hpp"
#include "Handler/Map/MapsHandler.hpp"

//Player
#include "Player/Player.hpp"

//Macros
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080


int main(){

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib [core] example - basic window");

    GameEntities gameEntities;

    Camera2D camera { 0 };
    camera.target = (Vector2){ 29 ,3100 };
    camera.offset = (Vector2){ SCREENWIDTH / 2.0f, SCREENWIDTH / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Player player {camera};

    EntityGenerator generator{gameEntities,camera};
    //Unidad de reconocimiento
    generator.CreateFormacionEnemigos(29, 2620,0,Formaciones::ESTANDAR,0);
    //Enemigos
    generator.CreateFormacionEnemigos(30, 1540,0,Formaciones::ESTANDAR,1);
    generator.CreateFormacionEnemigos(800, 1200,0,Formaciones::TRIANGULO,1);
    generator.CreateFormacionEnemigos(-767, 1200,0,Formaciones::LINEA,1);
    generator.CreateFormacionEnemigos(30, 290,0,Formaciones::CIRCULO,1);
    //generator.CreateEntity({1000,200},{0,0},TypeEntity::SOLDIER);
    //generator.CreateEntity({-400,300},{0,0},TypeEntity::STRUCTURE);
    //generator.CreateEntity({800,800},{0,0},TypeEntity::STRUCTURE);
    //generator.CreateEntities(20);
    //generator.CreateFormacionEnemigos(0,0,0,Formaciones::ESTANDAR);
    //generator.CreateEnemigos(2);

    MapsHandler maps {generator, camera};

    maps.addMap("assets/mapas/tutorial.tmx");

    Render_System render;
    Physics_System physics;
    Input_System input;
    Colisions_System colision;
    Attitude_System attitude;
    Animation_System animation;
    DeadLine_System dead;
    Interface_System interface{};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    while(!WindowShouldClose()){

        input.Update(gameEntities, player,camera, generator);
        
        
        physics.Update(gameEntities,camera);
        colision.Update(gameEntities,player,camera);
        attitude.Update(gameEntities,player,camera);
        animation.Update(gameEntities,camera);
        

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
            maps.printMap();
            render.Update(gameEntities, player);
            
        EndMode2D();
        interface.Update(gameEntities,camera,player);
        maps.printMap();
        render.Update(gameEntities,player,1);
        Rectangle rect {camera.target.x-SCREENWIDTH/2,camera.target.y-SCREENHEIGHT/2-260,SCREENWIDTH,SCREENHEIGHT-260};
        DrawRectangleLinesEx(rect,25,WHITE);
        EndMode2D();
        EndDrawing();
        

        dead.Update(gameEntities,camera);

    }
    CloseWindow();
    return 0;
}