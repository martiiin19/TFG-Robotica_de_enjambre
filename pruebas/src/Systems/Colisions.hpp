#pragma once

#include <vector>

#include "../Handler/Entity.hpp"

#include "../Player/Player.hpp"

#include "../Handler/GameEntities.hpp"

#define RADIUS 140

struct Colisions_System
{

    float calculateDistanceBetweenPoints(Vector2 p1,Vector2 p2){
        return std::sqrt(std::pow(p2.x-p1.x,2) + std::pow(p2.y-p1.y,2));
    }

    std::pair<float, float> lineCalculator(Vector2 entity, Vector2 structure,Camera2D& camera){
        //std::cout << entity.x << " " << entity.y << "<->" << structure.x << " " << structure.y << std::endl;
        //y = mx+b
        float m = (entity.y - structure.y)/(entity.x-structure.x);
        DrawLineV(GetWorldToScreen2D(structure,camera) ,GetWorldToScreen2D(entity,camera),YELLOW);
        float b = entity.y - m*entity.x;

        return std::make_pair(m,b);
    }

    void intersectionCalculator(Vector2 center, float m, float b,Entity* ent, Camera2D& camera){
        //(x-h)²+(y-k)² = r²
        float h = center.x;
        float k = center.y;
        //y = mx+b
        //(x-h)²+((mx+b)-k)²-r² = 0 (1+m2)x2+(2m(b−k)−2h)x+(h2+(b−k)2−r2)=0
        //AX²+BX+C = 0
        float A = 1+m*m;
        float B = (2*m*(b-k)-2*h);
        float C = h*h+(b-k)*(b-k)-RADIUS*RADIUS;

        float discriminante = B*B-4*A*C;
        if(discriminante == 0){
            float x = -B/(2*A);
            float y = m * x + b;
            static_cast<Soldier*>(ent)->setRepulsion({x,y});
        }else if(discriminante > 0){
            float x1 = (-B+std::sqrt(discriminante))/(2*A);
            float y1 = m * x1 + b;
            float x2 = (-B-std::sqrt(discriminante))/(2*A);
            float y2 = m * x2 + b;
            DrawLineV(GetWorldToScreen2D(center,camera) ,GetWorldToScreen2D({x1,y1},camera),YELLOW);
            DrawLineV(GetWorldToScreen2D(center,camera) ,GetWorldToScreen2D({x2,y2},camera),YELLOW);
            if(ent->getPosition().y > center.y && ent->getPosition().x > center.x){
                static_cast<Soldier*>(ent)->setRepulsion({x1,y1});
            }else if(ent->getPosition().y > center.y && ent->getPosition().x < center.x){
                static_cast<Soldier*>(ent)->setRepulsion({x2,y2});
            }else if(ent->getPosition().y < center.y && ent->getPosition().x > center.x){
                static_cast<Soldier*>(ent)->setRepulsion({x1,y1});
            }else{
                static_cast<Soldier*>(ent)->setRepulsion({x2,y2});
            }
            
        }
    }

    void updateColisionsToSelectEntities(Entity* ent,Player& player,Camera2D& camera) noexcept{
        bool flag = ent->UpdateCollision(GetScreenToWorld2D(player.getMouse().getCoord(),camera));
        if(flag == true ){
            player.getMouse().setColision(flag,ent);
        }else if(ent == player.getMouse().getEnt() && flag == false){
            player.getMouse().setColision(flag,nullptr);
        }
        if(player.rectSelection.width != 0 && player.rectSelection.height != 0){
            ent->UpdateRecColision(player.rectSelection);
        }   
    }
    
    

    void updateColisionsWithStructures(Entity* ent,GameEntities& game,Camera2D& camera){
        bool cent = false;
        for(auto& stc : game.getEntities(TypeEntity::STRUCTURE)){
            if(calculateDistanceBetweenPoints(ent->getPosition(),stc->getPosition()) < RADIUS){
                std::pair<float,float> line = lineCalculator(ent->getPosition(),stc->getPosition(), camera);
                intersectionCalculator(stc->getPosition(),line.first,line.second,ent,camera);
                cent = true;
                std::cout << stc->getID() << std::endl;
            }
            if(cent == false){
                static_cast<Soldier*>(ent)->setRepulsion({0,0});
            }
        }
    }
    
    void Update(GameEntities& game, Player& player,Camera2D& camera){
        for(auto& ent : game.getEntities(TypeEntity::SOLDIER)){
            updateColisionsToSelectEntities(ent,player,camera); 
            updateColisionsWithStructures(ent,game,camera);
        }
    }
};
