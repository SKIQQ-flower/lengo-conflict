#pragma once

#include "scene.hpp"
#include "raylib.h"
#include <string>

class SceneManager;
class EventBus;
class GameScene;

class MenuScene : public Scene
{
public:
    MenuScene();
    ~MenuScene() override;

    void Init() override;
    void Update() override;
    void Draw() override;
    void DrawInScreen() override;
    void Unload() override;
    std::string GetSceneName() const override;

    void SetSceneManager(SceneManager *manager) override;
    void SetEventBus(EventBus *bus) override;

private:
    SceneManager *sceneManager;
    EventBus *eventBus;
};
