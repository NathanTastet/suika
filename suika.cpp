#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

enum MenuOption
{
    START,
    OPTIONS,
    SCORES,
    QUIT
};

int main()
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de l'initialisation de SDL: %s", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de l'initialisation de SDL_ttf: %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Suika Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la création de la fenêtre: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la création du renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Surface *backgroundSurface = IMG_Load("menu.png");
    if (!backgroundSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement de l'image de fond: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Créer une texture à partir de l'image de fond
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    if (!backgroundTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la création de la texture de fond: %s", SDL_GetError());
        SDL_FreeSurface(backgroundSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Vérification de la présence d'un joystick
    bool hasJoystick = SDL_NumJoysticks() > 0;
    SDL_Joystick *joystick = nullptr;
    if (hasJoystick)
    {
        // Ouverture du joystick
        joystick = SDL_JoystickOpen(0);
        if (!joystick)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de l'ouverture du joystick: %s", SDL_GetError());
            SDL_DestroyTexture(backgroundTexture);
            SDL_FreeSurface(backgroundSurface);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
        }
    }

    // Boucle principale du jeu
    bool quit = false;
    Uint32 frameStart;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    // Position actuelle dans le menu
    int menuPosition = 0;

    // Variables pour l'animation de mouvement
    int animationOffset = 0;
    int animationDirection = 1;
    const int animationSpeed = 2; // Adjust the animation speed here

    while (!quit)
    {
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_s:
                    case SDLK_DOWN:
                        menuPosition++;
                        if (menuPosition > QUIT)
                        {
                            menuPosition = 0;
                        }
                        break;
                    case SDLK_z:
                    case SDLK_UP:
                        menuPosition--;
                        if (menuPosition < 0)
                        {
                            menuPosition = QUIT;
                        }
                        break;
                    case SDLK_q:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
            else if (hasJoystick && event.type == SDL_JOYBUTTONDOWN)
            {
                switch (event.jbutton.button)
                {
                    case 0: // Button A on joystick
                        SDL_Log("Démarrer le jeu");
                        break;
                    case 1: // Button B on joystick
                        SDL_Log("Options");
                        break;
                    case 2: // Button X on joystick
                        SDL_Log("Tableau des scores");
                        break;
                    case 3: // Button Y on joystick
                        quit = true;
                        break;
                    case 4: // Button L1 on joystick
                    case 5: // Button R1 on joystick
                        menuPosition--;
                        if (menuPosition < 0)
                        {
                            menuPosition = QUIT;
                        }
                        break;
                    case 6: // Button L2 on joystick
                    case 7: // Button R2 on joystick
                        menuPosition++;
                        if (menuPosition > QUIT)
                        {
                            menuPosition = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Afficher l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Charger la police
        TTF_Font* font = TTF_OpenFont("./burbank-big-condensed-black.ttf", 24);
        if (font == nullptr) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
            // Gérer l'erreur de chargement de la police
        }

        // Définir la couleur du texte
        SDL_Color color = {255, 255, 255, 255};

        // Set texture scale mode to nearest neighbor
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        // Afficher le titre du menu
        SDL_Rect titleRect = {100, 50, 400, 100};
        SDL_Surface* surfaceTitle = TTF_RenderText_Solid(font, "Suika Gym", color);
        SDL_Texture* titleMessage = SDL_CreateTextureFromSurface(renderer, surfaceTitle);
        SDL_RenderCopy(renderer, titleMessage, NULL, &titleRect);

        // Définir la taille de police pour les textes
        int fontSize = 50;

        // Afficher le texte pour "Start"
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Jouer", color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect startRect = {100, 200, surfaceMessage->w, surfaceMessage->h};
        SDL_RenderCopy(renderer, message, NULL, &startRect);

        // Afficher le texte pour "Options"
        surfaceMessage = TTF_RenderText_Solid(font, "Options", color);
        message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect optionsRect = {100, 350, surfaceMessage->w, surfaceMessage->h};
        SDL_RenderCopy(renderer, message, NULL, &optionsRect);

        // Afficher le texte pour "Scores"
        surfaceMessage = TTF_RenderText_Solid(font, "Scores", color);
        message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect scoresRect = {100, 500, surfaceMessage->w, surfaceMessage->h};
        SDL_RenderCopy(renderer, message, NULL, &scoresRect);

        // Afficher le texte pour "Quit"
        surfaceMessage = TTF_RenderText_Solid(font, "Quit", color);
        message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect quitRect = {100, 650, surfaceMessage->w, surfaceMessage->h};
        SDL_RenderCopy(renderer, message, NULL, &quitRect);

         // Mettre à jour la couleur du rectangle sélectionné avec animationOffset
        SDL_SetRenderDrawColor(renderer, 255 + animationOffset, 0, 0, 255); // Change color to red for selected rectangle with animationOffset
        switch (menuPosition)
        {
            case START:
                SDL_SetRenderDrawColor(renderer, 255 + animationOffset, 0, 0, 255); // Change color to red for selected rectangle with animationOffset
                SDL_RenderDrawRect(renderer, &startRect);
                break;
            case OPTIONS:
                SDL_SetRenderDrawColor(renderer, 255 + animationOffset, 0, 0, 255); // Change color to red for selected rectangle with animationOffset
                SDL_RenderDrawRect(renderer, &optionsRect);
                break;
            case SCORES:
                SDL_SetRenderDrawColor(renderer, 255 + animationOffset, 0, 0, 255); // Change color to red for selected rectangle with animationOffset
                SDL_RenderDrawRect(renderer, &scoresRect);
                break;
            case QUIT:
                SDL_SetRenderDrawColor(renderer, 255 + animationOffset, 0, 0, 255); // Change color to red for selected rectangle with animationOffset
                SDL_RenderDrawRect(renderer, &quitRect);
                break;
            default:
                break;
        }


        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Mettre à jour l'animation de mouvement
        animationOffset += animationDirection * animationSpeed;
        if (animationOffset >= 10 || animationOffset <= -10)
        {
            animationDirection *= -1;
        }

        // Attendre pour maintenir le taux de rafraîchissement
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Fermeture du joystick
    if (hasJoystick)
    {
        SDL_JoystickClose(joystick);
    }

    // Nettoyage et fermeture de SDL
    SDL_DestroyTexture(backgroundTexture);
    SDL_FreeSurface(backgroundSurface);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
