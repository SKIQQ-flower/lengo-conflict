#pragma once

#include <string>
#include "raylib.h"
#include <toml++/toml.hpp>

struct WindowConfig
{
    int WindowWidth = 800;
    int WindowHeight = 600;
    int ViewportWidth = 800;
    int ViewportHeight = 600;
};

struct GameConfig
{
    std::string *GameName = new std::string("My Game");
    std::string *GameVersion = new std::string("1.0.0");
};

struct Config
{
    WindowConfig window;
    GameConfig game;

    static Config LoadConfig(const std::string &path = "config.toml")
    {
        Config cfg;

        try
        {
            auto tbl = toml::parse_file(path);

            if (auto win = tbl["window"].as_table())
            {
                if (auto w = win->get_as<int>("WindowWidth"))
                    cfg.window.WindowWidth = *w;
                if (auto h = win->get_as<int>("WindowHeight"))
                    cfg.window.WindowHeight = *h;
                if (auto vw = win->get_as<int>("ViewportWidth"))
                    cfg.window.ViewportWidth = *vw;
                if (auto vh = win->get_as<int>("ViewportHeight"))
                    cfg.window.ViewportHeight = *vh;
            }

            if (auto game = tbl["game"].as_table())
            {
                if (auto name = game->get_as<std::string>("GameName"))
                    cfg.game.GameName = new std::string(*name);
            }
        }
        catch (const toml::parse_error &err)
        {
            TraceLog(LOG_ERROR, "TOML parse error: %s", err.description());
        }

        return cfg;
    }
};
