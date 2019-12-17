#include "UI.hpp"
#include "macros.hpp"

using namespace std;

using namespace sf;

void StartGame()
{
      sf::RenderWindow window(sf::VideoMode((boardSize - 1) * colDist + 2 * circleRadius, (boardSize - 1) * rowDist + 2 * circleRadius), "Bridg-It", Style::Titlebar | Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        loadBoard(window);
        window.display();
    }


}



int main()
{


    sf::RenderWindow meniu(sf::VideoMode(800,700), "Bridg-It");
    Meniusetup(meniu);
    centerscreen(meniu);
    return 0;
}

