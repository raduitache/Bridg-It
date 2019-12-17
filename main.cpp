#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define circleRadius 20.f
#define colDist 100.f
#define rowDist 100.f
#define boardSize 8

using namespace std;

using namespace sf;

void loadBoard(RenderWindow &window){
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

    Text startText, scoreText, exitText, settingText, soundText;
    Font myfont;
    if(!myfont.loadFromFile("Roboto-Italic.ttf"))
    {
        cout<<"Errors font, can't loaded"<<endl;
    }
    startText.setFont(myfont);
    startText.setString("Start");
    startText.setCharacterSize(80);
    startText.setColor(Color(255,0,0));
    startText.setPosition(300,40);
    //////////////////////////
    startText.setFont(myfont);
    startText.setString("Score");
    startText.setCharacterSize(80);
    startText.setColor(Color(255,0,0));
    startText.setPosition(280,160);
    ///////////////////////
    settingText.setFont(myfont);
    settingText.setString("Setting");
    settingText.setCharacterSize(80);
    settingText.setColor(Color(255,0,0));
    settingText.setPosition(270,280);
    /////////////////////////
    exitText.setFont(myfont);
    exitText.setString("Exit");
    exitText.setCharacterSize(80);
    exitText.setColor(Color(255,0,0));
    exitText.setPosition(310,400);
    /////////////////////////
    soundText.setFont(myfont);
    soundText.setString("Sound");
    soundText.setCharacterSize(80);
    soundText.setColor(Color(255,0,0));
    soundText.setPosition(280,520);

    while(meniu.isOpen())
    {
        sf::Event event;

         while (meniu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            meniu.close();
        }
        meniu.clear();
        meniu.draw(startText);
        meniu.draw(scoreText);
        meniu.draw(settingText);
        meniu.draw(exitText);
        meniu.draw(soundText);
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

