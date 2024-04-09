#pragma once 

#include "Animation.hpp"

struct Animation8Directions : public Animation
{
    explicit Animation8Directions(const char* filename,float speed) : Animation(filename){
        this->currentFrame = 0;
        frameCounter = 0;
        frameSpeed = speed;

    }


    void Update(int d) override{
        direccion = d;
        frameCounter += GetFrameTime();
        if (frameCounter >= frameSpeed) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame >= 4) // 8 filas * 4 columnas = 32 sprites
                currentFrame = 0;
        }
    }

    void Draw(Vector2 position) override{
        Rectangle sourceRec = {  (float)currentFrame * getTexture().width / 4 + 10, (float)direccion * getTexture().height / 8 + 10, (float)getTexture().width / 4, (float)getTexture().height / 8  };
        //Rectangle destRec = { position.x, position.y, (float)getTexture().width / 4, (float)getTexture().height / 8 };
        position.x = position.x -sourceRec.width/4;
        position.y = position.y -sourceRec.height/4;
        DrawTextureRec(getTexture(), sourceRec, position, WHITE);
    }

    private: 
        int direccion {0};

};
