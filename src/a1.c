/*************************a1.c****************************
Student Name: Nicholas Macedo                    Student Number:
Date: Jamuary 16th 2015                          Course Name:CIS 2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include "a1.h"

int main()
{
    int i = 0;
    char actionChar = 0;
    int gameDone = 0;
    int turn = 0;
    bool gameCont = true;
    char playerOne[12] = "000000000000";
    char playerTwo[12] = "000000000000";

    //Input of player names before game
    printf("Hello! Welcome to Obstruction!\n");
    printf("Before we begin could you please enter the name of the two players.\n");
    printf("What is your name player one?(Type it in.)\n");
    scanf("%s", playerOne);
    printf("What is your name player two?(Type it in.)\n");
    scanf("%s", playerTwo);

    //ncurses init
    initscr();
    cbreak();
    noecho();
    start_color();

    //Game Board Drawing
    for (i = 0; i < 13; i ++)
    {
        if (i % 2 == 0)
        {
            mvprintw(i,0,"+-+-+-+-+-+-+");
        }
        else
        {
            mvprintw(i,0,"| | | | | | |");
        }
    }

    //Drawing of the Second Board and printing of the rules and help info.
    secondaryBoard();
    helpInfo();
    mvprintw(11,16,"Game Feed:");
    move(1,1);
    refresh();

    //Start Game Play
    while (actionChar != 'q')
    {
        mvprintw(11,27,"%s it is your turn.", playerOne);
        move(1,1);
        refresh();
        turn = 1;
        gameDone = playerAction(actionChar,turn);  //calls playerAction

        if (gameDone == 1)
        {
            break;      //checks to see if the game is over
        }

        refresh();

        gameCont = boardFull();

        if (gameCont == true)
        {
            break;     //checks to see if the gameboard is full
        }

        mvprintw(11,27,"%s it is your turn.", playerTwo);
        move(1,1);
        refresh();
        turn = 2;

        gameDone = playerAction(actionChar,turn);

        if (gameDone == 1)
        {
            break;
        }

        gameCont = boardFull();

        if (gameCont == true)
        {
            break;
        }
        refresh();
    }

    //Used for when q is pushed else displays winner
    if (gameDone == 1)
    {
        endwin();
        return(0);
    }

    if (turn == 1)
    {
        mvprintw(11,27,"%s wins. Any key quits.", playerOne);
        move(1,1);
    }
    else
    {
        mvprintw(11,27,"%s wins. Any key quits.", playerTwo);
    }

    getch();
    endwin();
    return(0);

}
/*
playerAction: reads player input and acts accordingly. Loops until player chooses a spot and places either x or o.
In:actionChar (Key pressed) and turn (player turn)
Out:returns 1 if the game is done early (Q is pressed) or zero if the function runs through without Q being pressed.
What it does:Uses case to determine what to do with input and acts accordingly. Keeps movement inside board using an if statement.
*/
int playerAction(char actionChar,int turn)
{
    int yCord = 0;
    int xCord = 0;
    int turnOver = 0;

    while (turnOver == 0)
    {
        actionChar = getch();
        getyx(stdscr,yCord,xCord);

        switch (actionChar)
        {
        case 'i':
            yCord = yCord - 2;
            break;

        case 'k':
            yCord = yCord + 2;
            break;

        case 'j':
            xCord = xCord - 2;
            break;

        case 'l':
            xCord = xCord + 2;
            break;

        case 'p':
            turnOver = placeMove(yCord,xCord,turn);
            break;

        case 'h':
            hintPlayer();
            break;

        case 'q':
            return(1);
            break;

        default:
            mvprintw(11,27,"                                       ");
            mvprintw(11,27,"Invalid Input.");

    }

    //Keeps Cursor Inside Game Board
        if ( yCord > 12 || xCord > 12 )
        {
            move(1,1);
            refresh();
        }
        else
        {
            move(yCord,xCord);
            refresh();
        }
    }
    return(0);

}
/*
placeMove:Upon pushing Q it checks for if the space is open and if so places either an X or an O in the spot chosen.
In:yCord and xCord to know what spot to check, turn to check who's turn it is.
Out:Returns 0 if there is something blocking the spot else returns 1.
What it does:uses a case switch to see if anything is in that spot, if not then uses the  blank space to place the X or O and the &'s around it.
*/
int placeMove (int yCord, int xCord,int turn)
{
    char currentChar = 'f';

    /*Color Init*/
    //For the X's
    init_pair(1,COLOR_BLACK,COLOR_CYAN);
    //For the O's
    init_pair(2,COLOR_BLACK,COLOR_GREEN);
    //For the &'s
    init_pair(3,COLOR_WHITE,COLOR_RED);

    currentChar = mvinch(yCord,xCord);
    mvprintw(11,27,"                                ");

    switch (currentChar)
    {
    case 'X':
        mvprintw(11,27,"Invalid Move.");
        return (0);
        break;

    case 'O':
        mvprintw(11,27,"Invalid Move.");
        return(0);
        break;

    case '&':
        mvprintw(11,27,"Invalid Move.");
        return(0);
        break;

    case ' ':
        mvprintw(11,27,"                                     ");

        if (turn == 1)
        {
            attron(COLOR_PAIR(1));
            mvprintw(yCord,xCord,"X");  //prints X for Player 1
            attroff(COLOR_PAIR(1));
        }
        else
        {
            attron(COLOR_PAIR(2));
            mvprintw(yCord,xCord,"O");  //prints O for Player 2
            attroff(COLOR_PAIR(1));
        }

        /*Printing of the & in the blocked spots*/
        attron(COLOR_PAIR(3));
        //Top Right
        if (((yCord - 2) > 0) && ((xCord - 2) > 0))
        {
            mvprintw(yCord -2,xCord-2,"&");
        }

        //Top
        if ((yCord - 2) > 0)
        {
            mvprintw(yCord - 2,xCord,"&");
        }

        //Top Left
        if (((yCord - 2) > 0) && ((xCord + 2) < 12))
        {
            mvprintw(yCord - 2,xCord + 2,"&");
        }

        //Center Right
        if ((xCord - 2) > 0)
        {
            mvprintw(yCord,xCord - 2,"&");
        }

        //Center Left
        if ((xCord + 2) < 12)
        {
            mvprintw(yCord,xCord + 2,"&");
        }

        //Bottom Right
        if (((yCord + 2) < 12) && ((xCord - 2) > 0))
        {
            mvprintw(yCord + 2,xCord - 2,"&");
        }

        //Bottom
        if ((yCord + 2) < 12)
        {
            mvprintw(yCord + 2,xCord,"&");
        }

        //Bottom Left
        if (((yCord + 2) < 12) && ((xCord + 2) < 12))
        {
            mvprintw(yCord + 2,xCord +2,"&");
        }
        attroff(COLOR_PAIR(1));
        break;

    default:
        mvprintw(11,27,"Invalid Move.");
    }

    refresh();
    return(1);

}
/*
boardFull: Checks to see if the board is full and if the game is over.
In: Nothing is required for the input.
Out:The function returns either true or false.
What it does: The function cycles through the board and checks for any spaces. If it
              finds a space it sends back true then the game is over.
*/
bool boardFull()
{
    int i = 0;
    int j = 0;
    char isFinished = 'f';
    bool gameCont = true;

    for (i=0;i<13;i++)
    {
        for (j = 0; j < 13; j ++)
        {
            isFinished = mvinch(i,j);
            if (isFinished == ' ')
            {
                gameCont = false;
            }
        }
    }
    return(gameCont);

}
/*
hintPlayer: When user pushes H it finds a blank space for the user to play.
In: Nothing. It is a void function.
Out: Nothing. It is a void function.
What it does: It uses two for loops and checks for a blank spot then changes it to yellow
              to hint the user where they should go.
*/
void hintPlayer()
{
    int i = 0;
    int j = 0;
    char isEmpty = 'f';

    //Setting the Color for the help
    init_pair(4,COLOR_WHITE,COLOR_YELLOW);

    //Loops through the grid to find open spot then highlights yellow for user.
    for (i = 0; i < 13; i ++)
    {
        for (j = 0; j < 13; j ++)
        {
            isEmpty = mvinch(i,j);
            if (isEmpty == ' ')
            {
                attron(COLOR_PAIR(4));
                mvprintw(i,j," ");
                attroff(COLOR_PAIR(4));
                mvprintw(11,27,"Player hint in yellow.");
                return;
            }
        }
    }

}
/*
secondaryBoard: Draws the secondary board that surrounds the help/info text.
In: Nothing is required.
Out: Nothing. It is a void function.
What it does: Uses a for loop to print the board.
*/
void secondaryBoard()
{
    int i = 0;

    mvprintw(0,15,"+-----------------------------------------+");
    for (i = 1; i < 11; i ++)
    {
        if (i == 10)
        {
            mvprintw(10,15,"+-----------------------------------------+");
        }
        else
        {
            mvprintw(i,15,"|                                         |");
        }
    }
    mvprintw(12,15,"+-----------------------------------------+");

}
/*
helpInfo: Prints all the messages in the help to the screen.
In: Nothing. Its a void function.
Out: Nothing. Its a void function.
What it does: Uses the print statements to print to specific locations on the screen.
*/
void helpInfo()
{
    mvprintw(1,20,"Welcome to the game Obstruction!");
    mvprintw(2,19,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    mvprintw(3,17,"Game Controlls:");
    mvprintw(4,18,"i-Up");
    mvprintw(5,18,"k-Down");
    mvprintw(6,18,"j-Right");
    mvprintw(7,18,"l-Left");
    mvprintw(8,18,"p-Play");
    mvprintw(9,18,"h-Hint");
    mvprintw(3,36,"Game Information:");
    mvprintw(4,37,"-fill board to win");
    mvprintw(5,37,"-play in empty spot");
    mvprintw(6,37,"-lose if can't play");
    mvprintw(7,37,"-cannot play on X/O");
    mvprintw(8,37,"-cannot play on &'s");
    mvprintw(9,37,"-enjoy the game! :)");

}
