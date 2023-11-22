#pragma once

#include <iostream>
#include "tinyXML2/tinyxml2.h"


struct Map
{
    Map(const char *path){
        if (map.LoadFile(path) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error al cargar el archivo XML." << std::endl;
        }
    }

    ~Map(){
        
    }

    

    void printMap(){

    }

    private:
        tinyxml2::XMLDocument map;
       
};
