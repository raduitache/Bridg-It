#include "Backend.hpp"
#include "UI.hpp"
#include "globalVars.hpp"

using namespace std;

using namespace sf;

void StartGame()
{
    window.create(sf::VideoMode((boardSize - 1) * colDist + 2 * circleRadius, (boardSize - 1) * rowDist + 2 * circleRadius), "Bridg-It", Style::Titlebar | Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    linkDots(event.mouseButton);
                }
            }
        }

        window.clear();
        loadBoard();
        window.display();
    }


}



int main()
{
    boardSize = 8;
    createBoard();
    //StartGame();
    window.create(sf::VideoMode(800,700), "Bridg-It");
    Meniusetup();
    //centerscreen(meniu);
    return 0;
}

