#pragma once
#include <raylib.h>

class PixelPerfect
{
public:
    void SetResolutions(int virtualWidth, int virtualHeight, int WindowWidth, int WindowHeight);

    PixelPerfect();
    PixelPerfect(int virtualWidth, int virtualHeight, int WindowWidth, int WindowHeight); //constructor

    void Update();

    void BeginDraw();
    void EndDraw();

    void DrawResult();

    Vector2 GetMouseWorldPos();

    void SetZoom(float zoom, float min_zoom = 1.f, float max_zoom = 3.f);
    bool AddZoomInto(float zoom, float min_zoom = 1.f, float max_zoom = 3.f, Vector2 pos = {});

    float GetZoom();
    float GetVirtualRatio();

    void MoveCamera(float x, float y);
    void MoveCameraV(Vector2 move);

    void SetCameraPos(float x, float y);
    void SetCameraPosV(Vector2 pos);

    Vector2 ScreenToWorld(float x, float y);
    Vector2 ScreenToWorldV(Vector2 Screen);

    Vector2 WorldToScreen(float x, float y);
    Vector2 WorldToScreenV(Vector2 World);

    Vector2 GetWorldCameraPos();
    Vector2 GetSmoothCameraPos();

    Vector2 GetCameraCenter();
    void SetCameraCenter(Vector2 center);

    void Unload();

    inline int GetVirtualWidth() { return virtualScreenWidth; };
    inline int GetVirtualHeight() { return virtualScreenHeight; };

private:
    int virtualScreenWidth;
    int virtualScreenHeight;
    float aspect;
    int DefaultWidth;
    int DefaultHeight;
    float virtualRatio;

    Camera2D PixelCamera;
    Camera2D SmoothCamera;

    RenderTexture2D RenderTarget;

    Rectangle sourceRec;
    Rectangle destRec;
    float new_window_width = 0.f;

    Vector2 origin;
    float cameraX;
    float cameraY;
    Vector2 WorldMousePos;
};