#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

extern int boardSize;
extern char **board;
extern sf::RenderWindow window;
extern sf::Color backGroundColor, player1Color, player2Color;
extern sf::RectangleShape backGround;
extern sf::Image ticked, unticked;
extern bool playerRound;
extern bool isMuted;

