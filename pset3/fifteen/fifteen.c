/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];
// int blank[10][10];
int bi,bj;
// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
// void sort(int values[], int n);

int main(int argc, string argv[])
{
    
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // sets first tile and counts down to d * d - 1
    int ctr = d * d - 1;
    int i,j;
    int temp[1][1];
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < d; j++)
        {
            board[i][j]=ctr;
            ctr--;
        }
    }
    // if dimensions are even tiles should be odd 
    if ((d*d) % 2 == 0)
    {
        // sets temp tile to swap the "1" and "2"
        temp[0][0] = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp[0][0];
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int i,j;
    // for each row
    for (i = 0; i < d; i++)
    {
        // for each value in row
        for (j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                // save the variables for blank tile
                bi = i;
                bj = j;
                // blank tile = board[i][j];
                printf(" __ ");
            }
            else
            {
            // print value and space
                printf(" %2d ", board[i][j]);
            }
        }
        // print newline
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int temp[1][1];
    int y, z;
    for (y = 0; y < d; y++)
    {
        for (z = 0; z < d; z++)
        {
            // allow only move that is legal (adjacent to blank tile)
            if ((board[y][z] == tile) && ((board[y][z] == board[bi-1][bj]) || (board[y][z] == board[bi][bj+1]) || (board[y][z] == board[bi+1][bj]) || (board[y][z] == board[bi][bj-1]))) 
            {
                // swap tile and blank
                temp[0][0] = board[bi][bj];
                board[bi][bj] = board[y][z];
                board[y][z] = temp[0][0];
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int ctr = 1;
    int i,j;
    {
        // proceed if 0 is on the last tile
        if (board[d - 1][d - 1] == 0)
        {
            for (i = 0; i < d; i++)
            {
                for (j = 0; j < d; j++)
                {
                    /* if ((board[i][j] < board[i][j+1]) || (board[i][j] < board[i+1][j-(d-1)])) second rework */
                    // if tile is on place, continue checking
                    if (ctr == board[i][j])                             //
                    {                                                   //
                        ctr++;                                          // third rework
                        // if penultimate tile is on place return true  //
                        if (ctr == (d * d - 1))                         // 
                        return true;                                    //
                    }
                    // if (ctr == board[i][j])                          //
                    // continue;                                        //  first rework
                    // else                                             //
                    // break;                                           //
                }
            }
            // return true
        }
    }
    return false;
}

    // ctr++;
    // if ((ctr == board[i][j]) && ((d * d - 1) == (board[d][d-2])))// true
    // //  1      1     0  0
    // {
    //     if ((ctr + 1 == board[i][j+1]) || (ctr + 1 == board[i+1][j-(d-1)])) // ( false || false )
    //     //   2          2     0  1         2          0     0    -2 (2)
    //     board[d - 1][d - 1] = d * d;
    //     return true;
    // }
    
    // ctr++;
    // if (((ctr == board[i][j]) && ((ctr + 1 == board[i][j+1]) || (ctr + 1 == board[i+1][j-(d-1)]))) == true )// true
    // //  2      2     0  1
    // {
    //     // if ((ctr + 1 == board[i][j+1]) || (ctr + 1 == board[i+1][j-(d-1)])) // ( false || false )
    //     // //   3          0     0  2         3          0     1    -1 (2)
    //     board[d - 1][d - 1] = d * d;
    //     return 1;
    // }

    // if ((board[i][j] > board[i][j-1]) || (board[i][j] > board[i-1][j+(d-1)]))
                // continue;

    // if (board[i][j] == sort(board[i][j], d * d - 1)
            // return true
            // continue;
    
    // && ((board[i][j] + 1) == board[i][j+1] || (board[i][j] + 1)  == board[i-1][j-(d-1)]))
                        // ((board[i][j] - 1) == board[i][j-1] || (board[i][j] - 1)  == board[i-1][j]) &&
                        // ((board[i][j] + 1) == board[i][j+1] || (board[i][j] + 1) == board[i+1][j]))
                
                    // if ((board [i][j] != 1) && 
                    
                    // return true;
                
                // if (ctr == d * d - 1 && board[0][0] == 1)
    
    // int i,j;
    // for (i = 0; i < d; i++)
    // {
    //     for (j = 0; j < d; j++)
    //     {
    //         if (board[i][j] > board[i][j-1] || board[i][j] > board[i-1][j])
    //         return true;
    //     }
        
    // }
    

// void sort(int values[], int n)
// {
//     int i, j, temp;
//     int swapCtr = -1;
//     for (i = 0; i < n; i++)
//     {
//         for (j = 0; j < n; j++)
//         {
//             if (swapCtr != 0)
//             swapCtr = 0;
//             if (values[i] < values[j])
//             {
//                 temp = values[i];
//                 values[i] = values[j];
//                 values[j] = temp;
//                 swapCtr++;
//             }
//         }
//     }
//     return;
// }