#pragma once 

#include <raylib.h>
#include <string>
#include <iostream>

struct Textura
{
    Textura(const char* path) : filePath{path}{
        textura = LoadTexture(path);
        std::cout << filePath << std::endl;
    }

    ~Textura(){
        UnloadTexture(textura);
    }

    Texture2D getTexture(){
        return textura;
    }

    std::string getFilePath(){
        return filePath;
    }

    private:
        Texture2D textura;
        std::string filePath;
};
