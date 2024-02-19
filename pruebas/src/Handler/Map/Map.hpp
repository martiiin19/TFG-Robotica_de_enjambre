#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include "tinyXML2/tinyxml2.h"
#include "Tile.hpp"
#include <vector>
#include "../Textura.hpp"
#include "../EntityGenerator.hpp"

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
        int centinela = -1;
        for(XMLElement* child = map->FirstChildElement("tileset"); child != nullptr && centinela == -1; child = child->NextSiblingElement("tileset")){
            if(id < std::stoi(child->Attribute("firstgid"))){
                aux = child->PreviousSiblingElement("tileset");
                centinela = 0;
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

    void readMap(std::vector<Textura*>& texts,EntityGenerator& gen, Camera2D& cam){ // esta funcion se llamara los mas seguro desde el addMap para dejar preparado el mapa y solo printearlo
        map->QueryAttribute("width",&columnas);
        map->QueryAttribute("height",&filas);
        map->QueryAttribute("tilewidth",&tilewidth);
        map->QueryAttribute("tileheight",&tileheight);
        for(XMLElement* child = map->FirstChildElement("layer"); child != nullptr; child = child->NextSiblingElement("layer")){//MAL hay que leer los tiles no solo uno
            XMLElement* data = child->FirstChildElement("data");
            for(XMLElement* tile = data->FirstChildElement("tile"); tile != nullptr; tile = tile->NextSiblingElement("tile")){
                if(tile->Attribute("gid")){
                    int id = std::stoi(tile->Attribute("gid"));
                    int firstid = std::stoi(getTilesetXMLElement(id)->Attribute("firstgid"));
                    
                    Tile* nuevo = new Tile(id,*getTilesetXMLElement(id),textureComparer(getTilesetXMLElement(id)->FirstChildElement("image")->Attribute("source"),texts),firstid);//se crea el tile pero tengo que saber que tileset pasarle
                    tiles.emplace_back(nuevo);
                }
                   
            }
        }
        //std::cout << i << std::endl;
        putObjects(cam,gen);
    }
    
    void printLayers(Camera2D& cam){
        int i = 0;
        for(XMLElement* child = map->FirstChildElement("layer"); child != nullptr; child = child->NextSiblingElement("layer")){
            XMLElement* firstTile = child->FirstChildElement("data")->FirstChildElement("tile");
            
            for(int y=0;y<filas;y++){
                for(int x=0;x<columnas;x++){
                    //std::cout<< "Ancho: " << x << "/" << columnas*tilewidth << " Alto: " << y << "/" << filas*tileheight << std::endl;
                    if(firstTile->Attribute("gid")){
                        int m_X = (x - y) * tilewidth / 2;
                        int m_Y = (x + y) * tileheight / 2;
                        Vector2 pos {m_X,m_Y};

                        tiles[i]->printTile(pos);
                        
                        i++;
                    }
                    firstTile = firstTile->NextSiblingElement("tile");
                }
            }
        }
        
    }

    void createStructures(XMLElement* objectgroup,EntityGenerator& gen,Camera2D& cam){
        for(XMLElement* object = objectgroup->FirstChildElement("object");object!=nullptr;object = object->NextSiblingElement("object")){
            float m_X = (std::stof(object->Attribute("x")) - std::stof(object->Attribute("y")))/2;
            float m_Y = (std::stof(object->Attribute("x")) + std::stof(object->Attribute("y")))/2;
            gen.CreateEntity({m_X,m_Y},{0,0},TypeEntity::STRUCTURE);
        }
    }

    void putObjects(Camera2D& cam,EntityGenerator& gen){ // a esto se le pasa el generador
        for(XMLElement* child = map->FirstChildElement("objectgroup"); child!=nullptr; child = child->NextSiblingElement("objectgroup")){
            std::string name = child->Attribute("name");
            if(name =="Structuras"){
                createStructures(child,gen,cam);
            }
        }
    }


    void printMap(Camera2D& cam){
       printLayers(cam);
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
