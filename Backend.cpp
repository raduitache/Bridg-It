#include "Backend.hpp"
using namespace std;


void addDotsToBoard(){
    for(int i = 0; i < 2 * boardSize - 1; i++)
    {
        for(int j = 0; j < 2 * boardSize - 1; j++)
        {
            if((i + j) % 2 == 0)
            {
                board[i][j] = '0';
            }
            else if(i % 2 == 0 && j % 2 == 1)
            {
                board[i][j] = 'x';
            }
            else
            {
                board[i][j] = 'y';
            }
        }
    }
    board[0][0] = '-';
    board[0][2 * boardSize - 2] = '-';
    board[2 * boardSize - 2][0] = '-';
    board[2 * boardSize - 2][2 * boardSize - 2] = '-';
}

void printBoard(){
    for(int i = 0; i < 2 * boardSize - 1; i++)
    {
        for(int j = 0; j < 2 * boardSize - 1; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isClickValid(sf::Event::MouseButtonEvent mouse){
    int x = int(mouse.x / (rowDist / 2));
    int y = int(mouse.y / (colDist / 2));
    //cout << x << " " << y << endl;
    if(board[y][x] == 'x' && playerRound == 0)
        return 1;
    if(board[y][x] == 'y' && playerRound == 1)
        return 1;
    return 0;
}

unsigned linkIfValid(sf::Event::MouseButtonEvent click1, sf::Event::MouseButtonEvent click2){
    int x1 = int(click1.x / (rowDist / 2));
    int y1 = int(click1.y / (colDist / 2));
    int x2 = int(click2.x / (rowDist / 2));
    int y2 = int(click2.y / (colDist / 2));
    if(x1 == x2)
    {
        if(abs(y1 - y2) == 2)
        {
            if(board[(y1 + y2) / 2][x1] == '0')
            {
                board[(y1 + y2) / 2][x1] = '0' + playerRound + 1;
                playerRound = !playerRound;
                return gameOver(!playerRound);
            }
        }
    }
    if(y1 == y2)
    {
        if(abs(x1 - x2) == 2)
        {
            if(board[y1][(x1 + x2) / 2] == '0')
            {
                board[y1][(x1 + x2) / 2] = '0' + playerRound + 1;
                playerRound = !playerRound;
                return gameOver(!playerRound);
            }
        }
    }
    return 0;
}

void createBoard(){
    board = new char*[2 * boardSize - 1];
    for(int i = 0; i < 2 * boardSize - 1; i++)
    {
        board[i] = new char[2 * boardSize - 1];
    }
    addDotsToBoard();
    //printBoard();
}


int getSizeFromStr(string s){
    std::string::size_type sz;
    if(s.size() == 0)
        return -1;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    size_t found = s.find("x");
    if(found != string::npos)
    {
        if(s.substr(0, found) != s.substr(found + 1))
        {
            return -1;
        }
    }
    stringstream geek(s);
    int x = 0;
    geek >> x;
    try
    {
        //   return stoi(s);


    }
    catch(int e)
    {
        return -1;
    }
}

unsigned gameOver(bool player){
    queue q;
    if(player)
    {
        for(int i = 1; i < 2 * boardSize - 1; i += 2)
        {
            push(q, 0);
            push(q, i);
            if(BFS(q, player) != 0)
                return player + 1;
        }
        return 0;
    }
    for(int i = 1; i < 2 * boardSize - 1; i += 2)
    {
        push(q, i);
        push(q, 0);
        if(BFS(q, player) != 0)
            return player + 1;
    }
    return 0;
}

bool BFS(queue &q, bool player){
    bool visited[2 * boardSize - 1][2 * boardSize - 1];

    // setter because we need them
    for(int i = 0; i < 2 * boardSize - 1; i++)
    {
        for(int j = 0; j < 2 * boardSize - 1; j++)
        {
            visited[i][j] = false;
        }
    }

    while(q.size != 0)
    {

        // get the values from queue
        int row, col;
        col = q.front->val;
        pop(q);
        row = q.front->val;
        pop(q);
        // visit the node
        visited[row][col] = true;

        // based on which player we are
        if(player)
        {

            // check whether we have reached our goal
            if(col == 2 * boardSize - 2)
                return 1;
        }

        // and for the second player as well
        else
        {
            if(row == 2 * boardSize - 2)
                return 1;
        }

        // add next points in queue, if the case

        // check upper border
        if(row > 0)
        {

            // check if there is a link and if it is the player's
            if(board[row - 1][col] - '0' == player + 1 && !visited[row - 2][col])
            {

                // push the next point to the queue
                push(q, col);
                push(q, row - 2);
            }
        }

        // check lower border
        if(row < 2 * boardSize - 2)
        {

            // check if there is a link and if it is the player's
            if(board[row + 1][col] - '0' == player + 1 && !visited[row + 2][col])
            {

                // push the next point to the queue
                push(q, col);
                push(q, row + 2);

            }
        }

        // check right-most border
        if(col < 2 * boardSize - 2)
        {

            // check if there is a link and if it is the player's
            if(board[row][col + 1] - '0' == player + 1 && !visited[row][col + 2])
            {

                // push the next point to the queue
                push(q, col + 2);
                push(q, row);
            }
        }

        // check the left-most border
        if(col > 0)
        {

            // check if there is a link and if it is the player's
            if(board[row][col - 1] - '0' == player + 1 && !visited[row][col - 2])
            {

                // push the next point to the queue
                push(q, col - 2);
                push(q, row);
            }
        }

    }
    return 0;
}

unsigned playerMove(sf::Event::MouseButtonEvent click1, sf::Event::MouseButtonEvent click2)
{
     int x1 = int(click1.x / (rowDist / 2));
    int y1 = int(click1.y / (colDist / 2));
    int x2 = int(click2.x / (rowDist / 2));
    int y2 = int(click2.y / (colDist / 2));

}

void setPrerequisites(){
    fstream f;
    f.open("conf.ini", fstream::in);

    // first thing should be the boolean value for this
    f >> isMuted;

    // we'll need some values for the rgb code
    int r, g, b;

    // we'll have the colors stored as rgb codes, as it's easier to parse. The codes for the first player
    f >> r >> g >> b;
    player1Color = sf::Color(r, g, b);

    // and the same for the second
    f >> r >> g >> b;
    player2Color = sf::Color(r, g, b);

    // and finally a string for the font
    fontPath = "Assets" pathSeparator "Fonts" pathSeparator;
    string s;
    f >> s;
    fontPath += s;

    // and we'll be closing the stream now
    f.close();

    ticked.loadFromFile("Assets" pathSeparator "Images" pathSeparator "ticked.png");
    unticked.loadFromFile("Assets" pathSeparator "Images" pathSeparator "unticked.png");
    music.openFromFile("Assets" pathSeparator "Sounds" pathSeparator "backGroundMusic.ogg");
    clickSoundBuffer.loadFromFile("Assets" pathSeparator "Sounds" pathSeparator "pop.flac");
    winSoundBuffer.loadFromFile("Assets" pathSeparator "Sounds" pathSeparator "win.wav");
    music.setLoop(true);
    firstClickSound.setBuffer(clickSoundBuffer);
    secondClickSound.setBuffer(clickSoundBuffer);
    winSound.setBuffer(winSoundBuffer);
    secondClickSound.setPitch(1.2f);
    backGroundColor = sf::Color(44, 47, 51);
    if(isMuted == 0)
        music.play();
}

int getNumberOfFonts(){
    struct dirent **files;
    string ext = "tff";
    int n, res;

    n = scandir("Assets" pathSeparator "Fonts",  &files, NULL, alphasort);
    res = 0;
    for(int i = 0; i < n; i++){
        struct dirent *ent;

        ent = files[i];
        string name = ent->d_name;
        if(ent->d_type == DT_REG)
            res++;
    }

    return res;
}

void setFonts(string entries[], int n){
    struct dirent **files;
    int counter = 0, filesNumber;
    filesNumber = scandir("Assets" pathSeparator "Fonts", &files, NULL, alphasort);
    for(int i = 0; i < filesNumber; i++){
        struct dirent *ent = files[i];
        if(ent->d_type == DT_REG){
            entries[counter] = ent->d_name;
            counter++;
        }
    }
}

void saveSettings(){
    fstream f;
    f.open("conf.ini", fstream::out);
    f << isMuted << endl;
    unsigned p1 = player1Color.toInteger();
    unsigned p2 = player2Color.toInteger();
    f << (p1 >> 24) << " " << ((p1 << 8) >> 24) << " " << ((p1 << 16) >> 24) << endl;
    f << (p2 >> 24) << " " << ((p2 << 8) >> 24) << " " << ((p2 << 16) >> 24) << endl;
    f << fontPath.substr(fontPath.rfind(pathSeparator) + 1) << endl;
}
