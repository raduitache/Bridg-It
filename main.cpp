#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define circleRadius 10.f
#define colDist 60.f
#define rowDist 60.f



using namespace sf;


int loadBoard(RenderWindow &window){
    CircleShape shape(circleRadius);
    // load the first player's dots
    for(int i = 0; i < 5; i++){
        for(int j = 1; j < 5; j++){
            shape.setPosition(j * colDist - colDist / 2, i * rowDist);
            window.draw(shape);
        }
    }
    // load the second player's pieces
    shape.setFillColor(Color::Red);
    for(int i = 1; i < 5; i++){
        for(int j = 0; j < 5; j++){
            shape.setPosition(j * colDist, i * rowDist - rowDist / 2);
            window.draw(shape);
        }
    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Bridg-It");
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

