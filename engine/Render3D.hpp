#pragma once

#include <raylib.h>

class Render3D {

private:
    // Define the camera to look into our 3d world
    Camera camera = { 0 };

public:

    Render3D() {
        camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
        camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE; 
    }

    void Update();

    void BeginDraw();
    void EndDraw();
};