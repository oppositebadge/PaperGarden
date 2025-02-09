#include "Render3D.hpp"
#include <raylib.h>

void Render3D::Update(){
    UpdateCamera(&camera, CAMERA_ORBITAL);    
}

void Render3D::BeginDraw(){
    BeginMode3D(camera);
}

void Render3D::EndDraw(){
    EndMode3D();
}