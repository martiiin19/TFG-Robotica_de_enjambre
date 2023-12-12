#include <raylib.h>


//Systems
#include "Systems/Physics.hpp"
#include "Systems/Render.hpp"
#include "Systems/Colisions.hpp"
#include "Systems/Input.hpp"

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

    EntityGenerator generator{gameEntities};

    Player player;

    MapsHandler maps {};

    maps.addMap("assets/mapas/mapaXML.tmx");

    Render_System render;
    Physics_System physics;
    Input_System input;
    Colisions_System colision;

    generator.CreateEntity({1000,200},{0,0},TypeEntity::SOLDIER);
    generator.CreateEntity({500,500},{0,0},TypeEntity::STRUCTURE);
    //generator.CreateEntities(30);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    while(!WindowShouldClose()){

        input.Update(gameEntities, player);
        colision.Update(gameEntities,player);
        physics.Update(gameEntities);

        BeginDrawing(); 
            maps.printMap();
            render.Update(gameEntities, player);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}