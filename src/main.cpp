// Shrey Deogade & Aadesh Jay Harikumar
// Period 4
// Midterm Project

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
using namespace std;

// Size of the chessBoard
const int SIZE = 8;

// Enum to enumerate all the possible states of a Square (either taken up by a
// Queen, or Empty)
enum SquareStatus {
  Empty,
  Queen,
};

// The function prototypes
void solveEightQueens(SquareStatus[SIZE][SIZE]);
void initializeEmptyMatrix(SquareStatus[SIZE][SIZE]);
void printChessboard(SquareStatus[SIZE][SIZE]);

bool checkRow(SquareStatus[SIZE][SIZE], int);
bool checkColumn(SquareStatus[SIZE][SIZE], int);
bool checkDiagonals(SquareStatus[SIZE][SIZE], int, int);

bool columnTraversal(SquareStatus[SIZE][SIZE], int);

int main() {
  // Seed srand at time(0) for a pseudorandom number generator
  srand(time(0));

  // Initialize an empty chessBoard matrix
  SquareStatus chessBoard[SIZE][SIZE] = {};

  // Solve Eight Queens using the previous chessBoard matrix
  solveEightQueens(chessBoard);

  // Print the final result
  printChessboard(chessBoard);
  return 0;
}

void printChessboard(SquareStatus chessBoard[SIZE][SIZE]) {
  // The ANSI escape codes for colors
  string WHITE = "\033[0;107m";
  string GRAY = "\033[0;42m";

  string QUEEN_ON_WHITE = "\033[1;40;107m";
  string QUEEN_ON_GRAY = "\033[1;40;42m";
  string RESET = "\033[0m";

  // Check if should print white; else gray
  bool colorWhite = false;

  // Iterate through every element in the matrix
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Make a temporary square variable to house the current chessBoard piece
      SquareStatus square = chessBoard[i][j];

      // Choose which color to print
      string currentColor = (colorWhite) ? WHITE : GRAY;
      string GOLD = (colorWhite) ? QUEEN_ON_WHITE : QUEEN_ON_GRAY;

      // Make the symbol either a space (" ") or a Q ("Q") depending if the
      // square is a queen or not
      string symbol = (square == Queen) ? GOLD + "Q " + RESET : "  ";

      // Construct and cout a string that concatenates all the previous stuff
      cout << currentColor << " " << symbol << currentColor << "" << RESET;

      // Make white its inverse to alternate colors between squares
      colorWhite = !colorWhite;
    }

    // Make white its inverse to alternate colors between rows
    colorWhite = !colorWhite;
    // Newline
    cout << endl;
  }
}

void solveEightQueens(SquareStatus chessBoard[SIZE][SIZE]) {
  // The main interface to solveEightQueens on a given chessBoard.

  do {
    // Make sure the chessBoard is empty
    initializeEmptyMatrix(chessBoard);

    // Start off at a random position
    int startingPosition = rand() % 8;
    chessBoard[startingPosition][0] = Queen;
    // And solve until the problem is solved
  } while (!columnTraversal(chessBoard, 1));
}

void initializeEmptyMatrix(SquareStatus chessBoard[SIZE][SIZE]) {
  // Initialize an empty matrix by iterating through every element and setting
  // it to 0
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      chessBoard[i][j] = Empty;
    }
  }
}

bool columnTraversal(SquareStatus chessBoard[SIZE][SIZE], int column) {
  // Recursively traverse through the columns to solve the board - else false is
  // handled by the
  //   solveEightQueens function

  // Base case - if the column is greater than or equal than the size, just
  // return true
  if (column >= SIZE)
    return true;

  // Iterate through every element of the column
  for (int i = 0; i < SIZE; i++) {
    // Place a queen at the current (i, column) and later remove if it doesn't work
    chessBoard[i][column] = Queen;

    // Store a bool to see if all the rows, columns, and diagonals' requirements
    // are fulfilled
    bool requirementsFulfilled = checkRow(chessBoard, i) &&
                                 checkColumn(chessBoard, column) &&
                                 checkDiagonals(chessBoard, i, column);

    // Execute only if the previous bool is true and if the recursive call for
    // the next column is also true
    if (requirementsFulfilled && columnTraversal(chessBoard, column + 1)) {
      return true;
    }

    // If the current queen doesn't work, make it Empty (failed so many times
    // because I forgot to do this)
    chessBoard[i][column] = Empty;
  }
  // If no queens can be placed in the column, return false to backtrack
  return false;
}

bool checkRow(SquareStatus chessBoard[SIZE][SIZE], int row) {
  // Check if a row has any queens, and if the number of queens is not 1,
  // return false

  // Accumulator to keep track of how many queens there are in a row
  int sum = 0;

  // Iterate through all elements in the row
  for (int i = 0; i < SIZE; i++) {
    // Increment sum if a Queen is found
    if (chessBoard[row][i] == Queen)
      sum++;
  }

  // There should be only 1 queen per row, so if it doesn't, it's false
  // because it doesn't fulfill the "1 queen per row" requirement
  return sum == 1;
}

bool checkColumn(SquareStatus chessBoard[SIZE][SIZE], int column) {
  // Check if a column has any queens, and if the number of queens is not 1,
  // return false

  // Acummulator to keep track of how many queens there are in a column
  int sum = 0;

  // Iterate through all elements in the column
  for (int i = 0; i < SIZE; i++) {
    // Increment sum if a Queen is found
    if (chessBoard[i][column] == Queen)
      sum++;
  }

  // There should be only 1 queen per column, so if it doesn't, it's false
  // because it doesn't fulfill the "1 queen per column" requirement
  return sum == 1;
}

bool checkDiagonals(SquareStatus chessBoard[SIZE][SIZE], int row, int column) {
  // There are 2 types of diagonals:
  // * the ones that go from top-left to bottom-right
  // * the ones that go from bottom-left to top-right

  // Diagonal type 1:
  // Iterate through each element and see if there are any queens on a diagonal
  // twice
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Store the current square to make it easier to access
      SquareStatus square = chessBoard[i][j];

      // i == row and j == column checks to see if you accidently go over a
      // diagonal where a queen is already placed
      if (i == row && j == column)
        continue;

      // If 2 points are diagonally aligned, the same variables should subtract
      // and get the same number
      // Based on slope formula and y=mx+b
      bool isDiagonal = i - row == j - column;

      // See if the current square is a queen and is a diagonal. If it is, then
      // return false because it doesn't fulfill the "1 queen per diagonal"
      // requirement Uses previously assigned isDiagonal variable

      if (square == Queen && isDiagonal) {
        return false;
      }
    }
  }

  // Diagonal type 2 (mostly the same thing as the first diagonal):
  // Iterate through each element and see if there are any queens on a diagonal
  // twice
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Store the current square to make it easier to access
      SquareStatus square = chessBoard[i][j];

      // i == row and j == column checks to see if you accidently go over a
      // diagonal where a queen is already placed
      if (i == row && j == column)
        continue;

      // If 2 points are diagonally aligned, the same variables should subtract
      // and get the same number, except you switch the numbers in one of the
      // things because it's the reverse of the 1st type of diagonal
      // Based on slope formula and y = mx+b
      bool isDiagonal = i - row == column - j;

      // See if the current square is a queen and is a diagonal. If it is, then
      // return false because it doesn't fulfill the "1 queen per diagonal"
      // requirement
      //
      // Uses previously assigned isDiagonal variable
      if (square == Queen && isDiagonal) {
        return false;
      }
    }
  }

  // Return true if there isn't another queen in the same diagonal as the
  // original one (row, column)
  return true;
}
