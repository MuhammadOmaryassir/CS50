/**
 * fifteen.c
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

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

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
    FILE *file = fopen("log.txt", "w");
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
        int tile = get_int();
        
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
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    int number = (d * d) - 1 ; // Number Of Slots  Needed
    for( int i = 0 ; i < d ; i++ ) // Loop in Rows
    {
        for( int j = 0 ; j < d ; j++ ) // Loop in colums
        {
            board[i][j] = number ;
          	number -- ;
        }
    }
    if(((d*d) - 1) % 2 != 0) // check if number not even #swap
    {
     	int temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp;
    }
}


/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for( int i = 0 ; i < d ; i++ ) // Loop in Rows
    {
        for( int j = 0 ; j < d ; j++ ) // Loop in colums
        {
            if(board[i][j] == 0) // check of find 0 
            {
                printf(" _ "); // print _ so the player can see the tile
            }
            else
            {
             	printf("%2i " , board[i][j]); // make space befor single digit
            }
        }
        
          printf("\n"); // new line after each  row
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */

bool move(int tile)
{
    // TODO
    int blanki  = 0 ; // ith of the blank 
    int blankj  = 0 ; // jth of the blank 
    int tileloci = 0 ; // ith of tile 
    int tilelocj = 0 ; // jth of tile
    /**
     * loop in the 2D array 
     * get the blank locations
     * get the tile location
     **/
  for ( int i = 0 ; i < d ; i++ )
  {
    for( int j = 0 ; j < d ; j++ )
    {
      if(board[i][j] == 0 ) // get the blank location 
      {
        blanki = i ;
        blankj = j ;
      }
      if(board[i][j] == tile) // get the tile location 
      {
        tileloci = i ;
        tilelocj = j ; 
      }
    
    }
  }
  
  /**
   * check if it's legal move of not 
   * if it's a legal move then swab between tile and blank 
   **/
  if (tileloci == blanki + 1 || tileloci == blanki - 1 || tilelocj == blankj + 1 || tilelocj == blankj - 1)
   if ((tileloci == blanki + 1 && tilelocj == blankj) || (tileloci == blanki - 1 && tilelocj == blankj) || (tileloci == blanki && tilelocj == blankj + 1) || (tileloci == blanki && tilelocj == blankj - 1))
        {
            int temp = board[tileloci][tilelocj];
         	board[tileloci][tilelocj] = board[blanki][blankj];
         	board[blanki][blankj] = temp;
            return true ;
       }
    return false;
}
/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    /**
     * another array 
     * sorted in the right way 
     **/
  int check[DIM_MAX][DIM_MAX]; 
  int Number = 1; 
  for( int i = 0 ; i < d ; i++ )
  {
    for( int j = 0 ; j < d ; j++ )
    {
      if(Number == (d*d)) 
      {
        Number=0 ;
      }
       check[i][j] = Number ;
        Number++;
    }
  }
  int trick = 0 ; // var  to count how many number in his place 
  for( int i = 0 ; i < d ; i++ )
  {
    for( int j = 0 ; j < d ; j++ )
    {
      if ( board[i][j] == check[i][j] ) // check of the 2 arrays are equals to each others
        trick ++;
    }
  }
  if(trick==(d*d)) // if   all numbers on its places return true
    return true;
  else
    return false;
}
