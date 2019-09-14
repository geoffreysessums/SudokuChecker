# SudokuChecker

Geoffrey Sessums  
CS 2123 Data Structures - Fall 2016  
Language: C  

## Description

SudokuChecker verifies a proposed Sudoku solution from a text file following the Sudoku rules against duplicating values in a row, column, or outlined 3 x 3 square.

## What I Learned

* How to process command line arguments
* How to use header files
* How to process user input
* How to redirect input/output
* How to use 2D arrays
* How to handle simple errors

## Installation

Clone the repository wherever you like (e.g. `~/Projects/SudokuChecker`):  
`git clone https://github.com/gsessums/SudokuChecker.git`

## Usage

Use the included Makefile:  
`make`

To execute:  
`./sudokuChecker`

Alternatively:  

You may use the included sample files:  
`./sudokuChecker < sudoku-solution1-false-to-be-checked.txt`

## Testing

Several files are included for testing the program:  

* sudoku-puzzle1.txt
    * Input text file containing a sample sudoku puzzle.
* sudoku-solution1-false-to-be-checked.txt
    * Input text file containing a WRONG proposed solution.
* sudoku-solution1-true-to-be-checked.txt
    * Input text file containing a CORRECT proposed solution.

## Credits

Author: Geoffrey Sessums

## License

MIT License

Copyright (c) 2017 Geoffrey Sessums

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
