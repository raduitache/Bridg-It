#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "macros.hpp"
#include "globalVars.hpp"

using namespace sf;
using namespace std;


void loadBoard();

void Meniusetup();

void centerscreen(RenderWindow &meniu);

void drawLinks(int i, int j);

void gameOptionsMenu();

void setGameOptionsMenuEntities(Text entries[], RectangleShape &highlighter, RectangleShape &textBox, Font &myFont);

