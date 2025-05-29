#pragma once

#include "scene.hpp"
#include "raylib.h"
#include <string>
#include <memory>
#include <iostream>
#include <vector>

class SceneManager;
class EventBus;

namespace globals
{
    extern Color PointerColor;
}

namespace teams
{
    struct Team
    {
        Color Colors[2];
    };
    inline std::vector<Team> SortTeams(EventBus *bus)
    {
        std::cout << "Stub: SortTeams called." << std::endl;
        return {
            {
                {RED, MAROON},
            },
            {
                {BLUE, DARKBLUE},
            }};
    }
}

namespace boardrenderer
{
    class Board
    {
    public:
        Board(EventBus *bus, const std::vector<teams::Team> &teams_data)
        {
            std::cout << "Stub: Board created." << std::endl;
        }
        ~Board() { Unload(); }
        void HandleInput(EventBus *bus) {}
        void Draw() {}
        void Unload() { std::cout << "Stub: Board Unloaded." << std::endl; }
    };
    inline std::unique_ptr<Board> NewDefaultBoard(EventBus *bus, const std::vector<teams::Team> &teams_data)
    {
        return std::make_unique<Board>(bus, teams_data);
    }
}

namespace gradient
{
    class MovingGradient
    {
    public:
        MovingGradient(Color c1, Color c2) { std::cout << "Stub: MovingGradient created." << std::endl; }
        void ChangeColors(Color c1, Color c2) { std::cout << "Stub: MovingGradient ChangeColors." << std::endl; }
        void Draw() {}
    };
}

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene() override;

    void Init() override;
    void Update() override;
    void Draw() override;
    void DrawInScreen() override;
    void Unload() override;
    std::string GetSceneName() const override;

    void SetSceneManager(SceneManager *manager) override;
    void SetEventBus(EventBus *bus) override;

private:
    void CheckForReroll();

    SceneManager *sceneManager;
    EventBus *eventBus;

    std::unique_ptr<boardrenderer::Board> board;
    std::unique_ptr<gradient::MovingGradient> movingGradient;
};
