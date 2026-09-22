#include "Engine.h"
#include <chrono>

Engine::Engine(int width, int height, const std::string &windowTitle) {
    m_isEverythingReady = true;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL Init failed. Error: %s\n", SDL_GetError());
        m_isEverythingReady = false;
    }
    if (m_isEverythingReady) {
        m_window = SDL_CreateWindow(windowTitle.c_str(), width, height, SDL_WINDOW_RESIZABLE);
        if (!m_window) {
            SDL_Log("SDL Window Create Failed. Error: %s\n", SDL_GetError());
            m_isEverythingReady = false;
        }
    }
    if (m_isEverythingReady) {
        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (!m_window) {
            SDL_Log("SDL Renderer Create Failed. Error: %s\n", SDL_GetError());
            m_isEverythingReady = false;
        }
    }
    m_isGameRunning = true;
}

Engine::~Engine() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
}


void Engine::Start() {
    return;
}

void Engine::HandleEvent() {
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_EVENT_QUIT:
                m_isGameRunning = false;
                break;
            /** FPS CHANGE MID GAME 
            case SDL_EVENT_KEY_DOWN:
                switch (m_event.key.scancode)
                {
                case SDL_SCANCODE_1:
                    m_targetFPS = 60;
                    break;
                case SDL_SCANCODE_2:
                    m_targetFPS = 90;
                    break;
                case SDL_SCANCODE_3:
                    m_targetFPS = 120;
                    break;
                case SDL_SCANCODE_4:
                    m_targetFPS = 144;
                    break;
                
                
                default:
                    break;
                }
            */
            default:
                break;
        }
    }
}

void Engine::Update() {
    return;
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_renderer, 255,255,255,255);

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Engine::Tick() {
    HandleEvent();
    Update();
    Render();
}

void Engine::Run() {
    if (m_isEverythingReady) {
        Start();

        while (m_isGameRunning) {
            auto start = std::chrono::steady_clock::now();
            Tick();
            auto end = std::chrono::steady_clock::now();
            double elapsedTime = std::chrono::duration<double, std::milli>(end - start).count();
            double desiderFrametime = 1000 / m_targetFPS;
            double waitTime = desiderFrametime - elapsedTime;
            if (waitTime > 0.0) {
                SDL_Delay(static_cast<Uint32>(waitTime));
            }
        }
    }
}
