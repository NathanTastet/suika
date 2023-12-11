#include <SDL2/SDL.h>

int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de l'initialisation de SDL: %s", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Mon jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la création de la fenêtre: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Boucle principale du jeu
    bool quit = false;
    Uint32 frameStart;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (!quit) {
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Mettre à jour le jeu

        // Dessiner le jeu

        // Attendre pour maintenir le taux de rafraîchissement
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Nettoyage et fermeture de SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
