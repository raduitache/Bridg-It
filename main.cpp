#include "Backend.hpp"
#include "UI.hpp"
#include "globalVars.hpp"

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



    Text startText,scoreText,exitText,settingText,soundText,welcomeText;
    Font myfont;
    if(!myfont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf"))
    {
        cout<<"Errors font, can't loaded"<<endl;
    }

    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFont(myfont);
    welcomeText.setString("Welcome");
    welcomeText.setCharacterSize(80);
    welcomeText.setColor(Color(255,0,0));
   welcomeText.setPosition(240,40);
    ///////////////////////
   startText.setFont(myfont);
    startText.setString("Start");
    startText.setCharacterSize(80);
    startText.setColor(Color(255,0,0));
    startText.setPosition(300,140);
    //////////////////////////
    scoreText.setFont(myfont);
    scoreText.setString("Score");
    scoreText.setCharacterSize(80);
    scoreText.setColor(Color(255,0,0));
    scoreText.setPosition(280,240);
    ///////////////////////
    settingText.setFont(myfont);
    settingText.setString("Setting");
    settingText.setCharacterSize(80);
    settingText.setColor(Color(255,0,0));
    settingText.setPosition(270,340);
    /////////////////////////
    exitText.setFont(myfont);
    exitText.setString("Exit");
    exitText.setCharacterSize(80);
    exitText.setColor(Color(255,0,0));
    exitText.setPosition(310,440);

    while(meniu.isOpen())
    {
        sf::Event event;

         while (meniu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            meniu.close();
        }
        meniu.clear();
        meniu.draw(welcomeText);
        meniu.draw(startText);
        meniu.draw(scoreText);
        meniu.draw(settingText);
        meniu.draw(exitText);
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

    centerscreen(meniu);
       Meniusetup(meniu);





    //startGame();


    //gameOptionsMenu();
     //Meniusetup();
    //centerscreen(meniu);
     //dificultyMeniu();
      //numberOfPlayerMeniu();


    return 0;
}

