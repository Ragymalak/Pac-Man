#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<fstream>
using namespace std;
using namespace sf;
struct Ghosts
{
    bool OccupiedSquares[4] = { true,true,true,true };

}G1, G2, G3, G4;


void CheckSquares();
bool eatingcherrytest();
bool eatingpointstest();
bool gameover();

Ghosts GhostStorage[] = { G1,G2,G3,G4 };
Sprite Ghost[4];
Sprite pacman;
Sprite point;

string rec[22] = {
        " ################### ",
        " #C.......#.......C# ",
        " #.##.###.#.###.##.# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.###.#.###.#### ",
        "    #.#...a...#.#    ",
        "    #.#.##=##.#.#    ",
        "    #...#bcd#..C#    ",
        "    #.#.#####.#.#    ",
        "    #.#.......#.#    ",
        " ####.#.#####.#.#### ",
        " #..C.....#........# ",
        " #.##.###.#.###.##.# ",
        " #..#.....P.....#..# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### ",
        "                     "
};

Text text;             // for score 
int OppositeMovement[4] = {};               
int counter = 0;                                // for menus
int x = 3;                                      //for lifes
int score = 0;                                

//Checks for squares arround the ghosts and we use it in ghost movement
void CheckSquares()
{
    for (int l = 0; l < 4; l++)
    {

        for (int k = 0; k < 4; k++)
        {
            if (k == 0)
            {
                int j = (Ghost[l].getPosition().x + 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }

            }
            if (k == 1)
            {
                int j = (Ghost[l].getPosition().x - 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 2)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y - 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 3)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y + 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }


        }
    }
}
void savetofile(int score) {
    ofstream output;
    output.open("savefile", ios::app);
    output << score << endl;
    output.close();
}

         // simple functions 

//function to make points dissapear and play eating sound
bool eatingpointstest()
{
    int j = pacman.getPosition().x / 32, i = (pacman.getPosition().y) / 32;
    bool x = false;
    if (rec[i][j] == '.')
    {
        rec[i][j] = ' ';
        x = true;
        score++;
        return x;                                      // it return true to play sound
    }
}

//function to make cherry dissapear and increment score by 100
bool eatingcherrytest() {
    int j = pacman.getPosition().x / 32, i = (pacman.getPosition().y) / 32;
    bool x = false;
    if (rec[i][j] == 'C')
    {
        rec[i][j] = ' ';
        score += 100;
        text.setString("Score: " + to_string(score));
        x = true;                                    // return true to play sound
        return x;
    }

}

//function for pacman collision with ghost and lifes
bool gameover()
{
    bool PacmanDead = false;

    for (int Ggg = 0; Ggg < 4; Ggg++) {
        if (pacman.getPosition().x == Ghost[Ggg].getPosition().x && pacman.getPosition().y == Ghost[Ggg].getPosition().y)
        {
            PacmanDead = true;
            x = x - 1;                                     // reduce lifes 
            sleep(seconds(3));
            pacman.setPosition(320, 480);
            Ghost[0].setPosition(2 * 10 * 16, 2 * 7 * 16);
            Ghost[1].setPosition(2 * 9 * 16, 2 * 7 * 16);
            Ghost[2].setPosition(2 * 10 * 16, 2 * 7 * 16);
            Ghost[3].setPosition(2 * 11 * 16, 2 * 7 * 16);
            
        }
    }

    return PacmanDead;
}
void main()
{

    //window
    RenderWindow window(VideoMode(672, 704), "PAC MAN");
    window.setFramerateLimit(10);

    // Sound
    SoundBuffer beginning;
    beginning.loadFromFile("pacman_beginning.wav");
    Sound Beginning;
    Beginning.setBuffer(beginning);

    SoundBuffer eatingSound;
    eatingSound.loadFromFile("pacman_chomp.wav");
    Sound EatingSound;
    EatingSound.setBuffer(eatingSound);

    SoundBuffer winsound;
    winsound.loadFromFile("win.wav");
    Sound winningsound;
    winningsound.setBuffer(winsound);

    SoundBuffer eatingcherry;
    eatingcherry.loadFromFile("pacman_eatfruit.wav");
    Sound Eatingcherry;
    Eatingcherry.setBuffer(eatingcherry);

    SoundBuffer death;
    death.loadFromFile("pacman_death.wav");
    Sound Death;
    Death.setBuffer(death);


    bool rightButton = false, leftButton = false, upButton = false, downButton = false;
 
    

    //textures
    Texture pac;
    Texture ghost;
    Texture menu;
    Texture Point;
    Texture cherry;
    Texture win;
   
    // sound loading

    win.loadFromFile("winningscreen.png");
    menu.loadFromFile("main menu.jpeg");
    pac.loadFromFile("pacman sprite.jpeg");
    ghost.loadFromFile("ghost sprite.jpeg");
    Point.loadFromFile("point.jpeg");
    cherry.loadFromFile("pacman cherry.jpg");
    Text lifes;
    Font font2;
    font2.loadFromFile("Cabaret Display Italic.ttf");
    lifes.setFont(font2);
    lifes.setCharacterSize(24);

    //FONT for score

    Font font;
    font.loadFromFile("Cabaret Display Italic.ttf");
    text.setFont(font);
    text.setCharacterSize(24);



    Texture highscore;
    highscore.loadFromFile("high score.png");
    Sprite Highscore;
    Highscore.setTexture(highscore);
    Highscore.setScale(1, 1);
    Text highscores;
    highscores.setPosition(300,450);
    highscores.setFillColor(Color::Yellow);

    Font font3;
    font3.loadFromFile("Cabaret Display Italic.ttf");
    highscores.setFont(font);
    highscores.setCharacterSize(36);
    //rectangles size
    RectangleShape Rect;
    Rect.setSize(Vector2f(32, 32));

    // Sprites

    for (int i = 0; i < 4; i++) {
        Ghost[i].setTexture(ghost);
    }

    //intial position
    Ghost[0].setPosition(2 * 10 * 16, 2 * 7 * 16);
    Ghost[1].setPosition(2 * 9 * 16, 2 * 9 * 16);
    Ghost[2].setPosition(2 * 10 * 16, 2 * 9 * 16);
    Ghost[3].setPosition(2 * 11 * 16, 2 * 9 * 16);
    pacman.setTexture(pac);
    pacman.setPosition(320, 480);
    text.setPosition(32, 672);
    lifes.setPosition(32, 0);
    Rect.setFillColor(Color::Blue);            // collors for map , score & lifes
    text.setFillColor(Color::Yellow);
    lifes.setFillColor(Color::Red);

    //sprite for winning screen
    Sprite winning;
    winning.setTexture(win);

    //sprite for main menu screen
    Sprite Menu;
    Menu.setTexture(menu);

    //sprite for pacman points
    Sprite point;
    point.setTexture(Point);
     //sprite for cherry
    Sprite Cherry;
    Cherry.setTexture(cherry);

    // Scales for sprites
    Menu.setScale(1.68, 2.346);
    winning.setScale(0.2625, 0.44);
    pacman.setScale(1.5, 1.5);
    point.setScale(0.75, 0.75);
    Cherry.setScale(0.0763888888888889, 0.0709459459459459);
    for (int i = 0; i < 4; i++) 
    {
        Ghost[i].setScale(1.523809523809524, 1.560975609756098);

    }


    // starting animation
    pacman.setTextureRect(IntRect(4, 6, 12, 12));
    Ghost[0].setTextureRect(IntRect(0, 0, 64, 64));
    Ghost[1].setTextureRect(IntRect(0, 20.5, 21, 20.5));
    Ghost[2].setTextureRect(IntRect(0, 41, 21, 20.5));
    Ghost[3].setTextureRect(IntRect(0, 61.5, 21, 20.5));

    int pacanimation = 0;
    int pacy = 0;
    int ghostanmi = 0;

    bool intialmovement = true;


    //Music Playing
    Beginning.play();

    //Gameloop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();


            //pacman movement

            // position of square of pacman and squares around it 

            int xcurr, leftnext, rightnext, ycurr, upnext, downnext;

            bool canMoveUp = true , canMoveDown = true , canMoveRight = true , canMoveLeft = true;

            // we divide by 32 to get index on map
            leftnext = (pacman.getPosition().x - 32) / 32;                
            xcurr = (pacman.getPosition().x) / 32;
            rightnext = (pacman.getPosition().x + 32) / 32;
            upnext = (pacman.getPosition().y - 32) / 32;
            ycurr = (pacman.getPosition().y) / 32;
            downnext = (pacman.getPosition().y + 32) / 32;

            // check the abbility to move in each direction 

            if (rec[ycurr][leftnext] == '#')
            {
                canMoveLeft = false;
            }
            if (rec[ycurr][rightnext] == '#')
            {
                canMoveRight = false;
            }
            if (rec[upnext][xcurr] == '#')
            {
                canMoveUp = false;
            }
            if (rec[downnext][xcurr] == '#')
            {
                canMoveDown = false;
            }
    //---------------------------------------------------------------------------------------------------------------------

            if ((Keyboard::isKeyPressed(Keyboard::A)) && canMoveLeft == true) 
            {
                pacman.move(-16, 0);
                pacanimation++;
                pacy = 0;
                ghostanmi = 5;               // link the animation of ghost with the animation of
            }

            else if ((Keyboard::isKeyPressed(Keyboard::D)) && canMoveRight == true)
            {
                pacman.move(16, 0);
                pacman.setOrigin(0, 0);
                pacanimation++;
                ghostanmi = 7;
                pacy = 1;
            }
            else  if ((Keyboard::isKeyPressed(Keyboard::W)) && canMoveUp == true)
            {
                pacman.move(0, -16);
                pacanimation++;
                ghostanmi = 1;
                pacy = 2;
            }
            else  if ((Keyboard::isKeyPressed(Keyboard::S)) && canMoveDown == true) 
            {
                pacman.move(0, 16);
                pacanimation++;
                ghostanmi = 3;
                pacy = 3;
            }
        }
        // to prevent pacman from moving half square

        int xpos = pacman.getPosition().x;
        int ypos = pacman.getPosition().y;
        int remx = xpos % 32;
        int remy = ypos % 32;
        if (remx != 0 || remy != 0)
            pacman.setPosition(xpos - remx, ypos - remy);    


        //Ghost Movement
        CheckSquares();
        int GhostEmptySpace[4];
        int emptycounter = 0;
        for (int ghos = 0; ghos < 4; ghos++)
        {
            for (int Sqr = 0; Sqr < 4; Sqr++)
            {
                if (GhostStorage[ghos].OccupiedSquares[Sqr] == false)
                {
                    emptycounter++;
                }

            }
            GhostEmptySpace[ghos] = emptycounter;
        }

        // initial movement for ghosts

        int intialPosX = pacman.getPosition().x;
        int intialPosY = pacman.getPosition().y;

        if ((intialPosX == 288 || intialPosX == 352) && intialPosY == 480 && intialmovement == true)
        {
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[0].move(-32, 0);
            }

            Ghost[1].move(32, 0);
            Ghost[1].move(0, -32);
            Ghost[1].move(0, -32);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[1].move(-32, 0);
            }

            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[2].move(0, -32);
            }
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[2].move(32, 0);
            }

            Ghost[3].move(-32, 0);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(0, -32);
            }
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(32, 0);
            }

            intialmovement = false;                           // to prevent this controlled movement from being repeated 
            OppositeMovement[0] = 0;
            OppositeMovement[1] = 0;
            OppositeMovement[2] = 1;
            OppositeMovement[3] = 1;
        }
        CheckSquares();

        if (intialmovement == false)
        {
            rec[8][10] = '#';

            for (int G = 0; G < 4; G++)
            {
                if (emptycounter > 2)
                {
                    int Const = 0;
                    Const = 1 + rand() % 4;
                    switch (Const)
                    {
                    case 1:
                        if (GhostStorage[G].OccupiedSquares[0] == false && (0 != OppositeMovement[G]))
                        {
                            Ghost[G].move(32, 0);
                            OppositeMovement[G] = 1;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        break;
                    case 2:
                        if (GhostStorage[G].OccupiedSquares[1] == false && (1 != OppositeMovement[G]))
                        {
                            Ghost[G].move(-32, 0);

                            OppositeMovement[G] = 0;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        break;
                    case 3:
                        if (GhostStorage[G].OccupiedSquares[2] == false && (2 != OppositeMovement[G]))
                        {
                            Ghost[G].move(0, -32);

                            OppositeMovement[G] = 3;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        break;
                    case 4:
                        if (GhostStorage[G].OccupiedSquares[3] == false && (3 != OppositeMovement[G]))
                        {
                            Ghost[G].move(0, 32);

                            OppositeMovement[G] = 2;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        break;
                    default:
                        break;
                    }


                }


            }
        }

        //for menu:Start & Quit    WITH MOUSE
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mouseposition = Mouse::getPosition(window);
            if (mouseposition.x > 354.48 && mouseposition.x < 589.68 && mouseposition.y>192.372 && mouseposition.y < 506.736) {
                window.close();
            }
            else if (mouseposition.x > 84 && mouseposition.x < 322.56 && mouseposition.y>192.372 && mouseposition.y < 506.736) {
                counter = 1;
            }
        }

        text.setString("SCORE: " + to_string(score));
        lifes.setString("Lifes:  " + to_string(x));
        highscores.setString(" " + to_string(score));

        // sound playing
        if (eatingpointstest() == true)
        {
            EatingSound.play();
        }

        if (eatingcherrytest() == true)
        {
            Eatingcherry.play();
        }

        if (gameover() == true && x == 0)
        {
            Death.play();
            counter = 2;
             savetofile( score);
        }

        if (score == 4)
        {
            winningsound.play();
        }

        else if (score == 4) 
        {
            counter = 3;
        }

        //for animation
        pacman.setTextureRect(IntRect(pacanimation * 21.3, pacy * 21.5, 21.3, 21.5));
        Ghost[0].setTextureRect(IntRect(ghostanmi * 21, 0, 21, 20.5));
        Ghost[1].setTextureRect(IntRect(ghostanmi * 21, 20.5, 21, 20.5));
        Ghost[2].setTextureRect(IntRect(ghostanmi * 21, 41, 21, 20.5));
        Ghost[3].setTextureRect(IntRect(ghostanmi * 21, 61.5, 21, 20.5));

        pacanimation %= 3;
        
        window.clear();

        if (counter == 0) 
        {
            window.draw(Menu);
        }

        //draw the game
        else if (counter == 1) 
        {
            //drawing rectangles
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 21; j++)
                {
                    if (rec[i][j] == '#')
                    {
                        window.draw(Rect);
                        Rect.setPosition(j * 32, i * 32);
                    }

                    else if (rec[i][j] == 'P')
                    {
                        window.draw(pacman);
                    }

                    else if (rec[i][j] == 'a')
                    {
                        window.draw(Ghost[0]);
                    }

                    else if (rec[i][j] == 'b')
                    {
                        window.draw(Ghost[1]);
                    }

                    else if (rec[i][j] == 'c')
                    {
                        window.draw(Ghost[2]);
                    }

                    else if (rec[i][j] == 'd')
                    {
                        window.draw(Ghost[3]);
                    }

                    else if (rec[i][j] == '.')
                    {
                        window.draw(point);
                        point.setPosition(2 * j * 16.5, 2 * i * 16.5);
                    }

                    else if (rec[i][j] == 'C')
                    {
                        window.draw(Cherry);
                        Cherry.setPosition(2 * j * 16.5, 2 * i * 16.5);
                    }

                    window.draw(lifes);
                    window.draw(text);
                }
            }

        }

        //draw gameover screen

        else if (counter == 2)
        {
            Texture gameover;
            gameover.loadFromFile("Gameover.jpeg");
            Sprite Gameover;
            Gameover.setTexture(gameover);
            Gameover.setScale(0.6227988878591288, 1.066666666666667);
              window.draw(Gameover);
              counter = 4;
        }

        //draw winning screen
        else if (counter == 3) 
        {
            window.draw(winning);
        }

        else if (counter == 4) {

            window.draw(Highscore);
            window.draw(highscores);
        }



        // to update
        for (int Gg = 0; Gg < 4; Gg++)
        {
            GhostStorage[Gg].OccupiedSquares[0] = true;
            GhostStorage[Gg].OccupiedSquares[1] = true;
            GhostStorage[Gg].OccupiedSquares[2] = true;
            GhostStorage[Gg].OccupiedSquares[3] = true;
        }
        window.display();

    }


}