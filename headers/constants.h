#ifndef CONSTANTS_H
#define CONSTANTS_H

// état actuel du jeu :
enum class GameState {
    MENU,
    GAME,
    SCORE,
    OPTIONS,
    QUIT
};

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MENU_CHOIX_X 50
#define MENU_CHOIX_Y 100
#define MENU_CHOIX_SPACING 20

#define FRAME_RATE 60
#define FRAME_DELAY 1000 / FRAME_RATE

#endif
