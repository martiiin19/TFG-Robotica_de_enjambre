#pragma once

#include <iostream>
#include "tinyXML2/tinyxml2.h"
#include "Tile.hpp"
#include <vector>
#include "../Textura.hpp"

using namespace tinyxml2;

struct Map
{
    Map(const char *path){
        doc = new XMLDocument;
        if (doc->LoadFile(path) != XML_SUCCESS) {
            std::cerr << "Error al cargar el archivo XML." << std::endl;
        }
        map = doc->FirstChildElement("map");
        if(!map){
            std::cerr << "ERROR NO ES UN MAPA" << std::endl;
        }
    }

    ~Map(){
        delete doc;
    }

    std::vector<std::string> getImages(){
        std::vector<std::string> aux;
        for(tinyxml2::XMLElement* child = map->FirstChildElement("tileset"); child != nullptr; child = child->NextSiblingElement("tileset")){
            aux.push_back(child->FirstChildElement("image")->Attribute("source"));
        }
        return aux;
    }

    void readMap(){
        map->QueryAttribute("width",&columnas);
        map->QueryAttribute("height",&filas);

    }
    
    void printLayers(std::vector<Textura*>& tilesets){
        for(int y=0;y<filas;y++){
            for(int x=0;x<columnas;x++){
                
            }
        }
    }

    void putObjetcs(){

    }


    void printMap(std::vector<Textura*>& tilesets){
       printLayers(tilesets);
       putObjetcs();
    }

    const char* getPath(){
        return doc->Value();
    } 

    private:
        int filas;
        int columnas;
        XMLElement *map;
        XMLDocument *doc;
        std::vector<Tile*> tiles;
       
};
