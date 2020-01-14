#include "globalVars.hpp"

int boardSize;
char **board;
sf::Sound firstClickSound, secondClickSound, winSound;
sf::Music music;
sf::SoundBuffer clickSoundBuffer, winSoundBuffer;
sf::RenderWindow window;
sf::RectangleShape backGround;
sf::Image ticked, unticked;
sf::Color backGroundColor, player1Color, player2Color;
bool playerRound = 0;
bool isMuted;
std::string fontPath;
