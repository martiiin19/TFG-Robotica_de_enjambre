#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
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
        //Borramos el documento
        delete doc;
        //Borramos el vector de tiles
        for( auto* tile : tiles){
            tile->~Tile();
            delete tile;
        }
        tiles.clear();
        delete &tiles;
    }

    std::vector<std::string> getImages(){
        std::vector<std::string> aux;
        for(XMLElement* child = map->FirstChildElement("tileset"); child != nullptr; child = child->NextSiblingElement("tileset")){
            aux.push_back(child->FirstChildElement("image")->Attribute("source"));
        }
        return aux;
    }

    XMLElement* getTilesetXMLElement(int id){
        XMLElement* aux {};
        for(XMLElement* child = map->FirstChildElement("tileset"); child != nullptr; child = child->NextSiblingElement("tileset")){
            if(id < std::stoi(child->Attribute("firstgid"))){
                aux = child->PreviousSiblingElement("tileset");
            }
        }
        return aux;
    }

    Textura* textureComparer(std::string str, std::vector<Textura*>& texts){
        for(std::vector<Textura*>::size_type i =0 ; i<texts.size(); i++){
            if(str == texts[i]->getFilePath()){
                return texts[i];
            }
        }
        return nullptr;
    }

    void readMap(std::vector<Textura*>& texts){ // esta funcion se llamara los mas seguro desde el addMap para dejar preparado el mapa y solo printearlo
        map->QueryAttribute("width",&columnas);
        map->QueryAttribute("height",&filas);
        map->QueryAttribute("tilewidth",&tilewidth);
        map->QueryAttribute("tileheight",&tileheight);
        bool centinela {false};
        for(XMLElement* child = map->FirstChildElement("layer"); child != nullptr; child = child->NextSiblingElement("layer")){//MAL hay que leer los tiles no solo uno
            XMLElement* data = child->FirstChildElement("data");
            for(XMLElement* tile = data->FirstChildElement("tile"); tile != nullptr; tile = tile->NextSiblingElement("tile")){
                if(tile->Attribute("gid")){
                    if(!tiles.empty()){
                        for(auto* t : tiles){
                            if(std::stoi(tile->Attribute("gid")) == t->getID()){
                                centinela = true;
                            }
                        }
                    }
                    if(centinela == false){
                        int id = std::stoi(tile->Attribute("gid"));
                        int firstid = std::stoi(getTilesetXMLElement(id)->Attribute("firstgid"));
                        
                        Tile* nuevo = new Tile(id,*getTilesetXMLElement(id),textureComparer(getTilesetXMLElement(id)->FirstChildElement("image")->Attribute("source"),texts),firstid);//se crea el tile pero tengo que saber que tileset pasarle
                        tiles.emplace_back(nuevo);
                    }else{
                        centinela = false;
                    }
                }
                
                
            }
        }
    }
    
    void printLayers(){
        for(XMLElement* child = map->FirstChildElement("layer"); child != nullptr; child = child->NextSiblingElement("layer")){
            XMLElement* firstTile = child->FirstChildElement("data")->FirstChildElement("tile");

            for(int y=100;y<filas*tileheight;y+=tileheight){
                for(int x=100;x<columnas*tilewidth;x+=tilewidth){
                    //std::cout<< "Ancho: " << x << "/" << columnas*tilewidth << " Alto: " << y << "/" << filas*tileheight << std::endl;
                    if(firstTile->Attribute("gid")){
                        printTile(std::stoi(firstTile->Attribute("gid")),x,y);
                         
                    }
                    firstTile = firstTile->NextSiblingElement("tile");
                }
            }
        }
        
    }

    void putObjetcs(){

    }


    void printMap(){
       printLayers();
       putObjetcs();
    }

    void printTile(int gid, float x,float y){
        for(auto& t :tiles){
            if(gid == t->getID()){
                Vector2 pos {x,y};
                t->printTile(pos);
            }
        }
    }

    const char* getPath(){
        return doc->Value();
    } 

    private:
        int filas{};
        int columnas{};
        int tilewidth{};
        int tileheight{};
        XMLElement *map;
        XMLDocument *doc;
        std::vector<Tile*> tiles;
       
};
