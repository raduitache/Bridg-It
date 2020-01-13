#include <cmath>
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "globalVars.hpp"
#include "Backend.hpp"
#include "macros.hpp"

using namespace sf;
using namespace std;

void startGame();

void loadBoard();

void Meniusetup();

void centerscreen(RenderWindow &meniu);

void drawLinks(int i, int j);

void gameOptionsMenu();

void setGameOptionsMenuEntities(Text entries[], Font &myFont, int selection);

void setSelection(int &selection, Event::MouseButtonEvent mouse, Text entries[], Font &myFont);

unsigned linkDots(sf::Event::MouseButtonEvent mouse);

void dificultyMenu();

void numberOfPlayerMenu();

void showWinner(unsigned u);

void settingsMenu();

void setSettingsMenuEntries(Text entries[], Font &font, int &selection, Texture &myTick, RectangleShape &checkBox, Image &ticked, Image &unticked);

void selectFontMenu();

void selectPlayerColorsMenu();
