#pragma once

#include "Globals.hpp"

#include <algorithm>
#include <iostream>
#include <raylib.h>

#include <raymath.h>
#include <vector>

struct Triangle{
    std::vector<Vector2> points;

    Triangle(std::vector<Vector2> pnts) : points(pnts) {
        RearrangeCounterClockwise();
    }
    
    void DrawLines(Color color){
        float thick = 5.f;
        DrawLineEx(points[0], points[1], thick, color);
        DrawLineEx(points[0], points[2], thick, color);
        DrawLineEx(points[1], points[2], thick, color);

        float rad = thick/2;
        DrawCircleV(points[0], rad, color);
        DrawCircleV(points[1], rad, color);
        DrawCircleV(points[2], rad, color);
    }

    void Draw(Color color){
        DrawTriangle(points[0], points[1], points[2], color);
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

    bool CollisionWithPoint(Vector2 point){
        for (auto&& trig : trigs){
            if (CheckCollisionPointTriangle(point, trig.points[0], trig.points[1], trig.points[2])){
                return true;
            }
        }
        return false;
    }

    Vector2 CalculateCenter(){
        Vector2 sum = {0,0};
        for (auto trig : trigs){
            for (Vector2 point : trig.points){
                sum = Vector2Add(sum, point);
            }
        }

        return Vector2Scale(sum, 1.f / (trigs.size()*3) );
    }

    void Move(Vector2 delta_m, bool snap = true){
        for (auto&& trig : trigs){
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

    void DrawLines(Color clr){
        for (auto trig : trigs){
            trig.DrawLines(clr);
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

    // similarity rating
    float max_deviation = 60000;
    int error_margin_snap = 15;

    // taking picture
    int picture_count = 0;

public:
    Tangram(Vector2 center = {0,0}) { // default constructor fills tiles with starting tangram square layout
        float a = 320.f;
        
        tiles.push_back(Tile(
            { RightEvenTrig(center, a/sqrt(2), M_PI/4)},
            Globals::pico_red
        ));

        tiles.push_back(Tile(
            { RightEvenTrig(center, a/sqrt(2), M_PI/2+M_PI/4)},
            Globals::pico_green
        ));

        tiles.push_back(Tile(
            { RightEvenTrig(center, a/2/sqrt(2), M_PI+M_PI/4)},
            Globals::pico_yellow
        ));

        tiles.push_back(Tile(
            {
                RightEvenTrig(Vector2Add(center, Vector2{-a/2, 0}), a/2/sqrt(2), M_PI/4),
                RightEvenTrig(Vector2Add(center, Vector2{-a/4, a/4}), a/2/sqrt(2), M_PI+M_PI/4)
            },
            Globals::pico_orange
        ));
    
        tiles.push_back(Tile(
            { RightEvenTrig(Vector2Add(center, Vector2{-a/2, -a/2}), a/2, M_PI/2)},
            Globals::pico_blue
        ));

        tiles.push_back(Tile(
            { 
                RightEvenTrig(Vector2Add(center, Vector2{a/4, -a/4}), a/2/sqrt(2), M_PI+M_PI/4),
                RightEvenTrig(Vector2Add(center, Vector2{-a/4, -a/4}), a/2/sqrt(2), M_PI/4)
            },
            Globals::pico_vineous
        ));

        tiles.push_back(Tile(
            {RightEvenTrig(Vector2Add(center, Vector2{a/4, -a/4}), a/2/sqrt(2), -M_PI/4)},
            Globals::pico_pink
        ));

    }

    void Draw(){
        for (auto tile : tiles){
            tile.DrawLines(
                (tile.CollisionWithPoint(Globals::pixel_render->GetMouseWorldPos())) ? Globals::pico_black : Globals::pico_white);
            tile.Draw();
        }
    }

    std::vector<Tile> GetTiles() { return tiles; }

    int GetIdAtPoint(Vector2 point){
        for (int i = 0; i < tiles.size(); i++){        
            if (tiles[i].CollisionWithPoint(point)){
                return i;
            }
        }
        return -1;
    }

    void RotateTilesAtPoint(Vector2 point, float rotation, bool only_one_tile=false){
        for (auto&& tile : tiles){
            bool overlaps = false;
            
            if (tile.CollisionWithPoint(point)){
                overlaps = true;
            }

            if (overlaps){
                tile.Rotate(rotation);
                if (only_one_tile){
                    break;
                }
            }
        }
    }

    void MoveTilesAtPoint(Vector2 point, Vector2 move, bool only_one_tile=false){
        for (auto&& tile : tiles){
            bool overlaps = false;
            
            if (tile.CollisionWithPoint(point)){
                overlaps = true;
            }

            if (overlaps){
                tile.Move(move);
                if (only_one_tile){
                    break;
                }
            }
        }
    }

    void MoveTile(int id, Vector2 delta_m){
        tiles[id].Move(delta_m);
    }

    void RotateTile(int id, float delta_r){
        std::cout << id << '\n';
        tiles[id].Rotate(delta_r);
    }

    std::vector<Vector2> GetAllPoints(){
        std::vector<Vector2> points = {};
        for (auto&& tile : tiles){
            for (auto&& trig : tile.trigs){
                for (auto point : trig.points){
                    points.push_back(point);
                }
            }
        }
        return points;
    }

    int RatePointsSimilarity(const std::vector<Vector2>& points, const std::vector<Vector2>& ref){
        float sum_of_squared_dist = 0.f;
        
        for (auto&& point : points){
            float min_distance = -1;
        
            for (auto&& ref_point : ref){
                if (min_distance == -1){
                    min_distance = floor(Vector2Distance(point, ref_point)/error_margin_snap)*error_margin_snap;
                }
                else min_distance = fmin(min_distance, floor(Vector2Distance(point, ref_point)/error_margin_snap)*error_margin_snap);
            }
        
            sum_of_squared_dist += pow(min_distance,2);
        }

        int similarity = 100*fmax(0, (1 - sum_of_squared_dist/max_deviation));
        return similarity;
    }

    int RatePointsSimilarityFromCenter(const std::vector<Vector2>& reference){
        Vector2 ref_sum = {0,0};
        for (auto point : reference){
            ref_sum = Vector2Add(ref_sum, point);
        }
        Vector2 ref_center = Vector2Scale(ref_sum, 1.f/reference.size());
        
        std::vector<Vector2> new_reference = {};
        for (auto point : reference){
            new_reference.push_back(Vector2Subtract(point, ref_center));
        }

        Vector2 sum = {0,0};
        auto points = GetAllPoints();
        for (auto point : points){
            sum = Vector2Add(sum, point);
        }
        Vector2 center = Vector2Scale(sum, 1.f/points.size());
        
        std::vector<Vector2> new_points = {};
        for (auto point : points){
            new_points.push_back(Vector2Subtract(point, center));
        }

        /*
        for (auto point : new_reference){
            DrawCircleV(Vector2Add(point, Vector2{300,200}), 10, BLACK);
        }

        for (auto point : new_points){
            DrawCircleV(Vector2Add(point, Vector2{300,200}), 10, RED);
        }
        */


        return RatePointsSimilarity(new_points, new_reference);
    }

    int GetPictureCount() { return picture_count; }

    void TakePicture(){
        Vector2 sum = {0,0};
        auto points = GetAllPoints();
        for (auto point : points){
            sum = Vector2Add(sum, point);
        }
        Vector2 center = Vector2Scale(sum, 1.f/points.size());

        float size = 1024;

        RenderTexture2D render = LoadRenderTexture(size, size);
        Camera2D cam = {0};
        cam.target = center;
        cam.offset = (Vector2){size/2.f, size/2.f}; // Offset should be the screen center
        cam.rotation = 0.0f;
        cam.zoom = 1.0f; // Ensure zoom is set correctly
        
        BeginTextureMode(render);
            BeginMode2D(cam);
                ClearBackground(BLANK);
                Draw();
            EndMode2D();
        EndTextureMode();

        RenderTexture2D flipped_render = LoadRenderTexture(size, size);

        BeginTextureMode(flipped_render);
            ClearBackground(BLANK);
            DrawTextureRec(render.texture, Rectangle{0,0,size,size}, Vector2{}, WHITE);
        EndTextureMode();

        Image image = LoadImageFromTexture(flipped_render.texture);
        ExportImage(image, TextFormat("reference_%i.png", picture_count));
        picture_count++;
    }
};