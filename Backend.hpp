#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include "macros.hpp"
#include "globalVars.hpp"

using namespace std;

void createBoard();

int getSizeFromStr(string s);

bool isClickValid(sf::Event::MouseButtonEvent mouse);

void linkIfValid(sf::Event::MouseButtonEvent click1, sf::Event::MouseButtonEvent click2);

