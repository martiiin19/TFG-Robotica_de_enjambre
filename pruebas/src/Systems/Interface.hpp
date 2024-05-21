#pragma once 

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

#define HUD_POSITION GetScreenHeight()-260.f

struct Interface_System
{
     explicit Interface_System(){
        hudDown = LoadTexture("assets/interfaz/hudDown.png");
        rectangulo = LoadTexture("assets/interfaz/Rectangulo.png");
        circulo = LoadTexture("assets/interfaz/Circulo.png");
        triangulo = LoadTexture("assets/interfaz/Triangulo.png");
        linea = LoadTexture("assets/interfaz/Linea.png");
        ofensiva = LoadTexture("assets/interfaz/Ofensiva.png");
        defensiva = LoadTexture("assets/interfaz/Defensiva.png");
        pasiva = LoadTexture("assets/interfaz/Neutral.png");
        giro_derecha = LoadTexture("assets/interfaz/Giro_Derecha.png");
        giro_izquierda = LoadTexture("assets/interfaz/Giro_Izquierda.png");
        gira = LoadTexture("assets/interfaz/Gira.png");
        minimap.target = (Vector2){ 0.0f, 0.0f };
        minimap.offset = (Vector2){ 1920 - 175, HUD_POSITION+5 }; // Offset para posicionar el minimapa en la esquina superior derecha
        minimap.rotation = 0.0f;
        minimap.zoom = 0.052f; // Zoom del minimapa
    }

    void Update(GameEntities& game,Camera2D& camera,Player& player){

        std::string string1 = "Cantidad de Entidades: " + std::to_string(game.getEntities(TypeEntity::SOLDIER).size());
        const char* texto1 = string1.c_str();
        
        DrawText(texto1, 100 ,10, fontSize, WHITE);

        std::string string2 = "Angulo :" + std::to_string(static_cast<int>(player.angleOfFormationAux)) + "º";
        const char* texto2 = string2.c_str();

        DrawText(texto2, 600 ,10, fontSize, WHITE);
        
        DrawTextureRec(hudDown,source,{0,HUD_POSITION},WHITE); // Barra de Interfaz
        
        //Formaciones
        DrawTexture(rectangulo,13,HUD_POSITION+25,WHITE);
        DrawTexture(circulo,78,HUD_POSITION+25,WHITE);
        DrawTexture(triangulo,143,HUD_POSITION+25,WHITE);
        DrawTexture(linea,208,HUD_POSITION+25,WHITE);
        
        //Actitudes
        DrawTexture(ofensiva,13,HUD_POSITION+75,WHITE);
        DrawTexture(defensiva,78,HUD_POSITION+75,WHITE);
        DrawTexture(pasiva,143,HUD_POSITION+75,WHITE);

        //Giro
        DrawTexture(giro_izquierda,13,HUD_POSITION+125,WHITE);
        DrawTexture(giro_derecha,78,HUD_POSITION+125,WHITE);
        DrawTexture(gira,143,HUD_POSITION+125,WHITE);
        DrawRectangleV({1920 - 350, HUD_POSITION+5},{350,255},BLACK);
        BeginMode2D(minimap);
        

       
        
    }

    private:
        Camera2D minimap {0};
        Texture2D hudDown;
        Rectangle source {0,0,GetScreenWidth(),175};
        Texture2D rectangulo;
        Texture2D circulo;
        Texture2D triangulo;
        Texture2D linea;
        Texture2D ofensiva;
        Texture2D defensiva;
        Texture2D pasiva;
        Texture2D giro_derecha;
        Texture2D giro_izquierda;
        Texture2D gira;
        int fontSize {30};

        


        
};
