#include "UI.hpp"

using namespace sf;

void resetBackGround(){
    Vector2<float> bgSize(window.getSize().x, window.getSize().y);
    backGround.setPosition(0.f, 0.f);
    backGround.setSize(bgSize);
    backGround.setFillColor(backGroundColor);
}

void drawLinks(int i, int j){
    char player;
    Color culoare;
    if(board[i][j] == '1')
    {
        player = 'x';
        culoare = player1Color;
    }
    else if(board[i][j] == '2')
    {
        player = 'y';
        culoare = player2Color;
    }
    else
        return;

    if(board[i][j-1] == player && board[i][j+1] == player)
    {

        // build link shape and draw it
        RectangleShape link(Vector2f(colDist, linkWidth));
        link.setPosition((j - 1) * (colDist / 2) + circleRadius, i * (rowDist / 2) + circleRadius - linkWidth / 2);
        link.setFillColor(culoare);
        window.draw(link);
    }

    // or a vertical one
    else if(board[i - 1][j] == player && board[i + 1][j] == player)
    {

        // build link shape and draw
        RectangleShape link(Vector2f(linkWidth, rowDist));
        link.setPosition(j * (colDist / 2) + circleRadius - linkWidth / 2, (i - 1) * (rowDist / 2) + circleRadius);
        link.setFillColor(culoare);
        window.draw(link);
    }

}

void loadBoard(){

    resetBackGround();
    window.draw(backGround);
    CircleShape shape(circleRadius);

    // load the first player's dots
    shape.setFillColor(player1Color);
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 1; j < boardSize; j++)
        {
            shape.setPosition(j * colDist - colDist / 2, i * rowDist);
            window.draw(shape);
        }
    }

    // load the second player's pieces
    shape.setFillColor(player2Color);
    for(int i = 1; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            shape.setPosition(j * colDist, i * rowDist - rowDist / 2);
            window.draw(shape);
        }
    }

    // load links for both players
    for(int i = 0; i < 2 * boardSize - 1; i++)
    {
        for(int j = 0; j < 2 * boardSize - 1; j++)
        {
            // if required, draw the links

            drawLinks(i, j);

        }
    }
}

void moveUp(int &selection,Text entries[]){
    if(selection-1>0)
    {
        entries[selection].setColor(player2Color);
        selection--;
        entries[selection].setColor(player1Color);
    }
}

void moveDown(int &selection,Text entries[],int dimensions){
    if(selection+1<dimensions)
    {
        entries[selection].setColor(player2Color);
        selection++;
        entries[selection].setColor(player1Color);
    }
}

void eventEnter(int &selection){
    if(selection==1)
        numberOfPlayerMenu();
    if(selection==2)
        settingsMenu();
    if(selection==4)
        window.close();


}

void Meniusetup(){
    window.create(sf::VideoMode(800,600), "Bridg-It");

    resetBackGround();
    Text entries[5];
    Font myFont;
    myFont.loadFromFile(fontPath);
    for(int i = 0; i < 5; i++)
    {
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(player2Color);
        entries[i].setFont(myFont);
    }
    entries[0].setString("WELCOME");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("Start Game");
    entries[2].setString("Settings");
    entries[3].setString("High Score");
    entries[4].setString("Exit");
    int dimension=5;
    int selection=1;
    entries[1].setColor(player1Color);
    for(int i = 0; i < 5; i++)
    {
        entries[i].setPosition(window.getSize().x / 2 - entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 5));
    }
    while(window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyReleased:

                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp(selection,entries);
                    break;

                case sf::Keyboard::Down:
                    moveDown(selection,entries,dimension);
                    break;

                case sf::Keyboard::Enter:
                    eventEnter(selection);
                    break ;
                }
                break;
            }
            if(event.type == Event::Closed)
                window.close();

        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 5; i++)
            window.draw(entries[i]);
        window.display();

    }
}

void setGameOptionsMenuEntities(Text entries[], Font &myFont, int selection){

    resetBackGround();
    // set stuff that is the same for all text entries
    for(int i = 0; i < 4; i++)
    {
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(player2Color);
        entries[i].setFont(myFont);
    }
    entries[selection].setColor(player1Color);


    // maximum size of the board, considering the screen resolution
    int maxBoardSize = floor((VideoMode::getDesktopMode().height - 2 * circleRadius) / rowDist);

    // set individual characteristics;
    entries[0].setString("Choose the board size");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("5 x 5 Board");
    entries[2].setString("8 x 8 Board");

    // prevent having two identical options
    if(maxBoardSize <= 8)
    {
        entries[1].setString("3 x 3 Board");
        entries[2].setString("5 x 5 Board");
    }
    entries[3].setString(to_string(maxBoardSize) + " x " + to_string(maxBoardSize) + " Board");


    // positioning of all
    for(int i = 0; i < 4; i++)
    {
        entries[i].setPosition(window.getSize().x / 2 - entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 4));
    }
}

void setSelection(int &selection, Event::MouseButtonEvent mouse, Text entries[], Font &myFont){
    int currentSelection = int(mouse.y / (window.getSize().y / 5));
    if(currentSelection >= 4)
    {
        if(selection == 1)
            boardSize = 5;
        else if (selection == 2)
            boardSize = 8;
        else
            boardSize = getSizeFromStr(entries[selection].getString());
        if(boardSize == -1)
            entries[3].setString("Invalid format! Try either n or n x n format");
        else
            startGame();
    }
    if(currentSelection == 3)
    {
        entries[3].setString("");
    }
    if(currentSelection != 0)
        selection = currentSelection;
}

void gameOptionsMenu(){

    window.create(VideoMode(800, 600), "Bridg-It");

    // the text that will server as buttons, and the font for it
    Text entries[4];
    Font myFont;
    myFont.loadFromFile(fontPath);

    // set how many options we use
    int dim = 4;


    // this will let us know which option is selected, and what to highlight
    int selection = 1;

    setGameOptionsMenuEntities(entries, myFont, selection);
    // draw the window and wait for events
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::Resized:
            {
                // don't allow it to be too small for the text to be seen
                if (window.getSize().y < 4 * (textSize + textPadding))
                    window.setSize(Vector2u(window.getSize().x, unsigned(4 * (textSize + textPadding))));

                // adjust the view to the new window size, so the image doesn't appear stretched
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // keep the elements of the window responsive
                setGameOptionsMenuEntities(entries, myFont, selection);
                break;
            }
            case Event::KeyReleased:
                switch(event.key.code)
                {
                case Keyboard::Up:
                    moveUp(selection, entries);
                    break;
                case Keyboard::Down:
                    moveDown(selection, entries, dim);
                    break;
                case Keyboard::Enter:
                    boardSize = stoi(string(entries[selection].getString()));
                    startGame();
                    break;
                case Keyboard::Escape:
                    numberOfPlayerMenu();
                    break;
                }
                break;
            }
        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 4; i++)
            window.draw(entries[i]);
        window.display();
    }
}

unsigned linkDots(sf::Event::MouseButtonEvent mouse){

    if(isClickValid(mouse))
    {
        // wait for the second click:
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        return linkIfValid(mouse, event.mouseButton);
                    }
                }
            }

            window.clear();
            loadBoard();
            window.display();
        }
    }

}

void startGame(){
    createBoard();
    window.create(sf::VideoMode((boardSize - 1) * colDist + 2 * circleRadius, (boardSize - 1) * rowDist + 2 * circleRadius), "Bridg-It", Style::Titlebar | Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                gameOptionsMenu();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == Mouse::Left)
                {
                    unsigned s = linkDots(event.mouseButton);
                    showWinner(s);
                    if(s != 0)
                        window.close();
                }
            }
        }

        window.clear();
        loadBoard();
        window.display();
    }


}

void dificultyMenu(){
    window.create(sf::VideoMode(800,600), "Bridg-It");

    resetBackGround();

    Text entries[4];
    Font myFont;
    myFont.loadFromFile(fontPath);
    for(int i = 0; i < 4; i++)
    {
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(player2Color);
        entries[i].setFont(myFont);
    }

    // set individual characteristics;
    entries[0].setString("Chose Difficulty");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("Easy");
    entries[2].setString("Normal");
    entries[3].setString("Hard");
    for(int i = 0; i <4; i++)
    {
        entries[i].setPosition(window.getSize().x / 2 -
                               entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 5));
    }
    int selection=1;
    int dimension=4;
    entries[1].setColor(player1Color);

    while(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyReleased:

                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp(selection,entries);
                    break;

                case sf::Keyboard::Down:
                    moveDown(selection,entries,dimension);
                    break;


                case sf::Keyboard::Escape:
                    numberOfPlayerMenu();
                    break;
                }
                break;
            }
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 4; i++)
            window.draw(entries[i]);
        window.display();

    }

}

void eventEnter1(int &selection,Text entries[]){
    if(selection==1)
        gameOptionsMenu();
    if(selection==2)
        dificultyMenu();

}

void numberOfPlayerMenu(){
    window.create(sf::VideoMode(800,600), "Bridg-It");

    resetBackGround();

    Text entries[3];
    Font myFont;
    myFont.loadFromFile(fontPath);
    for(int i = 0; i < 3; i++)
    {
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(player2Color);
        entries[i].setFont(myFont);
    }

    // set individual characteristics;
    entries[1].setString("Player Vs Player");
    entries[1].setStyle(Text::Bold | Text::Underlined);
    entries[2].setString("Player Vs Pc");
    entries[2].setStyle(Text::Bold | Text::Underlined);


    for(int i = 0; i <3; i++)
    {
        entries[i].setPosition(window.getSize().x/2 -
                               entries[i].getGlobalBounds().width /2,i* (window.getSize().y/3));

    }
    int selection=1;
    int dimension=3;
    entries[1].setColor(player1Color);

    while(window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyReleased:

                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp(selection,entries);
                    break;

                case sf::Keyboard::Down:
                    moveDown(selection,entries,dimension);
                    break;

                case sf::Keyboard::Enter:
                    eventEnter1(selection,entries);
                    break ;
                case sf::Keyboard::Escape:
                    Meniusetup();
                    break;
                }
                break;
            }
            if(event.type == Event::Closed)
                window.close();

        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 3; i++)
            window.draw(entries[i]);
        window.display();
    }



}

void showWinner(unsigned u){
    if(u == 0)
        return;
    Text winnerText;
    if(u == 1){
        winnerText.setColor(player1Color);
        winnerText.setString("Player 1 won!");
    }
    else{
        winnerText.setColor(player2Color);
        winnerText.setString("Player 2 won!");
    }
    Font textFont;
    textFont.loadFromFile(fontPath);
    winnerText.setFont(textFont);
    winnerText.setCharacterSize(window.getSize().y / winnerText.getString().getSize() * 2);
    RectangleShape focusRect;
    Color newCol(44, 47, 51, 200);
    focusRect.setFillColor(newCol);
    winnerText.setPosition((window.getSize().x - winnerText.getGlobalBounds().width) / 2, (window.getSize().y - winnerText.getGlobalBounds().height) / 2);
    Vector2f windowSize;
    windowSize.x = float(window.getSize().x);
    windowSize.y = float(window.getSize().y);
    focusRect.setSize(windowSize);
    Clock clock;
    while(clock.getElapsedTime().asSeconds() < 5.0f){
        window.clear();
        loadBoard();
        window.draw(focusRect);
        window.draw(winnerText);
        window.display();
    }
}

void setSettingsMenuEntries(Text entries[], Font &font, int &selection, Texture &myTick, RectangleShape &checkBox){

    resetBackGround();

    // get font
    font.loadFromFile(fontPath);

    // set the common properties for the text values
    for(int i = 0; i < 5; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(player2Color);
        entries[i].setFont(font);
    }

    // highlight the selection
    entries[selection].setColor(player1Color);

    // set individual properties
    entries[0].setString("Settings");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("Music");
    entries[2].setString("Player colors");
    entries[3].setString("Font");
    entries[4].setString("Back");

    // depending on whether we'll have sound or not, we tick the box or untick it
    if(isMuted)
        myTick.loadFromImage(unticked);
    else
        myTick.loadFromImage(ticked);

    // little settings for the sprite to look good, and some positioning
    myTick.setSmooth(true);
    Vector2<float> checkBoxSize(entries[1].getGlobalBounds().height, entries[1].getGlobalBounds().height);
    checkBox.setSize(checkBoxSize);
    checkBox.setTexture(&myTick);
    checkBox.setPosition(entries[1].getPosition().x - 2 * checkBox.getSize().x, entries[1].getPosition().y + checkBox.getSize().y / 2);
    checkBox.setFillColor(player2Color);

    // positioning of all
    for(int i = 0; i < 5; i++)
    {
        entries[i].setPosition(window.getSize().x / 2 - entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 5));
    }
}

void settingsMenu(){

    window.create(sf::VideoMode(800,600), "Bridg-It");

    int selection = 1, dim = 5;
    Text entries[dim];
    Font myFont;
    Texture myTick;
    RectangleShape checkBox;

    ticked.loadFromFile("Assets" pathSeparator "Images" pathSeparator "ticked.png");
    unticked.loadFromFile("Assets" pathSeparator "Images" pathSeparator "unticked.png");

    setSettingsMenuEntries(entries, myFont, selection, myTick, checkBox);
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::Resized:
            {

                // adjust the view to the new window size, so the image doesn't appear stretched
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // keep the elements of the window responsive
                setSettingsMenuEntries(entries, myFont, selection, myTick, checkBox);
                break;
            }
            case Event::KeyReleased:
                switch(event.key.code)
                {
                case Keyboard::Up:
                    moveUp(selection, entries);
                    break;
                case Keyboard::Down:
                    moveDown(selection, entries, dim);
                    break;
                case Keyboard::Escape:
                    Meniusetup();
                    break;
                case Keyboard::Enter:
                    switch(selection){
                    case 1:
                        isMuted = !isMuted;
                        setSettingsMenuEntries(entries, myFont, selection, myTick, checkBox);
                        break;
                    case 2:
                        selectPlayerColorsMenu();
                        break;
                    case 3:
                        selectFontMenu();
                        break;
                    default:
                        Meniusetup();
                    }
                }
                break;
            }
        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 5; i++)
            window.draw(entries[i]);
        window.draw(checkBox);
        window.display();
    }
}

void setSelectPlayerColorsMenu(Text entries[], RectangleShape colorOptions[][3], Font &font){

    resetBackGround();

    // setting the text
    entries[0].setString("Choose player colors");
    entries[1].setString("Player 1");
    entries[2].setString("Player 2");
    entries[3].setString("Back");

    // choose font and assign it
    font.loadFromFile(fontPath);

    // set font and character size for all text
    for(int i = 0; i < 4; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setFont(font);
    }
    entries[0].setStyle(Text::Bold | Text::Underlined);

    // set the position and color for the text
    // place it right at the top, in the middle of the window
    entries[0].setPosition((window.getSize().x - entries[0].getGlobalBounds().width) / 2, 0.f);
    entries[0].setFillColor(player2Color);

    // right under where the colors will be, centered in the first half of the window
    entries[1].setPosition((window.getSize().x / 2 - entries[1].getGlobalBounds().width) / 2, window.getSize().y / 2 + 2 * entries[0].getGlobalBounds().height);
    entries[1].setFillColor(player1Color);
    // aligned somewhat like the one before, just centered in the second half of the window
    entries[2].setPosition(( 3 * window.getSize().x / 2 - entries[1].getGlobalBounds().width) / 2, window.getSize().y / 2 + 2 * entries[0].getGlobalBounds().height);
    entries[2].setFillColor(player2Color);

    // place it in the middle of the remaining space
    float spaceAfterEntities = 2 * entries[0].getGlobalBounds().height + window.getSize().y / 2 + entries[1].getGlobalBounds().height;
    entries[3].setPosition((window.getSize().x - entries[3].getGlobalBounds().width) / 2, spaceAfterEntities + (window.getSize().y - spaceAfterEntities- entries[3].getGlobalBounds().height) / 2);
    entries[3].setFillColor(player1Color);
    // set the colors for picking:
    colorOptions[0][0].setFillColor(Color::Black);
    colorOptions[0][1].setFillColor(Color::White);
    colorOptions[0][2].setFillColor(Color::Yellow);
    colorOptions[1][0].setFillColor(Color::Green);
    colorOptions[1][1].setFillColor(Color::Blue);
    colorOptions[1][2].setFillColor(Color::Cyan);
    colorOptions[2][0].setFillColor(Color::Magenta);
    colorOptions[2][1].setFillColor(Color::Red);
    colorOptions[2][2].setFillColor(Color(255, 165, 0));

    // set each rectangle's size
    Vector2<float> newSize(window.getSize().x / 6, window.getSize().y / 6);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            colorOptions[i][j].setSize(newSize);
        }
    }
}

void drawColors(RectangleShape colorOptions[][3], bool player, Text title){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            colorOptions[i][j].setPosition(player * window.getSize().x / 2 + j * window.getSize().x / 6, 2 * title.getGlobalBounds().height + i * window.getSize().y / 6);
            window.draw(colorOptions[i][j]);
        }
    }
}

void selectPlayerColorsMenu(){
    window.create(VideoMode(600, 800), "Bridg-It");
    Font font;
    Text entries[4];
    RectangleShape colorOptions[3][3];
    setSelectPlayerColorsMenu(entries, colorOptions, font);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            switch(event.type){
            case Event::Closed:
                window.close();
                settingsMenu();
                break;
            case Event::KeyReleased:
                switch(event.key.code){
                case Keyboard::Enter:
                    window.close();
                    settingsMenu();
                    break;
                case Keyboard::Escape:
                    window.close();
                    settingsMenu();
                }
                break;
            case Event::Resized:
            {

                // adjust the view to the new window size, so the image doesn't appear stretched
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // keep the elements of the window responsive
                setSelectPlayerColorsMenu(entries, colorOptions, font);
                break;
            }
            case Event::MouseButtonPressed:
                pickColor(event.mouseButton, colorOptions, entries);
                setSelectPlayerColorsMenu(entries, colorOptions, font);
            }
        }
        window.clear();
        window.draw(backGround);
        for(int i = 0; i < 4; i++)
            window.draw(entries[i]);
        drawColors(colorOptions, 0, entries[0]);
        drawColors(colorOptions, 1, entries[0]);
        window.display();
    }
}

void pickColor(Event::MouseButtonEvent mousebutton, RectangleShape colorOptions[][3], Text entries[]){
    if(mousebutton.button == Mouse::Left){

        // check if we're selecting a color
        if(mousebutton.y > 2 * entries[0].getGlobalBounds().height && mousebutton.y < 2 * entries[0].getGlobalBounds().height + window.getSize().y / 2){

            // see if it's for the first player
            if(mousebutton.x < window.getSize().x / 2 && player2Color != colorOptions[int((mousebutton.y - 2 * entries[0].getGlobalBounds().height) / colorOptions[0][0].getSize().y)][int(mousebutton.x / colorOptions[0][0].getSize().x)].getFillColor()){
                player1Color = colorOptions[int((mousebutton.y - 2 * entries[0].getGlobalBounds().height) / colorOptions[0][0].getSize().y)][int(mousebutton.x / colorOptions[0][0].getSize().x)].getFillColor();
            }
            else if(mousebutton.x > window.getSize().x / 2 && player1Color != colorOptions[int((mousebutton.y - 2 * entries[0].getGlobalBounds().height) / colorOptions[0][0].getSize().y)][int((mousebutton.x - window.getSize().x / 2) / colorOptions[0][0].getSize().x)].getFillColor()){
                player2Color = colorOptions[int((mousebutton.y - 2 * entries[0].getGlobalBounds().height) / colorOptions[0][0].getSize().y)][int((mousebutton.x - window.getSize().x / 2) / colorOptions[0][0].getSize().x)].getFillColor();
            }
        }
        if(mousebutton.y > entries[3].getPosition().y)
            settingsMenu();
    }
}

void setSelectFontMenuEntries(string fonts[], Text entries[], int numOfFonts, int selection, Font &font, View &titleView, View &fontsView){


    resetBackGround();

    // set the title's properties
    entries[0].setString("Choose font");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[0].setCharacterSize(textSize);
    entries[0].setFont(font);
    entries[0].setPosition((window.getSize().x - entries[0].getGlobalBounds().width) / 2, window.getSize().y / 2 - entries[0].getGlobalBounds().height);
    entries[0].setFillColor(player2Color);

    // set the fonts
    for(int i = 1; i <= numOfFonts; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setString(fonts[i - 1]);
        entries[i].setFont(font);
        entries[i].setPosition((window.getSize().x - entries[i].getGlobalBounds().width) / 2, i * entries[0].getGlobalBounds().height * 2);
        entries[i].setFillColor(player2Color);
    }
    entries[selection].setFillColor(player1Color);

    // finally let's set the views
    titleView.setViewport(FloatRect(0.f, 0.f, 1.f, 2 * entries[0].getGlobalBounds().height / window.getSize().y));
    titleView.setSize(window.getSize().x, 2 * entries[0].getGlobalBounds().height);
    titleView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    fontsView.setViewport(FloatRect(0.f, 2 * entries[0].getGlobalBounds().height / window.getSize().y, 1.0f, (window.getSize().y - 2 * entries[0].getGlobalBounds().height / window.getSize().y) / window.getSize().y));
    fontsView.setSize(window.getSize().x, window.getSize().y - 2 * entries[0].getGlobalBounds().height);
    fontsView.setCenter(window.getSize().x / 2, window.getSize().y / 2 + entries[0].getGlobalBounds().height);
    // well that took a lot to figure out :(((

}

void selectFontMenu(){

    window.create(VideoMode(800, 600), "Select Font");

    // since we'll do a scroll and I want the title to stand out, we'll need separate views
    View titleView, fontsView;

    // load font names
    int numOfFonts = getNumberOfFonts(), selection = 1;
    string fonts[numOfFonts];
    setFonts(fonts, numOfFonts);
    Font font;
    font.loadFromFile(fontPath);

    // make text entries
    Text entries[numOfFonts + 1];
    setSelectFontMenuEntries(fonts, entries, numOfFonts, selection, font, titleView, fontsView);

    while(window.isOpen()){
        Event event;

        while(window.pollEvent(event)){
            switch(event.type){
            case Event::Closed:
                settingsMenu();
                break;
            case Event::Resized:
                setSelectFontMenuEntries(fonts, entries, numOfFonts, selection, font, titleView, fontsView);
                break;
            case Event::KeyReleased:
                switch(event.key.code){
                case Keyboard::Up:
                    moveUp(selection, entries);
                    if(fontsView.getCenter().y > window.getSize().y / 2 + 2 * entries[0].getGlobalBounds().height)
                        fontsView.move(0.f, -2 * entries[0].getGlobalBounds().height);
                    else
                        fontsView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
                    break;
                case Keyboard::Down:
                    moveDown(selection, entries, numOfFonts + 1);
                    if(fontsView.getCenter().y < (numOfFonts - 1) * entries[0].getGlobalBounds().height * 2){
                        fontsView.move(0.f, 2 * entries[0].getGlobalBounds().height);
                    }
                    else{
                        fontsView.setCenter(window.getSize().x / 2, 2 * entries[0].getGlobalBounds().height * numOfFonts);
                    }
                    break;
                case Keyboard::Enter:
                    fontPath = "Assets" pathSeparator "Fonts" pathSeparator;
                    fontPath = fontPath + entries[selection].getString();
                    settingsMenu();
                }
            }
        }
        window.clear();
        window.setView(fontsView);
        window.draw(backGround);
        for(int i = 1; i <= numOfFonts; i++){
            window.draw(entries[i]);
        }
        window.setView(titleView);
        window.draw(backGround);
        window.draw(entries[0]);
        window.display();
        //fontsView.move(0.f, 0.05f);
    }
}
