//Leah Kazenmayer
#include <iostream>
#include <vector>
#include<string>
#include "colormod.h"
using namespace std;

void check(vector< vector<char> >&, vector< vector<bool> >&, int c, char *[]);

void forwardCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void backwardCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void downwardCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void upwardCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void diagonalRightCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void diagonalLeftCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void diagonalUpRightCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);
void diagonalUpLeftCheck(vector< vector<char> >&, vector< vector<bool> >&, int, int, string);

void printHighlightedMatrix(vector< vector<char> >&, vector< vector<bool> >&);

int main(int argc, char *argv[]) {
  int numRows;
  int numColumns;

  cin >> numRows; //Input the num of rows
  cin >> numColumns; //Input the num of columns

  vector< vector<char> > matrix( numRows , vector<char> (numColumns, 0)); //The two-d vector that holds the matrix

  //Fills in the matrix with the word search
  for(int i = 0; i<numRows; i++) {
    for (int j = 0; j<numColumns; j++) {
      cin >> matrix[i][j];
    }
  }

  vector< vector<bool> > matrixTruthValues( matrix.size() , vector<bool> (matrix[0].size(), false)); //The two-d vector that highlights found words

  check(matrix, matrixTruthValues, argc, argv); //Checks for all the words in all directions

  printHighlightedMatrix(matrix, matrixTruthValues); //Prints out the matrix highlighted

  return 0;
}

void check(vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int argc, char *argv[]) {
  for(int i = 0; i<argc; i++) { //For every word in the argument char array...
    string currentElement = argv[i]; //assign it as a string called "current element".
    //Then within the subsequent two for loops, it checks every index in
    //the two-d vector for each word in the char array in all the directions
    for(int j = 0; j<matrix.size(); j++) { //Rows
      for(int k = 0; k<matrix[0].size(); k++) { //Columns

        //Finds words from...
        forwardCheck(matrix, matrixTruthValues, j, k, currentElement); //left to right
        backwardCheck(matrix, matrixTruthValues, j, k, currentElement); //right to left 
        downwardCheck(matrix, matrixTruthValues, j, k, currentElement); //top to bottom
        upwardCheck(matrix, matrixTruthValues, j, k, currentElement); //bottom to top
        diagonalRightCheck(matrix, matrixTruthValues, j, k, currentElement); //diagonal from top left to bottom right
        diagonalLeftCheck(matrix, matrixTruthValues, j, k, currentElement); //diagonal from top right to bottom left
        diagonalUpRightCheck(matrix, matrixTruthValues, j, k, currentElement); //diagonal from bottom left to upper right
        diagonalUpLeftCheck(matrix, matrixTruthValues, j, k, currentElement); //diagonal from bottom right to upper left
      }
    }
  }
}

void printHighlightedMatrix(vector< vector<char> >& matrix, vector< vector<bool> >& matrixTruthValues) {
  Color::Setting red(Color::FG_RED); //Sets 'red' to the color red
  Color::Setting def(Color::FG_DEFAULT); //Sets 'def' to the normal terminal color 

  for (int i = 0; i<matrixTruthValues.size(); i++) { //Rows
    for (int j = 0; j<matrixTruthValues[0].size(); j++) { //Columns
      if (matrixTruthValues[i][j] == false) { //If the element in the matrixTruthValues matrix is false (aka not highlighted)...
        cout << matrix[i][j] << " "; //Print it in the default color
      } else {
        cout << red << matrix[i][j] << def << " "; //Otherwise print the element red
      }
    }
    cout << endl;
  }
}


/*
  Each individual check first calculates whether the word goes out of bounds in the matrix.
  If it stays in the dimensions of the matrix, then the word gets checked at that index in
  that specific direction.
  Starting at that index in the word search, the for loop adds characters to "wordFound"
  based on the length of currentElement in the direction stated by the function. If the
  wordFound matches the currentElement (from the char array), then the word gets highlighted
  in matrixTruthValues. matrixTruthValues is a duplicate of the word search, but only holds
  boolean values: true for highlighted, false for not highlighted. The matrixTruthValues
  gets sent through each method, updating the highlights as it goes until it's eventually printed
  after the whole matrix is searched.
*/
void forwardCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + k > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = k;

    for(int m = 0; m<currentElement.length(); m++) {
      wordFound += matrix[j][l];
      l++;
    }

    l = k;

    if(currentElement == wordFound) {
      for (int n = 0; n<currentElement.length(); n++) {
        matrixTruthValues[j][l] = true;
        l++;
      }
    }
  }
}

void backwardCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if ((currentElement.length()) + (matrix[0].size() - k - 1) > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = k;

    for(int m = 0; m<currentElement.length(); m++) {
      wordFound += matrix[j][l];
      l--;
    }

    l = k;

    if(currentElement == wordFound) {
      for (int n = 0; n<currentElement.length(); n++) {
        matrixTruthValues[j][l] = true;
        l--;
      }
    }
  }
}

void downwardCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + j > matrix.size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;

    for(int m = 0; m<currentElement.length(); m++) {
      wordFound += matrix[l][k];
      l++;
    }

    l = j;

    if(currentElement == wordFound) {
      for (int n = 0; n<currentElement.length(); n++) {
        matrixTruthValues[l][k] = true;
        l++;
      }
    }
  }
}

void upwardCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + (matrix.size() - j - 1) > matrix.size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;

    for(int m = 0; m<currentElement.length(); m++) {
      wordFound += matrix[l][k];
      l--;
    }

    l = j;

    if(currentElement == wordFound) {
      for (int n = 0; n<currentElement.length(); n++) {
        matrixTruthValues[l][k] = true;
        l--;
      }
    }
  }
}

void diagonalRightCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + j > matrix.size() || currentElement.length() + k > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;
    int m = k;

    for(int n = 0; n<currentElement.length(); n++) {
      wordFound += matrix[l][m];
      l++;
      m++;
    }

    l = j;
    m = k;

    if(currentElement == wordFound) {
      for (int o = 0; o<currentElement.length(); o++) {
        matrixTruthValues[l][m] = true;
        l++;
        m++;
      }
    }
  }
}

void diagonalLeftCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + j > matrix.size() || currentElement.length() + (matrix[0].size() - k - 1) > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;
    int m = k;

    for(int n = 0; n<currentElement.length(); n++) {
      wordFound += matrix[l][m];
      l++;
      m--;
    }

    l = j;
    m = k;

    if(currentElement == wordFound) {
      for (int o = 0; o<currentElement.length(); o++) {
        matrixTruthValues[l][m] = true;
        l++;
        m--;
      }
    }
  }
}

void diagonalUpRightCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + (matrix.size() - j - 1) > matrix.size() || currentElement.length() + k > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;
    int m = k;

    for(int n = 0; n<currentElement.length(); n++) {
      wordFound += matrix[l][m];
      l--;
      m++;
    }

    l = j;
    m = k;

    if(currentElement == wordFound) {
      for (int o = 0; o<currentElement.length(); o++) {
        matrixTruthValues[l][m] = true;
        l--;
        m++;
      }
    }
  }
}

void diagonalUpLeftCheck (vector< vector<char> > &matrix, vector< vector<bool> >& matrixTruthValues, int j, int k, string currentElement) {
  if (currentElement.length() + (matrix.size() - j - 1) > matrix.size() || (currentElement.length()) + (matrix[0].size() - k - 1) > matrix[0].size()) {
    return;
  } else {
    string wordFound = "";
    int l = j;
    int m = k;

    for(int n = 0; n<currentElement.length(); n++) {
      wordFound += matrix[l][m];
      l--;
      m--;
    }

    l = j;
    m = k;

    if(currentElement == wordFound) {
      for (int o = 0; o<currentElement.length(); o++) {
        matrixTruthValues[l][m] = true;
        l--;
        m--;
      }
    }
  }
}
