
#ifndef ECRANMENU_H
#define ECRANMENU_H

#include <iostream>
#include <vector>
#include "sdlManager.h"

class EcranMenu {
private:
    SDL_Renderer* renderer;
    SDL_Texture* titreTexture;
    std::vector<SDL_Texture*> choixTextures;

    void afficherTitre();
    void afficherChoix();
    void afficherFond();

public:
    EcranMenu(SDL_Renderer* renderer);
    void afficher();
};

#endif // ECRANMENU_H
