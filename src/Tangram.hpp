#pragma once

#include <algorithm>
#include <raylib.h>

#include <raymath.h>
#include <vector>

struct Triangle{
    std::vector<Vector2> points;

    Triangle(std::vector<Vector2> pnts) : points(pnts) {
        RearrangeCounterClockwise();
    }
    
    void Draw(Color color){
        DrawTriangle(points[0], points[1], points[2], color);

        for (auto point : points){
            DrawCircleV(point, 10, BLACK);
        }
    }

    void RearrangeCounterClockwise() {
        // Find the centroid of the triangle
        Vector2 centroid = {
            (points[0].x + points[1].x + points[2].x) / 3.0f,
            (points[0].y + points[1].y + points[2].y) / 3.0f
        };
        
        // Sort points based on the angle relative to the centroid using atan2
        std::sort(points.begin(), points.end(), [&centroid](const Vector2& a, const Vector2& b) {
            return std::atan2(a.y - centroid.y, a.x - centroid.x) > 
                std::atan2(b.y - centroid.y, b.x - centroid.x);
        });
    }

};

struct Tile {
    std::vector<Triangle> trigs;
    Color color;

    Vector2 CalculateCenter(){
        Vector2 sum = {0,0};
        for (auto trig : trigs){
            for (Vector2 point : trig.points){
                sum = Vector2Add(sum, point);
            }
        }

        return Vector2Scale(sum, 1.f / (trigs.size()*3) );
    }

    void Move(Vector2 delta_m){
        for (auto trig : trigs){
            for (int i = 0; i < trig.points.size(); i++){
                trig.points[i] = Vector2Add(trig.points[i], delta_m);
            }
            trig.RearrangeCounterClockwise();
        }
    }

    void Rotate(float delta_r){ // rotates around calculated center (avg of points)
        Vector2 center = CalculateCenter();
        for (auto&& trig : trigs){
            for (int i = 0; i < trig.points.size(); i++){
                Vector2 frm_cntr_to_pnt = Vector2Subtract(trig.points[i], center);
                frm_cntr_to_pnt = Vector2Rotate(frm_cntr_to_pnt, delta_r);
                trig.points[i] = Vector2Add(center, frm_cntr_to_pnt);
            }
            trig.RearrangeCounterClockwise();
        }
    }

    void Draw(){
        for (auto trig : trigs){
            trig.Draw(color);
        }
    }

    Tile(std::vector<Triangle> triangles, Color clr, float rotation = 0.f) : 
    trigs(triangles), color(clr) {
        Rotate(rotation);
    }
};

Triangle RightEvenTrig(Vector2 pos, float a, float r = 0.f);

class Tangram {
private:
    std::vector<Tile> tiles = {};

public:
    Tangram(Vector2 center = {0,0}) { // default constructor fills tiles with starting tangram square layout
        float a = 640.f;
        
        tiles.push_back(Tile(
            { RightEvenTrig(center, a/sqrt(2), M_PI/4)},
            RED
        ));

        tiles.push_back(Tile(
            { RightEvenTrig(center, a/sqrt(2), M_PI/2+M_PI/4)},
            GREEN
        ));

        tiles.push_back(Tile(
            { RightEvenTrig(center, a/2/sqrt(2), M_PI+M_PI/4)},
            YELLOW
        ));

        tiles.push_back(Tile(
            {
                RightEvenTrig(Vector2Add(center, Vector2{-a/2, 0}), a/2/sqrt(2), M_PI/4),
                RightEvenTrig(Vector2Add(center, Vector2{-a/4, a/4}), a/2/sqrt(2), M_PI+M_PI/4)
            },
            ORANGE
        ));
    
        tiles.push_back(Tile(
            { RightEvenTrig(Vector2Add(center, Vector2{-a/2, -a/2}), a/2, M_PI/2)},
            BLUE
        ));

        tiles.push_back(Tile(
            { 
                RightEvenTrig(Vector2Add(center, Vector2{a/4, -a/4}), a/2/sqrt(2), M_PI+M_PI/4),
                RightEvenTrig(Vector2Add(center, Vector2{-a/4, -a/4}), a/2/sqrt(2), M_PI/4)
            },
            BLACK
        ));

        tiles.push_back(Tile(
            {RightEvenTrig(Vector2Add(center, Vector2{a/4, -a/4}), a/2/sqrt(2), -M_PI/4)},
            PURPLE
        ));

    }

    void Update(){
    }

    void Draw(){
        for (auto tile : tiles){
            tile.Draw();
        }
    }

    std::vector<Tile> GetTiles() { return tiles; }
};