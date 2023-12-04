#pragma once 

#include <raylib.h>
#include <string>
#include "tinyXML2/tinyxml2.h"
#include <iostream>
#include <string>

using namespace tinyxml2;

struct Tile {

    int sacarId(int id,int firstID){
        return (id-firstID);
    }

    int numRows(XMLElement& tileset){
        int columns = 0;
        int tileCount = 0;
        tileset.QueryAttribute("columns",&columns);
        tileset.QueryAttribute("tilecount",&tileCount);

        return tileCount/columns;
    }
    
    int numColumns(XMLElement& tileset){
        int columns = 0;
        tileset.QueryAttribute("columns",&columns);
        return columns;
    }

    explicit Tile(int i,XMLElement& tileset, int firstID) : gid(i) { //lo suyo es pasarle el gid del tile y hacer el calculo para sacar el tile
        int id = sacarId(i,firstID);
        tileset.QueryAttribute("tilewidth",&tileWidth);
        tileset.QueryAttribute("tileheight",&tileHeight);
        int rows = numRows(tileset);
        int columns =numColumns(tileset);
        float columna = id / columns;
        float fila = id / rows;

        tile = {columna*tileWidth ,fila*tileHeight , tileWidth, tileHeight };

    }

    void printTile(Texture2D tex,Vector2 pos){
        DrawTextureRec(tex,tile,pos,WHITE);
    }

    private:
        int gid { 0 };
        float tileWidth;
        float tileHeight;
        Rectangle tile{};
};