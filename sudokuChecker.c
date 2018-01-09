/*******************************************************************************
 * sudokuChecker.c
 * Purpose:
 *  Verifies a proposed Sudoku solution from a text file following the Sudoku 
 *  rules against duplication values in a row, column, or outlined 3 x 3 square. 
 * Command Parameters:
 *  ./sudokuChecker < textFile
 * Input:
 *  A line of input containing a single command character L, C, or E.
 *  Lines of input containing sudoku puzzle values 0-9, zero representing an
 *  an empty cell.
 *  e.g.    L 
 *          002405800
 *          041800020
 *          600070039
 *          200030096
 *          009607100
 *          170050003
 *          960080001
 *          020009560
 *          008306900
 * Results:
 *  Option L:
 *      Prints the possible values and their position within the sudoku puzzle. 
 *  Option C:
 *      C-Checks a sudoku puzzle solution and prints "incorrect/correct."
 * Returns:
 *  0 exit normally. 
 ******************************************************************************/

// Header 
#include <stdio.h>
#include <stdlib.h>
#include "sudokuChecker.h"

// Main Program
int main(int argc, char *argv[])
{
    int count[MAXSIZE] = {0};
    char userChoice; 
    int sudoku[MAXROWS][MAXCOLUMNS] = {0}; // 2D Sudoku puzzle
    int rowIndex; 
    int columnIndex;
    int countIndex; 

    // Command argument is NOT expected
    if (argc > 1)
    {
        exitError("Usage: sudokuChecker < inputFile.txt");
    }
    // Prompt user
    actionMenu();

    // Get users' choice 
    scanf("%c" , &userChoice);
    printf("%c\n\n", userChoice);

    // Process option L
    if (userChoice == 'l' || userChoice == 'L') {
        // Prompt user for Sudoku values
        printf("%s\n", "Enter Sudoku values (i.e. 0 thru 9.)");
        // Read user values into sudoku matrix
        getSudokuValues(sudoku);
        printf("Possible Solutions:\n");
        // Loop thru rows
        for (rowIndex = 0; rowIndex < MAXROWS; rowIndex++) {
            // Loop thru columns
            for (columnIndex = 0; columnIndex < MAXCOLUMNS; columnIndex++) {
                // Detect empty cells
                if (sudoku[rowIndex][columnIndex] == 0) {
                // Print location of empty cells
                    printf("[%d][%d]: ", rowIndex, columnIndex);
                    // Search for possible values
                    searchRows(sudoku, count, rowIndex);
                    searchColumns(sudoku, count, columnIndex);
                    searchRegions(sudoku, count, rowIndex, columnIndex);
                    // Print possible values
                    printValues(count);
                    printf("\n");
                }
            }
        }
    }

    /*
     * If user chooses option C, then read puzzle values, check solution,
     * and print whether the solution is incorrect/correct.
     */
    if (userChoice == 'c' || userChoice == 'C') {
        getSudokuValues(sudoku);
        if(checkRows(sudoku) != 1 || 
                checkColumns(sudoku) != 1 || 
                checkRegions(sudoku) != 1)
        {
            printf("Incorrect solution.\n");
        } else
        {
            printf("Correct solution.\n");
        }
    }

    // exit normally
    return 0;
} // end of main

/****************************** getSudokuValues *********************************
 *******************************************************************************/
void getSudokuValues(int sudoku[][MAXCOLUMNS])
{
    int rowIndex;
    int columnIndex;
    int userInput;
    char trash[10];

    // Read values into Sudoku puzzle array
    for (rowIndex = 0; rowIndex < MAXROWS; rowIndex++) {
        for (columnIndex = 0; columnIndex < MAXCOLUMNS; columnIndex++) {
            // Continue loop as long as invalid puzzle values are entered
            int continueLoop = 1; // boolean flag
            while (continueLoop) {
                // get puzzle value
                if (1 == scanf("%d", &userInput)) {
                    // test for valid values: 0 thru 9
                    if (userInput >= 0 && userInput <= 9) {
                    continueLoop = 0; // leave while loop
                    } else { // continue while loop
                        printf("Invalid value: %d.\n", userInput);
                        printf("Enter values between 0 and 9.\n");
                    }
                } else { // continue while loop
                    scanf("%s", trash);
                    printf("Invalid value: %s.\n", trash);
                    printf("Enter values between 0 and 9.\n");
                }
            }
            // Valid value accepted
            sudoku[rowIndex][columnIndex] = userInput;
        }
    }
}

/****************************** printValues *************************************
 *******************************************************************************/
void printValues(int count[])
{
    int rowIndex;
    /*
     * If element contains zero, then
     * print position as possible value.
     */
    for (rowIndex = 0; rowIndex < 10; rowIndex++) {
        if (count[rowIndex] == 0) {
            printf("%d ", rowIndex);
        }
        // Reset values 
        count[rowIndex] = 0;
    }
}

/****************************** searchRows **************************************
 *******************************************************************************/
void searchRows(int sudoku[][MAXCOLUMNS], int count[], int rowIndex)
{
    int columnIndex;
    // Loops thru rows of the sudoku puzzle.
    for (columnIndex = 0; columnIndex < MAXROWS; columnIndex++) {
        // Track the numbers found within the puzzle by incrementing the
        // coresponding index within the count array
        count[sudoku[rowIndex][columnIndex]]++;
    }
}

/****************************** searchColumns ***********************************
 *******************************************************************************/
void searchColumns(int sudoku[][MAXCOLUMNS], int count[], int columnIndex)
{
    int rowIndex;
    // Loops thru columns of the sudoku puzzle.
    for (rowIndex = 0; rowIndex < MAXCOLUMNS; rowIndex++) {
        // Track the numbers found within the puzzle by incrementing the
        // coresponding index within the count array
        count[sudoku[rowIndex][columnIndex]]++;
    }
}

/****************************** searchRegions ***********************************
 * Purpose:
 *     Searches each 3x3 sub-region of the sudoku puzzle.
 * Parameters:
 * Notes:
 *******************************************************************************/
void searchRegions(int sudoku[][MAXCOLUMNS], int count[], int rowIndex,
        int columnIndex)
{
    int countIndex;
    int regionRowIndex;
    int regionColIndex;
 
    // Loop thru 3x3 sub-regions
    // Loops thru rows of 3x3 sub-region
    for(regionRowIndex = (rowIndex / 3) * 3; 
            regionRowIndex < (rowIndex / 3) * 3 + 3;
            regionRowIndex++) {
        // Loops thru columns of 3x3 sub-regions
        for (regionColIndex = (columnIndex / 3) * 3; 
                regionColIndex < (columnIndex / 3) * 3 + 3; 
                regionColIndex++) {
            // Loops thru count array 
            for (countIndex = 1; countIndex < MAXSIZE-1; countIndex++) {
                // Track the numbers found within the puzzle by incrementing the
                // coresponding index within the count array
                count[sudoku[regionRowIndex][regionColIndex]]++;
            }
        }
    }
}

/****************************** actionMenu **************************************
 * void actionMenu(); 
 * Purpose:
 *   Display menu options to user.
 *******************************************************************************/
void actionMenu() 
{
    printf("\n%s\n","Enter one of the following actions. ");
    printf("%s\n", "L-list possible values for empty cells in a Sudoku puzzle");
    printf("%s\n", "C-check a Sudoku solution");
    printf("%s\n", "E-exit");
    printf("\n%s", "Enter choice: ");
}
/********************************* checkRows ************************************
 * int checkRows(int sudoku[][MAXCOLUMNS]);
 * Purpose:
 *     Checks each row of the sudoku puzzle to insure that there are
 *     no duplicate or missing values.
 * Parameters:
 *     I    sudoku[][MAXCOLUMNS]    sudoku puzzle
 * Returns
 *     0    found error
 *     1    no errors found
 * *****************************************************************************/
int checkRows(int sudoku[][MAXCOLUMNS])
{
    int rowIndex;
    int countIndex;
    int columnIndex;
    int count[MAXSIZE] = {0};

    // Loop thru rows
    for (rowIndex = 0; rowIndex < MAXROWS; rowIndex++)
    {
        // Loop thru columns
        for (columnIndex = 0; columnIndex < MAXCOLUMNS; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
        // Loop thru count array
        for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
        {
            // Verify values 1 thru 9 are present & not duplicated
            // (i.e. not zero and not greater than 1
            if (count[countIndex] != 1)
            {
                return 0; // found error
            }
            // Reset count values to zero as we loop thru values
            count[countIndex] = 0;
        } // end of for-loop thru count array
    } // end of for-loop thru rows

    return 1; // no errors found
}

/******************************* checkColumns ***********************************
 * int checkColumns(int sudoku[][MAXCOLUMNS]);
 * Purpose:
 *     Checks each column of the sudoku puzzle to insure that there are
 *     no duplicate or missing values.
 * Parameters:
 *     I    sudoku[][MAXCOLUMNS]    sudoku puzzle
 * Returns
 *     0    found error
 *     1    no errors found
 * *****************************************************************************/
int checkColumns(int sudoku[][MAXCOLUMNS])
{
    int rowIndex;
    int countIndex;
    int columnIndex;
    int count[MAXSIZE] = {0};

    // Loop thru columns 
    for (columnIndex = 0; columnIndex < MAXCOLUMNS; columnIndex++)
    {
        // Loop thru rows 
        for (rowIndex = 0; rowIndex < MAXROWS; rowIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
        // Loop thru count array
        for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
        {
            // Verify values 1 thru 9 are present & not duplicated
            // (i.e. not zero and not greater than 1
            if (count[countIndex] != 1)
            {
                return 0; // found error
            }
            // Reset count values to zero as we loop thru values
            count[countIndex] = 0;
        } // end of for-loop thru count array
    } // end of for-loop thru columns 

    return 1; // no errors found
}

/******************************* checkRegions ***********************************
 * int checkRegions(int sudoku[][MAXCOLUMNS])
 * Purpose:
 *     Checks each 3x3 sub region of the sudoku puzzle to insure that there are
 *     no duplicate or missing values.
 * Parameters:
 *     I    sudoku[][MAXCOLUMNS]    sudoku puzzle
 * Returns
 *     0    found error
 *     1    no errors found
 * *****************************************************************************/
int checkRegions(int sudoku[][MAXCOLUMNS])
{
    int rowIndex;
    int countIndex;
    int columnIndex;
    int count[MAXSIZE] = {0};

    // Loop thru rows, of top left 3x3 region
    for (rowIndex = 0; rowIndex < 3; rowIndex++)
    {
        // Loop thru columns, of top left 3x3 region
        for (columnIndex = 0; columnIndex < 3; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru top left 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in top left 3x3 region

    // Loop thru rows, of top center 3x3 region
    for (rowIndex = 0; rowIndex < 3; rowIndex++)
    {
        // Loop thru columns, of top center 3x3 region
        for (columnIndex = 3; columnIndex < 6; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru top center 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in top center 3x3 region

    // Loop thru rows, of top right 3x3 region
    for (rowIndex = 0; rowIndex < 3; rowIndex++)
    {
        // Loop thru columns, of top right 3x3 region
        for (columnIndex = 6; columnIndex < MAXCOLUMNS; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru top right 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in top right 3x3 region

    // Loop thru rows, of middle left 3x3 region
    for (rowIndex = 3; rowIndex < 6; rowIndex++)
    {
        // Loop thru columns, of middle left 3x3 region
        for (columnIndex = 0; columnIndex < 3; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru middle left 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in middle left 3x3 region

    // Loop thru rows, of mid-center 3x3 region
    for (rowIndex = 3; rowIndex < 6; rowIndex++)
    {
        // Loop thru columns, of mid-center 3x3 region
        for (columnIndex = 3; columnIndex < 6; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru mid center 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in mid-right 3x3 region
    
    // Loop thru rows, of mid-right 3x3 region
    for (rowIndex = 3; rowIndex < 6; rowIndex++)
    {
        // Loop thru columns, of mid-right 3x3 region
        for (columnIndex = 6; columnIndex < MAXCOLUMNS; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru mid-right 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in mid-right 3x3 region

    // Loop thru rows, of bottom left 3x3 region
    for (rowIndex = 6; rowIndex < MAXROWS; rowIndex++)
    {
        // Loop thru columns, of bottom left 3x3 region
        for (columnIndex = 0; columnIndex < 3; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru bottom left 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in bottom left 3x3 region

    // Loop thru rows, of bottom center 3x3 region
    for (rowIndex = 6; rowIndex < MAXROWS; rowIndex++)
    {
        // Loop thru columns, of bottom center 3x3 region
        for (columnIndex = 3; columnIndex < 6; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru bottom center 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in bottom center 3x3 region

    // Loop thru rows, of bottom right 3x3 region
    for (rowIndex = 6; rowIndex < MAXROWS; rowIndex++)
    {
        // Loop thru columns, of bottom right 3x3 region
        for (columnIndex = 6; columnIndex < MAXCOLUMNS; columnIndex++)
        {
            count[sudoku[rowIndex][columnIndex]]++;
        }
    } // end of loop thru bottom right 3x3 region

    // Loop thru count array
    for (countIndex = 1; countIndex < MAXSIZE - 1; countIndex++)
    {
        // Verify values 1 thru 9 are present & not duplicated
        // (i.e. not zero and not greater than 1
        if (count[countIndex] != 1)
        {
            return 0; // found error
        }
        // Reset count values to zero as we loop thru values
        count[countIndex] = 0;
    } // end of for-loop thru count array
    // no errors found in bottom right 3x3 region

    return 1; // no errors found
}

/******************** exitError *************************************************
    void exitError(char *message)
Purpose:
    Prints an error message. Exits with ERROR_PROCESSING.
Parameters:
    I char Message              error message to print
Notes:
    This routine causes the program to exit.
********************************************************************************/
void exitError(char *message)
{
    printf("%s\n", message);
    exit(ERROR_PROCESSING);
}
