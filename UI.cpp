#include "UI.hpp"


using namespace sf;


void drawLinks(int i, int j){
    char player;
    Color culoare;
    if(board[i][j] == '1'){
        player = 'x';
        culoare = Color::White;
    }
    else if(board[i][j] == '2'){
        player = 'y';
        culoare = Color::Red;
    }
    else return;

    if(board[i][j-1] == player && board[i][j+1] == player){

        // build link shape and draw it
        RectangleShape link(Vector2f(colDist, linkWidth));
        link.setPosition((j - 1) * (colDist / 2) + circleRadius, i * (rowDist / 2) + circleRadius);
        link.setFillColor(culoare);
        window.draw(link);
    }

    // or a vertical one
    else if(board[i - 1][j] == player && board[i + 1][j] == player){

        // build link shape and draw
        RectangleShape link(Vector2f(linkWidth, rowDist));
        link.setPosition(j * (colDist / 2) + circleRadius, (i - 1) * (rowDist / 2) + circleRadius);
        link.setFillColor(culoare);
        window.draw(link);
    }

}

void loadBoard(){
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

    // load links for the first player
    for(int i = 0; i < 2 * boardSize - 1; i++){
        for(int j = 0; j < 2 * boardSize - 1; j++){
            // if required, draw the links

            drawLinks(i, j);

        }
    }
}

void Meniusetup()
{

    Text startText, scoreText, exitText, settingText, soundText;
    Font myfont;
    if(!myfont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf"))
    {
        cout<<"Errors font, can't loaded"<<endl;
    }
    startText.setFont(myfont);
    startText.setString("Start");
    startText.setCharacterSize(textSize);
    startText.setColor(textColor);
    startText.setPosition(300,40);
    //////////////////////////
    startText.setFont(myfont);
    startText.setString("Score");
    startText.setCharacterSize(textSize);
    startText.setColor(textColor);
    startText.setPosition(280,160);
    ///////////////////////
    settingText.setFont(myfont);
    settingText.setString("Setting");
    settingText.setCharacterSize(textSize);
    settingText.setColor(textColor);
    settingText.setPosition(270,280);
    /////////////////////////
    exitText.setFont(myfont);
    exitText.setString("Exit");
    exitText.setCharacterSize(textSize);
    exitText.setColor(textColor);
    exitText.setPosition(310,400);
    /////////////////////////
    soundText.setFont(myfont);
    soundText.setString("Sound");
    soundText.setCharacterSize(textSize);
    soundText.setColor(textColor);
    soundText.setPosition(280,520);

    while(window.isOpen())
    {
        sf::Event event;

         while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
        window.clear();
        window.draw(startText);
        window.draw(scoreText);
        window.draw(settingText);
        window.draw(exitText);
        window.draw(soundText);
        window.display();

    }
}


void centerscreen(RenderWindow &window)
{
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5,
                                     sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

}
