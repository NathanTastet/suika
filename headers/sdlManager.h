#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class SDLManager {
public:
    SDLManager();
    ~SDLManager();
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    void checkAffichageFrame();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Uint32 m_lastFrameTime;
};

#endif // SDL_MANAGER_H