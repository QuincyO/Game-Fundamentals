#include <SDL_image.h>


SDL_Texture* playerSprite, enemySprite, projectileShips, bossSprite;
SDL_Rect* playerSpriteSRC, enemySpriteSRC, projectileShipsSRC, bossSpriteSRC;
SDL_Rect* playerSpriteDST, enemySpriteDST, projectileShipsDST, bossSpriteSRC;



playerSprite = IMG_LoadTexture(pRenderer,"../Assets/PNG/playerShip1_blue.png");