#include "../headers/sdlManager.h"
#include <iostream>
#include "../headers/constants.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDLManager::SDLManager() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "Erreur lors de l'initialisation de SDL: " << SDL_GetError() << std::endl;
        // Gérer l'erreur
    }

    if (TTF_Init() < 0) {
        std::cout << "Erreur lors de l'initialisation de SDL_ttf: " << TTF_GetError() << std::endl;
        // Gérer l'erreur
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cout << "Erreur lors de l'initialisation de SDL_image: " << IMG_GetError() << std::endl;
        // Gérer l'erreur
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Erreur lors de l'initialisation de SDL_mixer: " << Mix_GetError() << std::endl;
        // Gérer l'erreur
    }

    m_window = SDL_CreateWindow("Suika Gym", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cout << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
        // Gérer l'erreur
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cout << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
        // Gérer l'erreur
    }
    
}

SDL_Renderer* SDLManager::getRenderer() const {
    return m_renderer;
}

SDL_Window* SDLManager::getWindow() const {
    return m_window;
}

SDLManager::~SDLManager() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void SDLManager::checkAffichageFrame() {
    // Afficher le frame que 60 fois par seconde, sinon ne rien faire

    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 elapsedFrameTime = currentFrameTime - m_lastFrameTime;

    if (elapsedFrameTime >= FRAME_DELAY) {
        m_lastFrameTime = currentFrameTime;
        SDL_RenderPresent(m_renderer);
    }
}
