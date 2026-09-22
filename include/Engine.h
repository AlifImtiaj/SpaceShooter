#pragma once
#include <string>

#include <SDL3/SDL.h>

class Engine {
private:
// private variables
    SDL_Window * m_window = nullptr;
    SDL_Renderer * m_renderer = nullptr;

    SDL_Event m_event;

    float m_targetFPS = 60;

    bool m_isEverythingReady = false;
    bool m_isGameRunning = false;

public:
// public variable and constructor, destructor (at the end)


    Engine() = default;
    Engine(int width, int height, const std::string& windowTitle);
    ~Engine();

private:
// private functions
    void Start();
    void HandleEvent();
    void Update();
    void Render();
    void Tick();

public:
// public functions
    void Run();
};