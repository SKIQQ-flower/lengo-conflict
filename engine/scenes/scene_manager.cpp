#include "scene_manager.hpp"
#include "event_bus.hpp"
#include "../config.hpp"
#include <iostream>
#include <toml++/toml.hpp>

SceneManager::SceneManager(EventBus *bus, const Config &config)
    : currentScene(nullptr), eventBus(bus), gameConfig(config)
{
}

SceneManager::~SceneManager()
{
    if (currentScene)
    {
        currentScene->Unload();
    }
}

void SceneManager::SetScene(std::unique_ptr<Scene> newScene)
{
    if (newScene)
    {
        if (currentScene)
        {
            currentScene->Unload();
        }
        currentScene = std::move(newScene);
        currentScene->SetSceneManager(this);
        currentScene->SetEventBus(eventBus);

        std::string windowTitle = gameConfig.game.GameName + " : " + currentScene->GetSceneName();
        SetWindowTitle(windowTitle.c_str());

        currentScene->Init();
        std::cout << "Scene set to: " << currentScene->GetSceneName() << std::endl;
    }
    else
    {
        std::cout << "Attempted to set a null scene." << std::endl;
    }
}

void SceneManager::InitCurrentScene()
{
    if (currentScene)
    {
        currentScene->Init();
    }
}

void SceneManager::UpdateCurrentScene()
{
    if (currentScene)
    {
        currentScene->Update();
    }
}

void SceneManager::DrawCurrentScene()
{
    if (currentScene)
    {
        currentScene->Draw();
    }
}

void SceneManager::DrawCurrentSceneInScreen()
{
    if (currentScene)
    {
        currentScene->DrawInScreen();
    }
}

Scene *SceneManager::GetCurrentScene() const
{
    return currentScene.get();
}
