#include <sstream>
#include <string>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>
#include "macros.hpp"
#include "globalVars.hpp"
#include "dataStructures.hpp"

using namespace std;

void createBoard();

int getSizeFromStr(string s);

bool isClickValid(sf::Event::MouseButtonEvent mouse);

unsigned linkIfValid(sf::Event::MouseButtonEvent click1, sf::Event::MouseButtonEvent click2);

unsigned gameOver(bool player);

bool BFS(queue &q, bool player);

void setPrerequisites();

int getNumberOfFonts();

void setFonts(string entries[], int n);

void saveSettings();
