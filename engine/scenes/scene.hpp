#pragma once

#include <string>

class SceneManager;
class EventBus;

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void DrawInScreen() = 0;
    virtual void Unload() = 0;
    virtual std::string GetSceneName() const = 0;
    virtual void SetSceneManager(SceneManager *manager) = 0;
    virtual void SetEventBus(EventBus *bus) = 0;
};
