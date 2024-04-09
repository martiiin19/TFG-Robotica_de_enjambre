#pragma once

#include "Animations/Animation8Directions.hpp"
#include "Animations/AnimationSequence.hpp"

#include "StatesAnimation.hpp"

struct HandlerAnimator
{
    explicit HandlerAnimator(){
        move = new Animation8Directions("assets/animaciones/Characters/Knight1_Move.png",0.1f);
        attack = new Animation8Directions("assets/animaciones/Characters/Knight1_Attack.png",0.1f);
        stay = new AnimationSequence("assets/animaciones/Characters/Knight1_Stay.png",0.3f,5);
    }

    ~HandlerAnimator(){

    }

    void Update(StatesAnimation s, int d){
        sta = s;
        switch (sta)
        {
        case StatesAnimation::STAY:
            stay->Update(d);
            break;
        case StatesAnimation::MOVE:
            move->Update(d);
            break;
        case StatesAnimation::ATTACK:
            attack->Update(d);
            break;
        case StatesAnimation::FAINT:
            faint->Update(d);
            break;
        }
    }

    void Draw(Vector2 pos){
        switch (sta)
        {
        case StatesAnimation::STAY:
            stay->Draw(pos);
            break;
        case StatesAnimation::MOVE:
            move->Draw(pos);
            break;
        case StatesAnimation::ATTACK:
            attack->Draw(pos);
            break;
        case StatesAnimation::FAINT:
            faint->Draw(pos);
            break;
        }
    }

    private:
        StatesAnimation sta {StatesAnimation::MOVE};
        AnimationSequence* stay;
        Animation8Directions* attack;
        Animation8Directions* move;
        Animation* faint;

};
