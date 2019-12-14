#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define circleRadius 20.f
#define colDist 100.f
#define rowDist 100.f
#define boardSize 8



using namespace sf;


int loadBoard(RenderWindow &window){
    CircleShape shape(circleRadius);
    // load the first player's dots
    for(int i = 0; i < boardSize; i++){
        for(int j = 1; j < boardSize; j++){
            shape.setPosition(j * colDist - colDist / 2, i * rowDist);
            window.draw(shape);
        }
    }
    // load the second player's pieces
    shape.setFillColor(Color::Red);
    for(int i = 1; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            shape.setPosition(j * colDist, i * rowDist - rowDist / 2);
            window.draw(shape);
        }
    }

}

int main()
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

    return 0;
}

