
#include "../headers/ecranMenu.h"
#include "../headers/constants.h"
#include "../headers/sdlManager.h"



int main() {
    // appelle le constructeur de SDLManager qui va créer la fenêtre SDL
    SDLManager sdlManager;

    // Créer les écrans
    EcranMenu ecranMenu(sdlManager.getRenderer());

    // on s'initialise sur l'écran du menu
    GameState gameState = GameState::MENU;
    // Afficher l'écran du menu
    ecranMenu.afficher();

    // Boucle principale du jeu

    while(gameState != GameState::QUIT){
        switch(gameState){
            case GameState::MENU:
                // Lecture controles cas Menu
                break;
            case GameState::GAME:
                // Lecture controles cas Game
                break;
            case GameState::OPTIONS:
                // Lecture controles cas Options
                break;
            case GameState::SCORE:
                // Lecture controles cas Score
                break;
        }

        // Afficher le frame que 60 fois par seconde, sinon ne rien faire
        sdlManager.checkAffichageFrame();
    }

    // Les destructeurs vont supprimer les variables allouées dynamiquement
    // tout seul, donc pas besoin de les supprimer dans le main
    
    return 0;
}
