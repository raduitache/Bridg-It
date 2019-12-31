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

void setGameOptionsMenuEntities(Text entries[], RectangleShape &highlighter, RectangleShape &textBox, Font &myFont){
    // set stuff that is the same for all text entries
    for(int i = 0; i < 5; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(textColor);
        entries[i].setFont(myFont);
    }

    // set individual characteristics;
    entries[0].setString("Choose the board size");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("3 x 3 Board");
    entries[2].setString("8 x 8 Board");
    entries[3].setString("Insert custom board size");
    entries[4].setString("Play!");
    highlighter.setFillColor(highlightColor);
    highlighter.setSize(Vector2f(window.getSize().x, window.getSize().y / 5));
    textBox.setSize(Vector2f(window.getSize().x * 3 / 4, 3 * entries[3].getGlobalBounds().height / 2));

    // positioning of all
    for(int i = 0; i < 5; i++){
        entries[i].setPosition(window.getSize().x / 2 - entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 5));
    }
    highlighter.setPosition(0, window.getSize().y / 5);
    textBox.setPosition(window.getSize().x / 8, entries[3].getPosition().y);
}

void setSelection(int &selection, Event::MouseButtonEvent mouse, Text entries[], Font &myFont){
    int currentSelection = int(mouse.y / (window.getSize().y / 5));
    if(currentSelection >= 4){
        if(selection == 1) boardSize = 5;
        if(selection == 2) boardSize = 8;
        else boardSize = getSizeFromStr(entries[3].getString());
    }
    if(currentSelection != 0) selection = currentSelection;
}


void gameOptionsMenu(){

    window.create(VideoMode(800, 600), "Bridg-It");

    // the text that will server as buttons, and the font for it
    Text entries[5];
    Font myFont;
    myFont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf");

    // two rectangles, one will represent the highlighting, and the second will simulate a textbox
    RectangleShape highlighter, textBox;

    // this will let us know which option is selected, and what to highlight
    int selection = 1;

    setGameOptionsMenuEntities(entries, highlighter, textBox, myFont);
    // draw the window and wait for events
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            if(event.type == Event::Resized){

                // don't allow it to be too small for the text to be seen
                if (window.getSize().y < 5 * (textSize + textPadding)) window.setSize(Vector2u(window.getSize().x, unsigned(5 * (textSize + textPadding))));

                // adjust the view to the new window size, so the image doesn't appear stretched
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // keep the elements of the window responsive
                setGameOptionsMenuEntities(entries, highlighter, textBox, myFont);
            }
            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    setSelection(selection, event.mouseButton, entries, myFont);
                    highlighter.setPosition(0, window.getSize().y / 5 * selection);
                }
            }
        }
        window.clear();
        window.draw(highlighter);
        window.draw(textBox);
        for(int i = 0; i < 5; i++) window.draw(entries[i]);
        window.display();
    }
}



void linkDots(sf::Event::MouseButtonEvent mouse){
    if(isClickValid(mouse)){
            // wait for the second click:
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        linkIfValid(mouse, event.mouseButton);
                        return;
                    }
                }
            }

            window.clear();
            loadBoard();
            window.display();
        }
    }

}
void startGame()
{
    createBoard();
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
