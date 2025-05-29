#include "raylib-cpp.hpp"
#include "./engine/scenes/scene_manager.hpp"
#include "./engine/scenes/menu_scene.hpp"
#include "./engine/scenes/game_scene.hpp"
#include "./engine/scenes/event_bus.hpp"
#include "./engine/config.hpp"
#include "./engine/globals.hpp"
#include <memory>
#include <iostream>

namespace pointer
{
    class Pointer
    {
    public:
        Pointer(Texture2D pressedTex, Texture2D regularTex)
            : pressedTexture(pressedTex), regularTexture(regularTex)
        {
            std::cout << "Stub: Pointer created." << std::endl;
        }
        ~Pointer()
        {
            Unload();
        }

        void DrawPointer()
        {
            Vector2 mousePos = GetMousePosition();
            Texture2D currentTexture = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? pressedTexture : regularTexture;

            DrawTexture(currentTexture, (int)mousePos.x, (int)mousePos.y, WHITE);
        }

        void Unload()
        {
            std::cout << "Stub: Pointer Unloaded (textures managed by caller in this stub)." << std::endl;
        }

    private:
        Texture2D pressedTexture;
        Texture2D regularTexture;
    };

    inline std::unique_ptr<Pointer> NewPointer(Texture2D pressedTex, Texture2D regularTex)
    {
        return std::make_unique<Pointer>(pressedTex, regularTex);
    }
}

namespace globals
{
    Texture2D ContainerNPatchTexture;

    void InitializeGlobals()
    {
        ContainerNPatchTexture = LoadTexture("./assets/sprites/npatchs/container.png");
        if (ContainerNPatchTexture.id == 0)
        {
            std::cerr << "Failed to load ./assets/sprites/npatchs/container.png" << std::endl;
        }
        PointerColor = WHITE;
    }

    void UnloadGlobals()
    {
        UnloadTexture(ContainerNPatchTexture);
    }
}

int main()
{
    EventBus signalBus;
    Config cfg = Config::LoadConfig();

    InitWindow(cfg.window.WindowWidth, cfg.window.WindowHeight, cfg.game.GameName.c_str());
    SetTargetFPS(60);

    globals::InitializeGlobals();

    Image icon = LoadImage("assets/sprites/gameicon.png");
    if (icon.data != nullptr)
    {
        SetWindowIcon(icon);
        UnloadImage(icon);
    }
    else
    {
        std::cerr << "Failed to load game icon: assets/sprites/gameicon.png" << std::endl;
    }

    float virtualW = static_cast<float>(cfg.window.ViewportWidth);
    float virtualH = static_cast<float>(cfg.window.ViewportHeight);
    RenderTexture2D renderTexture = LoadRenderTexture(static_cast<int>(virtualW), static_cast<int>(virtualH));
    if (renderTexture.id == 0)
    {
        std::cerr << "Failed to load render texture." << std::endl;
        CloseWindow();
        return -1;
    }

    Texture2D pointerPressedTex = LoadTexture("./assets/sprites/pointer/pressed.png");
    Texture2D pointerRegularTex = LoadTexture("./assets/sprites/pointer/regular.png");
    if (pointerPressedTex.id == 0)
        std::cerr << "Failed to load ./assets/sprites/pointer/pressed.png" << std::endl;
    if (pointerRegularTex.id == 0)
        std::cerr << "Failed to load ./assets/sprites/pointer/regular.png" << std::endl;

    std::unique_ptr<pointer::Pointer> gamePointer = pointer::NewPointer(pointerPressedTex, pointerRegularTex);

    SceneManager sceneManager(&signalBus, cfg);

    auto menu = std::make_unique<MenuScene>();
    sceneManager.SetScene(std::move(menu));

    while (!WindowShouldClose())
    {
        sceneManager.UpdateCurrentScene();

        BeginTextureMode(renderTexture);
        ClearBackground(BLACK);

        sceneManager.DrawCurrentScene();

        if (gamePointer)
        {
            gamePointer->DrawPointer();
        }

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);

        float screenW = static_cast<float>(GetScreenWidth());
        float screenH = static_cast<float>(GetScreenHeight());
        float scale = std::min(screenW / virtualW, screenH / virtualH);

        Rectangle srcRect = {0.0f, 0.0f, virtualW, -virtualH};
        Rectangle destRect = {
            (screenW - (virtualW * scale)) * 0.5f,
            (screenH - (virtualH * scale)) * 0.5f,
            virtualW * scale,
            virtualH * scale};
        Vector2 origin = {0.0f, 0.0f};

        DrawTexturePro(renderTexture.texture, srcRect, destRect, origin, 0.0f, WHITE);

        sceneManager.DrawCurrentSceneInScreen();

        EndDrawing();
    }

    if (gamePointer)
    {
    }
    UnloadTexture(pointerPressedTex);
    UnloadTexture(pointerRegularTex);

    globals::UnloadGlobals();
    UnloadRenderTexture(renderTexture);

    CloseWindow();

    return 0;
}