/*******************************************************************************
 * sudokuChecker.h by Geoffrey Sessums
 * Purpose:
 *   Defines constants for
 *       rows
 *       columns
 *       row and column size
 *   Prototypes
 * Notes:
 *   None
 *******************************************************************************/

#define ERROR_PROCESSING 99

// Constants for 9x9 sudoku puzzle array
#define MAXROWS 9
#define MAXCOLUMNS 9
#define MAXSIZE 10

// Prototypes
void actionMenu();
void exitError(char *message);
void getSudokuValues(int sudoku[][MAXCOLUMNS]);
void searchRows(int sudoku[][MAXCOLUMNS], int count[], int);
void searchColumns(int sudoku[][MAXCOLUMNS], int count[], int);
void searchRegions(int sudoku[][MAXCOLUMNS], int count[], int, int);
void printValues(int count[]);
int checkRows(int sudoku[][MAXCOLUMNS]);
int checkColumns(int sudoku[][MAXCOLUMNS]);
int checkRegions(int sudoku[][MAXCOLUMNS]);
