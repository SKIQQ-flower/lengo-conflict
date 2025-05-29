#include "menu_scene.hpp"
#include "scene_manager.hpp"
#include "event_bus.hpp"
#include "game_scene.hpp"
#include <iostream>
#include <memory>

MenuScene::MenuScene() : sceneManager(nullptr), eventBus(nullptr)
{
    std::cout << "MenuScene created." << std::endl;
}

MenuScene::~MenuScene()
{
    std::cout << "MenuScene destroyed." << std::endl;
}

void MenuScene::SetSceneManager(SceneManager *manager)
{
    this->sceneManager = manager;
}

void MenuScene::SetEventBus(EventBus *bus)
{
    this->eventBus = bus;
}

void MenuScene::Init()
{
    std::cout << "MenuScene Init." << std::endl;
}

void MenuScene::Unload()
{
    std::cout << "MenuScene Unload." << std::endl;
}

void MenuScene::Update()
{
    if (!sceneManager)
    {
        std::cerr << "MenuScene Error: SceneManager is not set." << std::endl;
        return;
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
    {
        std::cout << "Enter key pressed in MenuScene. Changing to GameScene." << std::endl;
        auto gameScene = std::make_unique<GameScene>();
        sceneManager->SetScene(std::move(gameScene));
    }
}

void MenuScene::DrawInScreen()
{
}

void MenuScene::Draw()
{
    ClearBackground(RAYWHITE);
    DrawText("Menu - Pressione ENTER para comecar", 100, 200, 20, BLACK);
}

std::string MenuScene::GetSceneName() const
{
    return "Menu";
}
