#include "PixelPerfect.hpp"
#include <cmath>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

void PixelPerfect::SetResolutions(int virtualWidth, int virtualHeight, int WindowWidth, int WindowHeight){
    virtualScreenWidth = virtualWidth;
    virtualScreenHeight = virtualHeight;
    aspect = float(virtualScreenWidth) / virtualScreenHeight;
    DefaultWidth = WindowWidth;
    DefaultHeight = WindowHeight;

    virtualRatio = std::min(
        float(WindowWidth) / virtualScreenWidth,
        float(WindowHeight) / virtualScreenHeight
    );

    RenderTarget = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    sourceRec = { 0.0f, 0.0f, (float)RenderTarget.texture.width, -(float)RenderTarget.texture.height };
}

PixelPerfect::PixelPerfect(){
    PixelCamera = {{}, {}, 0};  // Game world camera
    PixelCamera.zoom = 1.0f;
    SmoothCamera = {{}, {}, 0}; // Smoothing camera
    SmoothCamera.zoom = 1.0f;

    origin = { 0.0f, 0.0f };

    cameraX = 0.0f;
    cameraY = 0.0f;

    WorldMousePos = {0.f ,0.f};
}

PixelPerfect::PixelPerfect(int virtualWidth, int virtualHeight, int WindowWidth, int WindowHeight){
    PixelPerfect();

    SetResolutions(virtualWidth, virtualHeight, WindowWidth, WindowHeight);
}

void PixelPerfect::Update(){
        // Set the camera's target to the values computed above
        SmoothCamera.target = (Vector2){ cameraX, cameraY };

        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        PixelCamera.target.x = truncf(SmoothCamera.target.x);
        SmoothCamera.target.x -= PixelCamera.target.x;
        SmoothCamera.target.x *= virtualRatio;


        PixelCamera.target.y = truncf(SmoothCamera.target.y);
        SmoothCamera.target.y -= PixelCamera.target.y;
        SmoothCamera.target.y *= virtualRatio;

        //----------------------------------------------------------------------------------
        // Update render destination rectangle
        virtualRatio = (float)GetScreenWidth() / virtualScreenWidth;
        new_window_width = std::min((float)GetScreenWidth(), GetScreenHeight() * aspect);

        //because we are updating render window we update virtual ratio
        virtualRatio = std::min(
            new_window_width / virtualScreenWidth,
            new_window_width / aspect / virtualScreenHeight
        );


        destRec = {
        -virtualRatio,
        -virtualRatio,
        new_window_width + (virtualRatio*2),
        new_window_width / aspect + (virtualRatio*2)
        };

        //----------------------------------------------------------------------------------
        //Calculate mouse position in world space
        
        //int borderX = GetScreenWidth() - new_window_width;
        //int borderY = GetScreenHeight() - new_window_width / aspect;

        WorldMousePos = {
        cameraX + GetMousePosition().x / virtualRatio / SmoothCamera.zoom,
        cameraY + GetMousePosition().y / virtualRatio / SmoothCamera.zoom
        };
}

void PixelPerfect::BeginDraw(){
    BeginTextureMode(RenderTarget);
        BeginMode2D(PixelCamera);
}

void PixelPerfect::EndDraw(){
        EndMode2D();
    EndTextureMode();
}

void PixelPerfect::DrawResult()
{
    BeginMode2D(SmoothCamera);
        DrawTexturePro(RenderTarget.texture, sourceRec, destRec, origin, 0.0f, WHITE);
    EndMode2D();
}

Vector2 PixelPerfect::GetMouseWorldPos(){
    return WorldMousePos;
}

void PixelPerfect::SetZoom(float zoom, float min_zoom, float max_zoom){
    SmoothCamera.zoom = std::max(min_zoom, zoom);
    SmoothCamera.zoom = std::min(max_zoom, zoom);
}

bool PixelPerfect::AddZoomInto(float zoom, float min_zoom, float max_zoom, Vector2 pos){
    if (min_zoom <= SmoothCamera.zoom + zoom && max_zoom >= SmoothCamera.zoom + zoom)
    {
        SmoothCamera.zoom += zoom;
        
        if (zoom != 0)
        {
            cameraX = pos.x - virtualScreenWidth / SmoothCamera.zoom / 2.f;
            cameraY = pos.y - virtualScreenHeight / SmoothCamera.zoom / 2.f;
            return true;
        }
    }    
    return false;
}

float PixelPerfect::GetZoom(){
    return SmoothCamera.zoom;
}

float PixelPerfect::GetVirtualRatio(){
    return virtualRatio;
}

void PixelPerfect::MoveCamera(float x, float y){
    cameraX += x;
    cameraY += y;
}

void PixelPerfect::MoveCameraV(Vector2 move){
    cameraX += move.x;
    cameraY += move.y;
}

void PixelPerfect::SetCameraPos(float x, float y){
    cameraX = x;
    cameraY = y;
}

void PixelPerfect::SetCameraPosV(Vector2 pos){
    cameraX = pos.x;
    cameraY = pos.y;
}

Vector2 PixelPerfect::ScreenToWorld(float x, float y){
    return Vector2 {
    cameraX + x / virtualRatio / SmoothCamera.zoom,
    cameraY + y / virtualRatio / SmoothCamera.zoom
    };
}

Vector2 PixelPerfect::ScreenToWorldV(Vector2 Screen){
    return ScreenToWorld(Screen.x, Screen.y);
}

Vector2 PixelPerfect::WorldToScreen(float x, float y){
    return Vector2{
        (x - cameraX) * virtualRatio * SmoothCamera.zoom,
        (y - cameraY) * virtualRatio * SmoothCamera.zoom
    };
}

Vector2 PixelPerfect::WorldToScreenV(Vector2 World){
    return WorldToScreen(World.x, World.y);
}

Vector2 PixelPerfect::GetWorldCameraPos(){
    return PixelCamera.target;
}

Vector2 PixelPerfect::GetSmoothCameraPos(){
    return Vector2{
        cameraX,
        cameraY
    };
}

Vector2 PixelPerfect::GetCameraCenter(){
    return Vector2{
        GetSmoothCameraPos().x + GetVirtualWidth()/2.f * GetZoom(),
        GetSmoothCameraPos().y + GetVirtualHeight()/2.f * GetZoom(),
    };
}

void PixelPerfect::SetCameraCenter(Vector2 center){
    SetCameraPosV(
        Vector2Subtract(center, Vector2
            {
            GetVirtualWidth()/2.f / GetZoom(),
            GetVirtualHeight()/2.f / GetZoom()
            }
        )
    );
}

void PixelPerfect::Unload(){
    UnloadRenderTexture(RenderTarget);
}