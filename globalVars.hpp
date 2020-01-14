#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

extern int boardSize;
extern int pcActive;
extern char **board;
extern sf::Sound firstClickSound, secondClickSound, winSound;
extern sf::Music music;
extern sf::SoundBuffer clickSoundBuffer, winSoundBuffer;
extern sf::RenderWindow window;
extern sf::Color backGroundColor, player1Color, player2Color;
extern sf::RectangleShape backGround;
extern sf::Image ticked, unticked;
extern bool playerRound;
extern bool isMuted;
extern std::string fontPath;
