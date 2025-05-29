#pragma once

#include "scene.hpp"
#include <raylib-cpp.hpp>
#include <string>
#include <memory>

class EventBus;
struct Config;

class SceneManager
{
public:
    SceneManager(EventBus *bus, const Config &config);
    ~SceneManager();

    void SetScene(std::unique_ptr<Scene> newScene);
    void InitCurrentScene();
    void UpdateCurrentScene();
    void DrawCurrentScene();
    void DrawCurrentSceneInScreen();

    Scene *GetCurrentScene() const;

private:
    std::unique_ptr<Scene> currentScene;
    EventBus *eventBus;
    const Config &gameConfig;
};
