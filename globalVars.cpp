#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int boardSize;
char **board;
sf::RenderWindow window;
sf::RectangleShape backGround;
sf::Image ticked, unticked;
sf::Color backGroundColor, player1Color = sf::Color::White, player2Color = sf::Color::Red;
bool playerRound = 0;

bool isMuted = 0;
