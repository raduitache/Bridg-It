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

void moveUp(int &selection,Text entries[]){
    if(selection-1>0)
    {
        entries[selection].setColor(sf::Color::Red);
        selection--;
        entries[selection].setColor(sf::Color::White);
    }
}

void moveDown(int &selection,Text entries[],int dimensions){
    if(selection+1<dimensions)
    {
        entries[selection].setColor(sf::Color::Red);
        selection++;
        entries[selection].setColor(sf::Color::White);
    }
}

void eventEnter(int &selection){
    if(selection==1)
    numberOfPlayerMenu();
    if(selection==2)
        numberOfPlayerMenu();
    if(selection==4)
     window.close();


}

void Meniusetup(){
    window.create(sf::VideoMode(800,600), "Bridg-It");

    Text entries[5];
    Font myFont;
    myFont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf");
    for(int i = 0; i < 5; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(textColor);
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
    entries[1].setColor(sf::Color::White);
    for(int i = 0; i < 5; i++){
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
             for(int i = 0; i < 5; i++) window.draw(entries[i]);
        window.display();

    }
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
    entries[1].setString("5 x 5 Board");
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
        else if (selection == 2) boardSize = 8;
        else boardSize = getSizeFromStr(entries[selection].getString());
        if(boardSize == -1) entries[3].setString("Invalid format! Try either n or n x n format");
        else startGame();
    }
    if(currentSelection == 3){
        entries[3].setString("");
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
            if(event.type == Event::TextEntered && selection == 3){
                if(event.text.unicode == 8){
                    sf::String myStr = entries[3].getString();
                    myStr.erase(myStr.getSize() - 1);
                    entries[3].setString(myStr);
                }
                else
                    entries[3].setString(entries[3].getString() + event.text.unicode);
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
void startGame(){
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

void dificultyMenu(){
    window.create(sf::VideoMode(800,600), "Bridg-It");

     Text entries[4];
     Font myFont;
    myFont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf");
    for(int i = 0; i < 4; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(textColor);
        entries[i].setFont(myFont);
    }

    // set individual characteristics;
    entries[0].setString("Chose Difficulty");
    entries[0].setStyle(Text::Bold | Text::Underlined);
    entries[1].setString("Easy");
    entries[2].setString("Normal");
    entries[3].setString("Hard");
     for(int i = 0; i <4; i++){
        entries[i].setPosition(window.getSize().x / 2 -
        entries[i].getGlobalBounds().width / 2, i * (window.getSize().y / 5));
    }
    int selection=1;
    int dimension=4;
    entries[1].setColor(sf::Color::White);

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
       for(int i = 0; i < 4; i++) window.draw(entries[i]);
        window.display();

    }

}

void eventEnter1(int &selection,Text entries[])
{
    if(selection==1)
    gameOptionsMenu();
    if(selection==2)
    dificultyMenu();

}

void numberOfPlayerMenu(){
    window.create(sf::VideoMode(800,600), "Bridg-It");
    Text entries[3];
    Font myFont;
    myFont.loadFromFile("Assets" pathSeparator "Fonts" pathSeparator "Roboto-Italic.ttf");
    for(int i = 0; i < 3; i++){
        entries[i].setCharacterSize(textSize);
        entries[i].setColor(textColor);
        entries[i].setFont(myFont);
    }

     // set individual characteristics;
    entries[1].setString("Player Vs Player");
    entries[1].setStyle(Text::Bold | Text::Underlined);
    entries[2].setString("Player Vs Pc");
    entries[2].setStyle(Text::Bold | Text::Underlined);


     for(int i = 0; i <3; i++){
        entries[i].setPosition(window.getSize().x/2 -
        entries[i].getGlobalBounds().width /2,i* (window.getSize().y/3));

    }
    int selection=1;
    int dimension=3;
    entries[1].setColor(sf::Color::White);

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
       for(int i = 0; i < 3; i++) window.draw(entries[i]);
        window.display();
    }



    }



