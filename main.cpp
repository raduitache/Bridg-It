#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define circleRadius 20.f
#define colDist 100.f
#define rowDist 100.f
#define boardSize 8

using namespace std;

using namespace sf;

void loadGame(RenderWindow &window){
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

void Meniusetup(RenderWindow &meniu)
{

    Text Starttext,Scoretext,Exittext,Settingtext;
    Font myfont;
    if(!myfont.loadFromFile("Roboto-Italic.ttf"))
    {
        cout<<"Errors font, can't loaded"<<endl;
    }
    Starttext.setFont(myfont);
    Starttext.setString("Start");
    Starttext.setCharacterSize(80);
    Starttext.setColor(Color(255,0,0));
    Starttext.setPosition(10,80);
    //////////////////////////
    Scoretext.setFont(myfont);
    Scoretext.setString("Score");
    Scoretext.setCharacterSize(50);
    Scoretext.setColor(Color(255,0,0));
    Scoretext.setPosition(250,100);
    ///////////////////////
    Settingtext.setFont(myfont);
    Settingtext.setString("Setting");
    Settingtext.setCharacterSize(50);
    Settingtext.setColor(Color(255,0,0));
    Settingtext.setPosition(150,100);
    /////////////////////////
    while(meniu.isOpen())
    {
        sf::Event event;

         while (meniu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            meniu.close();
        }
        meniu.clear();
        meniu.draw(Starttext);
        meniu.draw(Scoretext);
        meniu.display();

    }
}

void centerscreen(RenderWindow &window)
{
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5,
                                     sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

}

int main()
{


    sf::RenderWindow meniu(sf::VideoMode(800,700), "Bridg-It");
       Meniusetup(meniu);
       centerscreen(meniu);

    return 0;
}

