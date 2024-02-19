#pragma once 

#include <vector>
#include <algorithm>
#include "Map.hpp"
#include <iostream>
#include "../Textura.hpp"
#include "../EntityGenerator.hpp"

struct MapsHandler{

    explicit MapsHandler(EntityGenerator& generator, Camera2D& camera) : gen{generator}, cam{camera} {}

    void addMap(const char* path){
        Map* m = new Map(path);
        maps.emplace_back(m);
        std::vector<std::string> aux = m->getImages();
        bool centinela {false}; 
        
        if(!aux.empty()){
            unsigned int size = textures.size();
            for(auto str : aux){
                for(unsigned int i =0; i<size;i++){
                    if(str == textures[i]->getFilePath()){
                        centinela = true;
                    }
                }
                if(centinela == false){
                    Textura* nueva = new Textura(str.c_str());
                    textures.emplace_back(nueva);
                } 
            }
        }
        m->readMap(textures,gen,cam);
        
    }

    void deleteMap(const char* path){
        unsigned int cont {0};
        int aux {-1};
        for(auto* map : maps){
            if(std::strcmp(map->getPath(),path) == 0){
                map->~Map();
                aux = cont;
            }
            cont++;
        }
        if(aux > -1){
            maps.erase(maps.begin() + aux);
        }
       
    }

    void printMap(){

        maps.at(id)->printMap(cam); // esto hay que cambiarlo por un vector personalizado a la mapa con sus tilesets
    }



    private:
        int id { 0 };
        std::vector<Map*> maps;   
        std::vector<Textura*> textures;
        EntityGenerator& gen;
        Camera2D& cam;
};