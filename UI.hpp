#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Backend.hpp"
#include "macros.hpp"
#include "globalVars.hpp"

using namespace sf;
using namespace std;

void startGame();

void loadBoard();

void Meniusetup();

void centerscreen(RenderWindow &meniu);

void drawLinks(int i, int j);

void gameOptionsMenu();

void setGameOptionsMenuEntities(Text entries[], RectangleShape &highlighter, RectangleShape &textBox, Font &myFont);

void setSelection(int &selection, Event::MouseButtonEvent mouse, Text entries[], Font &myFont);

void linkDots(sf::Event::MouseButtonEvent mouse);

void dificultyMeniu();

void numberOfPlayerMenu();
