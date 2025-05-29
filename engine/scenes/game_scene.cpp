#include "game_scene.hpp"
#include "scene_manager.hpp"
#include "event_bus.hpp"
#include <iostream>

namespace globals
{
    Color PointerColor = WHITE;
}

GameScene::GameScene() : sceneManager(nullptr), eventBus(nullptr)
{
    std::cout << "GameScene created." << std::endl;
}

GameScene::~GameScene()
{
    std::cout << "GameScene destroyed." << std::endl;
}

void GameScene::SetSceneManager(SceneManager *manager)
{
    this->sceneManager = manager;
}

void GameScene::SetEventBus(EventBus *bus)
{
    this->eventBus = bus;
}

void GameScene::Init()
{
    std::cout << "GameScene Init." << std::endl;
    if (!eventBus)
    {
        std::cerr << "GameScene Error: EventBus is not set." << std::endl;
        return;
    }

    auto sortedTeams = teams::SortTeams(eventBus);
    if (sortedTeams.size() < 2)
    {
        std::cerr << "GameScene Error: Not enough teams sorted for initialization." << std::endl;
        Color team1Color1 = RED;
        Color team1Color2 = MAROON;
        Color team2Color1 = BLUE;
        Color team2Color2 = DARKBLUE;

        if (!sortedTeams.empty())
        {
            team1Color1 = sortedTeams[0].Colors[0];
            team1Color2 = sortedTeams[0].Colors[1];
            if (sortedTeams.size() > 1)
            {
                team2Color1 = sortedTeams[1].Colors[0];
                team2Color2 = sortedTeams[1].Colors[1];
            }
            else
            {
                team2Color1 = sortedTeams[0].Colors[0];
                team2Color2 = sortedTeams[0].Colors[1];
            }
        }
        board = boardrenderer::NewDefaultBoard(eventBus, sortedTeams);
        movingGradient = std::make_unique<gradient::MovingGradient>(team2Color2, team1Color2);
        globals::PointerColor = team2Color1;
    }
    else
    {
        board = boardrenderer::NewDefaultBoard(eventBus, sortedTeams);
        movingGradient = std::make_unique<gradient::MovingGradient>(sortedTeams[1].Colors[1], sortedTeams[0].Colors[1]);
        globals::PointerColor = sortedTeams[1].Colors[0];
    }
}

void GameScene::Unload()
{
    std::cout << "GameScene Unload." << std::endl;
    if (board)
    {
        board->Unload();
    }
}

void GameScene::CheckForReroll()
{
    if (IsKeyPressed(KEY_R))
    {
        std::cout << "R key pressed in GameScene. Rerolling." << std::endl;
        if (!eventBus)
        {
            std::cerr << "GameScene Error: EventBus is not set for reroll." << std::endl;
            return;
        }
        auto new_teams = teams::SortTeams(eventBus);
        if (new_teams.size() < 2)
        {
            std::cerr << "GameScene Reroll Error: Not enough teams sorted." << std::endl;
            return;
        }
        board = boardrenderer::NewDefaultBoard(eventBus, new_teams);
        if (movingGradient)
        {
            movingGradient->ChangeColors(new_teams[1].Colors[1], new_teams[0].Colors[1]);
        }
        globals::PointerColor = new_teams[1].Colors[0];
    }
}

void GameScene::Update()
{
    CheckForReroll();
    if (board && eventBus)
    {
        board->HandleInput(eventBus);
    }
    else
    {
        if (!board)
            std::cerr << "GameScene Update Warning: Board is null." << std::endl;
        if (!eventBus)
            std::cerr << "GameScene Update Warning: EventBus is null." << std::endl;
    }
}

void GameScene::DrawInScreen()
{
}

void GameScene::Draw()
{
    if (movingGradient)
    {
        movingGradient->Draw();
    }
    if (board)
    {
        board->Draw();
    }
}

std::string GameScene::GetSceneName() const
{
    return "Game";
}
