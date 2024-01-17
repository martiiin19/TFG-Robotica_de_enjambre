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

    Player player;

    Camera2D camera { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ SCREENWIDTH / 2.0f, SCREENWIDTH / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    MapsHandler maps {};
    EntityGenerator generator{gameEntities,camera};

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

        input.Update(gameEntities, player,camera);
        colision.Update(gameEntities,player);
        physics.Update(gameEntities);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
            maps.printMap(camera);
            render.Update(gameEntities, player);
        EndMode2D();
        EndDrawing();

    }
    CloseWindow();
    return 0;
}