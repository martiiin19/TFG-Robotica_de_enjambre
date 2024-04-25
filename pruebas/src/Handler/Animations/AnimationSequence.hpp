#pragma once


struct AnimationSequence : public Animation
{
    explicit AnimationSequence(const char* filename,float speed,int f) : Animation(filename){
        frames = f;
        currentFrame = 0;
        frameCounter = 0;
        frameSpeed = speed;
    }

    void Update(int d) override{
        frameCounter += GetFrameTime();
        if (frameCounter >= frameSpeed) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame > frames) // 8 filas * 4 columnas = 32 sprites
                currentFrame = 0;
        }
    }

    void Draw(Vector2 position) override{
        Rectangle sourceRec = { (float)(currentFrame % frames) * getTexture().width / frames+10, 10, (float)getTexture().width/frames, (float)getTexture().height};
        position.x = position.x -sourceRec.width/4;
        position.y = position.y -sourceRec.height/4;
        DrawTextureRec(getTexture(), sourceRec, position, WHITE);
    }

    private:
        int frames;
};
