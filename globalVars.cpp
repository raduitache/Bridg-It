#include "globalVars.hpp"

int boardSize;
char **board;
sf::Sound firstClickSound, secondClickSound;
sf::Music music;
sf::SoundBuffer soundBuffer;
sf::RenderWindow window;
sf::RectangleShape backGround;
sf::Image ticked, unticked;
sf::Color backGroundColor, player1Color = sf::Color::White, player2Color = sf::Color::Red;
bool playerRound = 0;
bool isMuted = 0;
std::string fontPath;
