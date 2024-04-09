#pragma once

#include <raylib.h>

struct Animation
{
    explicit Animation(const char* filename){
        tex = LoadTexture(filename);
    }

    ~Animation(){

    }

    virtual void Update(int direccion) = 0;

    virtual void Draw(Vector2 position) = 0;

    int currentFrame;
    float frameCounter;
    float frameSpeed;
    
    Texture2D getTexture(){
        return tex;
    }

    private:
        Texture2D tex;
        


};
