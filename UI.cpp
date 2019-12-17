#include "UI.hpp"



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
