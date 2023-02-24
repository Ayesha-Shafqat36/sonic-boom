#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x,int y)
{
 COORD coordinates;
 coordinates.X =x;
 coordinates.Y =y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
char getCharAtxy(short int x,short int y)
{
    CHAR_INFO ci;
    COORD xy = {0,0};
    SMALL_RECT rect={x,y,x,y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

// bullet count Arrays
int bulletX[200];
int bulletY[200];
bool bulletActive[200];

// Sonic bullets
int bulletCount =0;

// ENEMY CHARACTER BULLETS

// EggPawn bullets 
int pawn_BulletX[200];
int pawn_BulletY[200];
bool pawn_BulletActive[200];
int pawnBulletCount = 0;

// Death EggRobot bullets
int robo_BulletX[200];
int robo_BulletY[200];
bool robo_BulletActive[200];
int robotBulletCount = 0;

//Death Eggrobot2 bullets
int robo2_BulletX[200];
int robo2_BulletY[200];
bool robo2_BulletActive[200];
int robot_BulletCount = 0;

// Sonic character
char heart=3;
char sonic1[5]={' ','^','_','^',' '};
char sonic2[5]={'|',heart,'_',heart,'|'};
char sonic3[5]={' ','-','-','-',' '};

int sonicX=2;
int sonicY=2;

// ENEMY CHARACTERS 

// Enemy1(eggMan) character
char crystal=4;
char eggman1[5]={' ',crystal,' ',crystal,' '};
char eggman2[5]={' ','_','_','_',' '};
char eggman3[5]={'[','_','_','_',']'};

int eggmanX=10;
int eggmanY=10;

// Enemy2(EggPawn) character
char v=249;
char eggPawn1[5]={' ',' ',v,'_',v};
char eggPawn2[5]={'<','-','|','_','|'};

int eggPawnX=110;
int eggPawnY=10;

// Enemy3(deathEggRobot) character
char box=219;
char deathEggRobot1[3]={' ','^',' '};
char deathEggRobot2[3]={' ','|',' '};
char deathEggRobot3[3]={box,box,box};

int deathEggRobotX=77;
int deathEggRobotY=18;

char deathEggRobott1[3]={' ','^',' '};
char deathEggRobott2[3]={' ','|',' '};
char deathEggRobott3[3]={box,box,box};

int deathEggRobottX=38;
int deathEggRobottY=22;

void printMaze();
void printSonic();
void printEggMan();
void printEggPawn();
void printDeathEggRobot();
void printDeathEggRobott();
void moveSonicLeft();
void moveSonicRight();
void moveSonicUp();
void moveSonicDown();
void eraseSonic();
void eraseEggMan();
void eraseEggPawn();
void eraseDeathEggRobot();
void moveEggMan();
void moveEggManUp();
void moveEggManDown();
void moveEggManRight();
void moveEggManLeft();
void moveEggPawn();
void generateBullet();
void moveBullet();
void printBullet(int x,int y);
void eraseBullet(int x,int y);
void makeBulletInactive(int i);
void pawnBulletInactive(int i);
void pawnBullet();
void movePawnBullet();
void robotBullet();
void moveRobotBullet();
void robot_Bullet();
void moveRobot_Bullet();
void roboBulletInactive(int i);
void robo_BulletInactive(int i);
void addScoreLeft();
void addScoreRight();
void addScoreUp();
void addScoreDown();
void addScore();
void printScore();
void lifeCount();
void printLifeCount();
void addLifeLeft();
void addLifeRight();
void addLifeUp();
void addLifeDown();
void eggPawnBulletCollisionWithSonic();
void robo_BulletCollisionWithSonic();
void robo2_BulletCollisionWithSonic();
void gameOver();

string Direction="Down";
string Direction_2="Right";
int timer = 0;
int timerr = 0;
int r_timer = 0;
int r2_timer = 0;
int e_timer = 0;
int score = 0;
int healthPallets = 6;

main()
{
    system("cls");
    printMaze();
    printSonic();
    printEggMan();
    printEggPawn();
    printDeathEggRobot();
    printDeathEggRobott();
    
    while(true)
    {
        printLifeCount();
        printScore();
        if(GetAsyncKeyState(VK_LEFT))
        {
            moveSonicLeft();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            moveSonicRight();
        }
        if(GetAsyncKeyState(VK_UP))
        {
            moveSonicUp();
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            moveSonicDown();
        }
        if(GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }
        if (timer == 3)
        {
            moveEggPawn();
            if (timerr == 9)
            {
            pawnBullet();
            timerr=0;
            }
            timer=0;
        }
        if(e_timer == 3)
        {
            moveEggMan();
            e_timer = 0;
        }
        if (r_timer == 9)
        {
            printDeathEggRobot();
            robotBullet();
            r_timer =0;
        }
        if (r2_timer == 9)
        {
            printDeathEggRobott();
            robot_Bullet();
            r2_timer = 0;
        }
        if (healthPallets == 0)
        {
            system("cls");
            gameOver();
            cout << endl << endl;
            cout << "SCORE : " << score;
            break;
        }
        moveRobot_Bullet();
        movePawnBullet();
        moveRobotBullet();
        moveBullet();
        eggPawnBulletCollisionWithSonic();
        robo_BulletCollisionWithSonic();
        robo2_BulletCollisionWithSonic();
        timerr++;
        timer++;
        r_timer++;
        r2_timer++;
        e_timer++;
        Sleep(90);
    }
}
void printMaze()
{
    cout << "|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|"<<endl;
    cout << "|%|                                                    |         |         |                          |                           |%|"<<endl;
    cout << "|%|                                                    |         |         |             o o o o o o o|                           |%|"<<endl;
    cout << "|%|                                                    |         |     o o |                          |                           |%|"<<endl;
    cout << "|%|                                                    |         |     o o |                                                      |%|"<<endl;
    cout << "|%|                                                    |         |     o o |                                                      |%|"<<endl;
    cout << "|%|                                                    |         |     o o |                |__________              _____________|%|"<<endl;
    cout << "|%|                                                    |         |     o o |                           |                          |%|"<<endl;               
    cout << "|%|                                          |         |         |     o o |_________                  |                          |%|"<<endl;                      
    cout << "|%|                                          |                   |     o o                             |                          |%|"<<endl;
    cout << "|%|                                          |                   |                                     |______________            |%|"<<endl;
    cout << "|%|                                          |                   |                                                                |%|"<<endl;
    cout << "|%|                              |           |_________          |         _________________                                      |%|"<<endl;
    cout << "|%|                              |                o o o o o o o o|                          |                                     |%|"<<endl;
    cout << "|%|                              |                               |                         0|                        |            |%|"<<endl;
    cout << "|%|                              |                               |                          |                        |            |%|"<<endl;
    cout << "|%|                              |            ___________________|                          |________________________|            |%|"<<endl;
    cout << "|%|                              |                                                                                   |            |%|"<<endl;
    cout << "|%|                              |                 0                      |                  o o o o o o o o o o o o |            |%|"<<endl;
    cout << "|%|                              |                                       0|                                          |            |%|"<<endl;
    cout << "|%|                              |                         _______________|___________                               |            |%|"<<endl;
    cout << "|%|                              |           |                                     | o                               |            |%|"<<endl;
    cout << "|%|                              |           |                                     | o                               |            |%|"<<endl;
    cout << "|%|                              |           |                                     | o                               |            |%|"<<endl;
    cout << "|%|__________         ___________|___________|_____________                ________| o                               |            |%|"<<endl;
    cout << "|%|                                          |                                     | o                  |            |____________|%|"<<endl;
    cout << "|%|                                          |                                     |_________           |                         |%|"<<endl;
    cout << "|%|                    o o o o o o o o o o o |                                     |                    |                         |%|"<<endl;
    cout << "|%|                                         0|                                    0|                    |o o o o o o o o o o o o o|%|"<<endl;
    cout << "|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|%|"<<endl;
}
// Print sonic function
void printSonic()
{
    gotoxy(sonicX,sonicY);
    for(int i=0; i<5; i++)
    {
        cout<< sonic1[i];
    }
    gotoxy(sonicX,sonicY+1);
    for(int i=0; i<5; i++)
    {
        cout<< sonic2[i];
    }
    gotoxy(sonicX,sonicY+2);
    for(int i=0; i<5; i++)
    {
        cout<< sonic3[i];
    }
}

   //PRINT ENEMIES FUNCTIONS

// Print EggMan function
void printEggMan()
{
    gotoxy(eggmanX,eggmanY);
    for(int i=0; i<5; i++)
    {
        cout<< eggman1[i];
    }
    gotoxy(eggmanX,eggmanY+1);
    for(int i=0; i<5; i++)
    {
        cout<< eggman2[i];
    }
    gotoxy(eggmanX,eggmanY+2);
    for(int i=0; i<5; i++)
    {
        cout<< eggman3[i];
    }
}
// Print EggPawn function
void printEggPawn()
{
    gotoxy(eggPawnX,eggPawnY);
    for(int i=0; i<5; i++)
    {
        cout<< eggPawn1[i];
    }
    gotoxy(eggPawnX,eggPawnY+1);
    for(int i=0; i<5; i++)
    {
        cout<< eggPawn2[i];
    }
}
// Print Death EggRobot function
void printDeathEggRobot()
{
    gotoxy(deathEggRobotX,deathEggRobotY);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobot1[i];
    }
    gotoxy(deathEggRobotX,deathEggRobotY+1);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobot2[i];
    }
    gotoxy(deathEggRobotX,deathEggRobotY+2);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobot3[i];
    }
}
// Print Death EggRobot 2 function
void printDeathEggRobott()
{
    gotoxy(deathEggRobottX,deathEggRobottY);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobott1[i];
    }
    gotoxy(deathEggRobottX,deathEggRobottY+1);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobott2[i];
    }
    gotoxy(deathEggRobottX,deathEggRobottY+2);
    for(int i=0; i<3; i++)
    {
        cout<< deathEggRobott3[i];
    }
}

    //SONIC MOVEMENT FUNCTIONS

// funtion to move sonic left
void moveSonicLeft()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX - 1, sonicY + y);
    if (next != ' ' && next != 'o' && next != '0')
    {
       return;
    }
    }
    eraseSonic();
    sonicX = sonicX - 1;
    printSonic();
    addScoreLeft();
    addLifeLeft();
}
// funtion to move sonic right
void moveSonicRight()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX + sizeof(sonic3), sonicY + y);
    if (next != ' ' && next != 'o' && next != '0')
    {
        return;
    }
    }
    eraseSonic();
    sonicX = sonicX + 1;
    printSonic();
    addScoreRight();
    addLifeRight();
}
// funtion to move sonic up
void moveSonicUp()
{
    for(int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x, sonicY - 1);
    if (next != ' ' && next != 'o'&& next != '0')
    {
        return;
    }
    }
    eraseSonic();
    sonicY = sonicY - 1;
    printSonic();
    addScoreUp();
    addLifeUp();
}
// funtion to move sonic down
void moveSonicDown()
{
    for (int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x,sonicY + 3);
    if(next != ' ' && next != 'o'&& next != '0')
    {
        return;
    }
    }
    eraseSonic();
    sonicY = sonicY + 1;
    printSonic();
    addScoreDown();
    addLifeDown();
}

    //ERASE SONIC FUNCTION

// function to erase already present sonic
void eraseSonic()
{
    gotoxy(sonicX,sonicY);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
    gotoxy(sonicX,sonicY+1);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
    gotoxy(sonicX,sonicY+2);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
}

    //ERASE ENEMIES FUNCTIONS

// function to erase already present Eggman
void eraseEggMan()
{
    gotoxy(eggmanX,eggmanY);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
    gotoxy(eggmanX,eggmanY+1);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
    gotoxy(eggmanX,eggmanY+2);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
}
// function to erase already present EggPawn
void eraseEggPawn()
{
    gotoxy(eggPawnX,eggPawnY);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
    gotoxy(eggPawnX,eggPawnY+1);
    for(int i=0; i<5; i++)
    {
        cout<< " ";
    }
}
// function to erase already present Death EggRobot
void eraseDeathEggRobot()
{
    gotoxy(deathEggRobotX,deathEggRobotY);
    for(int i=0; i<3; i++)
    {
        cout<< " ";
    }
    gotoxy(deathEggRobotX,deathEggRobotY+1);
    for(int i=0; i<3; i++)
    {
        cout<< " ";
    }
    gotoxy(deathEggRobotX,deathEggRobotY+2);
    for(int i=0; i<3; i++)
    {
        cout<< " ";
    }
}

    //ENEMIES MOVEMENT FUNCTIONS

// function to move EggMan
void moveEggMan()
{
    int X= eggmanX-sonicX;
    int Y= eggmanY-sonicY;
   
    if (X > 0)
    {
        moveEggManLeft();
    }
    if (X < 0)
    {
        moveEggManRight();
    }
    if (Y > 0)
    {
        moveEggManUp();
    }
    if (Y < 0)
    {
        moveEggManDown();
    }
}
// function to move EggMan up
void moveEggManUp()
{
    for(int x=0; x<sizeof(eggman3); x++)
    {
    char next = getCharAtxy(eggmanX + x, eggmanY - 1);
    if (next != ' ')
    {
        return;
    }
    }
    eraseEggMan();
    eggmanY--;
    printEggMan();
}
// function to move EggMan Down
void moveEggManDown()
{
    for(int x=0; x<sizeof(eggman3); x++)
    {
    char next = getCharAtxy(eggmanX + x, eggmanY + 3);
    if (next != ' ')
    {
        return;
    }
    }
    eraseEggMan();
    eggmanY=eggmanY+1;
    printEggMan();
}
// function to move EggMan Right
void moveEggManRight()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(eggmanX + sizeof(eggman3), eggmanY +y);
    if (next !=' ')
    {
       return;
    }
    }
    eraseEggMan();
    eggmanX++;
    printEggMan();
}
// function to move EggMan Left
void moveEggManLeft()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(eggmanX - 1, eggmanY + y);
    if (next !=' ')
    {
       return;
    }
    }
    eraseEggMan();
    eggmanX--;
    printEggMan();
}
// function to move EggPawn
void moveEggPawn()
{
    if(Direction == "Up")
    {
        char next1 = getCharAtxy(eggPawnX    , eggPawnY - 1);
        char next2 = getCharAtxy(eggPawnX + 1, eggPawnY - 1);
        if (next1 == ' ' && next2 == ' ')
        {
            eraseEggPawn();
            eggPawnY--;
            printEggPawn();
        }
        else
        {
            Direction = "Down";
        }
    }
    if(Direction == "Down")
    {
        char next1 = getCharAtxy(eggPawnX     , eggPawnY + 2);
        char next2 = getCharAtxy(eggPawnX + 1 , eggPawnY + 2);
        if (next1 == ' ' && next2 == ' ')
        {
            eraseEggPawn();
            eggPawnY++;
            printEggPawn();
        }
        else
        {
            Direction = "Up";
        }
    }
    if(Direction_2 == "Right")
    {
        char next1 = getCharAtxy(eggPawnX    , eggPawnY    );
        char next2 = getCharAtxy(eggPawnX + 5, eggPawnY + 1);
        char next3 = getCharAtxy(eggPawnX + 5, eggPawnY + 2);
        char next4 = getCharAtxy(eggPawnX + 5, eggPawnY + 3);
        char next5 = getCharAtxy(eggPawnX + 5, eggPawnY + 4);

       if (next1 == ' ' && next2 == ' ' && next3 == ' ' && next4 == ' ' && next5 == ' ')
       {
           eraseEggPawn();
           eggPawnX++;
           printEggPawn();
       }
       else
       {
           Direction_2 = "Left";
       }
    }
   if(Direction_2 == "Left")
    {
       char next1 = getCharAtxy(eggPawnX    , eggPawnY    );
       char next2 = getCharAtxy(eggPawnX - 1, eggPawnY + 1);
       char next3 = getCharAtxy(eggPawnX - 1, eggPawnY + 2);
       char next4 = getCharAtxy(eggPawnX - 1, eggPawnY + 3);
       char next5 = getCharAtxy(eggPawnX - 1, eggPawnY + 4);

       if (next1 == ' ' && next2 == ' ' && next3 == ' ' && next4 == ' ' && next5 == ' ')
       {
           eraseEggPawn();
           eggPawnX--;
           printEggPawn();
       }
       else
       {
           Direction_2 = "Right";
       }
    }
}
// GENERATE SONIC BULLET FUNCTIONS

// Bullet generate function of sonic
void generateBullet()
{
    bulletX[bulletCount] = sonicX + 6;
    bulletY[bulletCount] = sonicY;
    bulletActive[bulletCount] = true;
    gotoxy(sonicX + 6, sonicY);
    cout << ".";
    bulletCount++;
}
// move bullet function
void moveBullet()
{
    for(int x =0; x < bulletCount; x++)
    {
        if (bulletActive[x] == true)
        {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            if (next != ' ')
            {
                eraseBullet(bulletX[x],bulletY[x]);
                makeBulletInactive(x);
            }
            else
            {
                eraseBullet(bulletX[x],bulletY[x]);
                bulletX[x] = bulletX[x] + 1;
                printBullet(bulletX[x],bulletY[x]);
            }
        }
    }
}
// function to print bullet
void printBullet(int x,int y)
{
    gotoxy(x,y);
    cout << ".";
}
// function to erase bullet 
void eraseBullet(int x,int y)
{
    gotoxy(x,y);
    cout << " ";
}
// function to inactivate the bullet
void makeBulletInactive(int i)
{
    bulletActive[i] = false;
}

//ENEMIES BULLETS

// Bullet generate function of EggPawn
void pawnBulletInactive(int i)
{
    pawn_BulletActive[i] = false;
}
void pawnBullet()
{
    pawn_BulletX[pawnBulletCount] = eggPawnX - 1;
    pawn_BulletY[pawnBulletCount] = eggPawnY;
    pawn_BulletActive[pawnBulletCount] = true;
    gotoxy(eggPawnX-1, eggPawnY);
    cout << ".";
    pawnBulletCount++;
}
// move egg pawn bullet function
void movePawnBullet()
{
    for(int x =0;x < pawnBulletCount; x++)
    {
        if (pawn_BulletActive[x] == true)
        {
            char next = getCharAtxy(pawn_BulletX[x] - 1, pawn_BulletY[x]);
            if (next != ' ')
            {
                eraseBullet(pawn_BulletX[x],pawn_BulletY[x]);
                pawnBulletInactive(x);
            }
            else
            {
                eraseBullet(pawn_BulletX[x],pawn_BulletY[x]);
                pawn_BulletX[x] = pawn_BulletX[x] - 1;
                printBullet(pawn_BulletX[x],pawn_BulletY[x]);
            }
        }
    }
}
// Bullet generate function of EggRobot
void roboBulletInactive(int i)
{
    robo_BulletActive[i] = false;
}
void robotBullet()
{
    robo_BulletX[robotBulletCount] = deathEggRobotX;
    robo_BulletY[robotBulletCount] = deathEggRobotY - 2;
    robo_BulletActive[robotBulletCount] = true;
    gotoxy(deathEggRobotX, deathEggRobotY - 2);
    cout << ".";
    robotBulletCount++;
}
// move egg pawn bullet function
void moveRobotBullet()
{
    for(int x =0;x < robotBulletCount; x++)
    {
        if (robo_BulletActive[x] == true)
        {
            char next = getCharAtxy(robo_BulletX[x], robo_BulletY[x] - 2);
            if (next != ' ')
            {
                eraseBullet(robo_BulletX[x],robo_BulletY[x]);
                roboBulletInactive(x);
            }
            else
            {
                eraseBullet(robo_BulletX[x],robo_BulletY[x]);
                robo_BulletY[x]--;
                printBullet(robo_BulletX[x],robo_BulletY[x]);
            }
        }
    }
}
// Bullet generate function of EggRobot 2
void robo_BulletInactive(int i)
{
    robo2_BulletActive[i] = false;
}
void robot_Bullet()
{
    robo2_BulletX[robot_BulletCount] = deathEggRobottX;
    robo2_BulletY[robot_BulletCount] = deathEggRobottY - 2;
    robo2_BulletActive[robot_BulletCount] = true;
    gotoxy(deathEggRobottX, deathEggRobottY - 2);
    cout << ".";
    robot_BulletCount++;
}
// move EggRobot 2 bullet function
void moveRobot_Bullet()
{
    for(int x =0;x < robot_BulletCount; x++)
    {
        if (robo2_BulletActive[x] == true)
        {
            char next = getCharAtxy(robo2_BulletX[x], robo2_BulletY[x] - 2);
            if (next != ' ')
            {
                eraseBullet(robo2_BulletX[x],robo2_BulletY[x]);
                robo_BulletInactive(x);
            }
            else
            {
                eraseBullet(robo2_BulletX[x],robo2_BulletY[x]);
                robo2_BulletY[x]--;
                printBullet(robo2_BulletX[x],robo2_BulletY[x]);
            }
        }
    }
}
// FUNCTIONS TO ADD SCORE

//function to add score
void addScore()
{
    score++;
}
//function to print score
void printScore()
{
    gotoxy(45, 30);
    cout << "SCORE : " << score;
}

// function to add score left
void addScoreLeft()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX - 1, sonicY + y);
    if (next == 'o')
    {
       addScore();
    }
    }
}
// funtion to add score right
void addScoreRight()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX + sizeof(sonic3), sonicY + y);
    if (next == 'o')
    {
        addScore();
    }
    }
}
// funtion to add score sonic up
void addScoreUp()
{
    for(int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x, sonicY - 1);
    if (next == 'o')
    {
        addScore();
    }
    }
}
// funtion to add score sonic down
void addScoreDown()
{
    for (int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x,sonicY + 3);
    if(next == 'o')
    {
        addScore();
    }
    }
}

// LIFE COUNT FUNCTIONS

//function to decrease life count
void lifeCount()
{
    healthPallets--;
}
//function to print life count
void printLifeCount()
{
    gotoxy(45,31);
    cout << "LIFE COUNTS : " << healthPallets;
}
// function of eggpawn's bullets collision with Sonic 
void eggPawnBulletCollisionWithSonic()
{
    for(int i=0; i < pawnBulletCount; i++)
    {
        if(pawn_BulletActive[i] == true)
        {
            if((pawn_BulletX[i] == sonicX ||pawn_BulletX[i] == sonicX + 1 || pawn_BulletX[i] == sonicX + 2 || pawn_BulletX[i] == sonicX + 3 ||  pawn_BulletX[i] == sonicX + 4 ) && (pawn_BulletY[i] == sonicY || pawn_BulletY[i] == sonicY - 1))
            {
                lifeCount();
            }
        }
    }
}
// function of robot1's bullets collision with sonic
void robo_BulletCollisionWithSonic()
{
    for(int i=0; i < robotBulletCount; i++)
    {
        if(robo_BulletActive[i] == true)
        {
            if((robo_BulletY[i] == sonicY  || robo_BulletY[i] == sonicY + 1 || robo_BulletY[i] == sonicY + 2)&& (robo_BulletX[i] == sonicX || robo_BulletX[i] == sonicX - 1 || robo_BulletX[i] == sonicX - 2 || robo_BulletX[i] == sonicX - 3 || robo_BulletX[i] == sonicX - 4))
            {
                lifeCount();
            }
        }
    }
}
// function of robot2's collision with sonic
void robo2_BulletCollisionWithSonic()
{
    for(int i=0; i < robot_BulletCount; i++)
    {
        if(robo2_BulletActive[i] == true)
        {
            if((robo2_BulletY[i] == sonicY || robo2_BulletY[i] == sonicY + 1 || robo2_BulletY[i] == sonicY + 2)&& (robo2_BulletX[i] == sonicX || robo2_BulletX[i] == sonicX - 1 || robo2_BulletX[i] == sonicX - 2 || robo2_BulletX[i] == sonicX - 3 || robo2_BulletX[i] == sonicX - 4))
            {
                lifeCount();
            }
        }
    }
}
// function of EggMan collision with sonic

// function to add life left
void addLifeLeft()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX - 1, sonicY + y);
    if (next == '0')
    if(healthPallets < 6)
    {
    {
       healthPallets++;
    }
    }
    }
}
// funtion to add score right
void addLifeRight()
{
    for(int y=0; y<3; y++)
    {
    char next = getCharAtxy(sonicX + sizeof(sonic3), sonicY + y);
    if (next == '0')
    if(healthPallets < 6)
    {
    {
        healthPallets++;
    }
    }
    }
}
// funtion to add score sonic up
void addLifeUp()
{
    for(int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x, sonicY - 1);
    if (next == '0')
    if(healthPallets < 6)
    {
    {
        healthPallets++;
    }
    }
    }
}
// funtion to add score sonic down
void addLifeDown()
{
    for (int x=0; x<sizeof(sonic3); x++)
    {
    char next = getCharAtxy(sonicX + x,sonicY + 3);
    if(next == '0')
    if(healthPallets < 6)
    {
    {
        healthPallets++;
    }
    }
    }
}

// GAME OVER FUNCTION

void gameOver()
{
    cout<< "    ###      ##      ##     ##    #####      ###     ##     ##    #####    ###  " << endl;
    cout<< "  ##       ##  ##    ## # # ##    ##       ##   ##    ##   ##     ##     ##   ##" << endl;
    cout<< "  ## ###   ######    ##  #  ##    ####     ##   ##     ## ##      ####   #####  " << endl;
    cout<< "  ##  ##   ##  ##    ##     ##    ##       ##   ##      ###       ##     ##  ## " << endl;
    cout<< "   ####    ##  ##    ##     ##    #####      ###         #        #####  ##   ##" << endl;
}