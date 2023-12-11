#include "../headers/ecranMenu.h"
#include <SDL2/SDL_ttf.h>
#include "../headers/constants.h"

EcranMenu::EcranMenu(SDL_Renderer *renderer) : renderer(renderer) {}

void EcranMenu::afficher()
{
    // Code pour afficher l'écran du menu
    afficherTitre();
    afficherChoix();
    afficherFond();
}

void EcranMenu::afficherTitre()
{
    // Code pour afficher le texte de titre en haut à droite
    TTF_Font *titreFont = TTF_OpenFont("../fonts/burbank-big-condensed-black.ttf", 24);
    if (!titreFont) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }
    SDL_Color textColor = {255,255,255}; // Define textColor
    SDL_Surface *titreSurface = TTF_RenderText_Solid(titreFont, "Titre", textColor);
    SDL_Texture *titreTexture = SDL_CreateTextureFromSurface(renderer, titreSurface);
    SDL_FreeSurface(titreSurface);

    int width, height;
    SDL_QueryTexture(titreTexture, NULL, NULL, &width, &height);


    // Afficher la texture du titre
    SDL_Rect titreRect;
    titreRect.x = SCREEN_WIDTH - width;
    titreRect.y = 0;
    titreRect.w = width;
    titreRect.h = height;

    SDL_RenderCopy(renderer, titreTexture, NULL, &titreRect);
}

void EcranMenu::afficherChoix()
{
    // Code pour afficher les choix du menu
    int choixX = MENU_CHOIX_X;
    int choixY = MENU_CHOIX_Y;
    int choixSpacing = MENU_CHOIX_SPACING;

    for (int i = 0; i < choixTextures.size(); i++)
    {
        SDL_Texture *choixTexture = choixTextures[i];
        int width, height;
        SDL_QueryTexture(choixTexture, NULL, NULL, &width, &height);


        // Afficher la texture du choix
        SDL_Rect choixRect;
        choixRect.x = choixX;
        choixRect.y = choixY + (i * (height + choixSpacing));
        choixRect.w = width;
        choixRect.h = height;
        SDL_RenderCopy(renderer, choixTexture, NULL, &choixRect);
    }
}

void EcranMenu::afficherFond()
{
    // Code pour afficher le fond du menu
    SDL_Surface *fondSurface = IMG_Load("../assets/menu.png");
    SDL_Texture *fondTexture = SDL_CreateTextureFromSurface(renderer, fondSurface);
    SDL_FreeSurface(fondSurface);

    // Afficher la texture du fond
    SDL_Rect fondRect;
    fondRect.x = 0;
    fondRect.y = 0;
    fondRect.w = SCREEN_WIDTH;
    fondRect.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer, fondTexture, NULL, &fondRect);
}