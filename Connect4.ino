

#include <LedControl.h>

/*
 * Simon Taylor
 * the date
 * this is a project
 */

// define the segments for Seven Segment Display
#define segA 1
#define segB 2
#define segC 3
#define segD 4
#define segE 5
#define segF 6
#define segG 7

// define the displays for Seven Segment Display
#define display1 22
#define display2 23
#define display3 24
#define display4 25

// define the player LED indicators
#define player1LED 28
#define player2LED 29

// define the matrix pins
#define matrixCLK 30
#define matrixCS 31
#define matrixDIN 32
#define matrixNumOfDevices 1

// define the joystick pins
#define joystickSEL 12
#define joystickHORX A1
#define joystickVERT A2

// define the connect4 stuff
int board[7][8]; // 7 rows, 8 columns
int player1Score = 0;
int player2Score = 0;
int playerTurn = 1;  // either 1 or 2
int delayTime = 500; // in ms
bool gameOver = false;

// define jostick shit
int joystickY;
int joystickX;

bool joystickUP = false;
bool joystickDOWN = false;
bool joystickLEFT = false;
bool joystickRIGHT = false;
bool joystickSELECT;

// define the object being used
LedControl matrix = LedControl(matrixDIN, matrixCLK, matrixCS, matrixNumOfDevices);

/*
 *  displaying methods
 */
void segDisplay(int display, int seg)
{
  // display numbers on a seven segment display
  // takes an int that is which display is being outputted and the num to output
  // only works for me in this class

  switch (display)
  {
  case 1:
    digitalWrite(display1, HIGH);
    break;
  case 2:
    digitalWrite(display2, HIGH);
    break;
  case 3:
    digitalWrite(display3, HIGH);
    break;
  case 4:
    digitalWrite(display4, HIGH);
    break;
  }

  switch (seg)
  {
  case 0:
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    break;
  case 1:
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    break;
  case 2:
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segD, LOW);
    break;
  case 3:
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    break;
  case 4:
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    break;
  case 5:
    digitalWrite(segA, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    break;
  case 6:
    digitalWrite(segA, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segG, LOW);
    break;
  case 7:
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    break;
  case 8:
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    break;
  case 9:
    digitalWrite(segA, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    break;
  }
}

void clearSevSeg()
{
  for (int i = segA; i <= segG; i++)
  {
    digitalWrite(i, HIGH);
  }
  for (int i = display1; i <= display4; i++)
  {
    digitalWrite(i, LOW);
  }
}

void displayPlayer1()
{
  matrix.clearDisplay(0);
  digitalWrite(player2LED, LOW);
  clearSevSeg();

  for (int row = 0; row < sizeof(board) / sizeof(int); row++)
  {
    for (int col = 0; col < sizeof(board[0]) / sizeof(int); col++)
    {
      if (board[row][col] == 1)
      {
        matrix.setLed(0, row, col, true);
      }
    }
  }

  digitalWrite(player1LED, HIGH);

  segDisplay(1, player1Score);
}

void displayPlayer2()
{
  matrix.clearDisplay(0);
  digitalWrite(player1LED, LOW);
  clearSevSeg();

  for (int row = 0; row < sizeof(board) / sizeof(int); row++)
  {
    for (int col = 0; col < sizeof(board[0]) / sizeof(int); col++)
    {
      if (board[row][col] == 2)
      {
        matrix.setLed(0, row, col, true);
      }
    }
  }

  digitalWrite(player2LED, HIGH);

  segDisplay(4, player2Score);
}

void winDisplay()
{
  for (int i = 0; i < 5; i++)
  {
    for (int row = 0; row < sizeof(board) / sizeof(int); row++)
    {
      for (int col = 0; col < sizeof(board[0]) / sizeof(int); col++)
      {
        matrix.setLed(0, row, col, true);
      }
      delay(20);
    }
    for (int row = 0; row < sizeof(board) / sizeof(int); row++)
    {
      for (int col = 0; col < sizeof(board[0]) / sizeof(int); col++)
      {
        matrix.setLed(0, row, col, false);
      }
      delay(20);
    }
  }
}

/*
 *  other methods that are actaully helpful
 */
void setJoystickValues()
{
  joystickLEFT = analogRead(joystickHORX) > 823;
  joystickRIGHT = analogRead(joystickHORX) < 200;
  joystickUP = analogRead(joystickVERT) > 823;
  joystickDOWN = analogRead(joystickVERT) < 200;

  joystickSELECT = digitalRead(joystickSEL) == LOW;
}

int pickCol(int player)
{
  //  setJoystickValues();

  bool selectedCol = false;
  int col = 0;

  while (!selectedCol)
  {
    /* code */
    setJoystickValues();
    matrix.setLed(0, 7, col, true);
    if (joystickSELECT)
    {
      drop(col, player);
      selectedCol = true;

      delay(250);
      return col;
    }

    if (joystickLEFT)
    {
      matrix.setLed(0, 7, col, false);
      col--;
      delay(250);
    }
    if (joystickRIGHT)
    {
      matrix.setLed(0, 7, col, false);
      col++;
      delay(250);
    }
  }
}

/*
 *  connect4 helping methods
 */

void drop(int col, int player)
{
  for (int row = 0; row < sizeof(board) / sizeof(int); row++)
  {
    if (board[row][col] == 0)
    {
      board[row][col] = player;
      break;
    }
  }
}

bool checkCol(int col)
{
  for (int row = 0; row < sizeof(board) / sizeof(int); row++)
  {
    if (board[row][col] != 0)
    {
      return false;
    }
  }
  return true;
}

void addWin(int player)
{
  switch (player)
  {
  case 1:
    player1Score++;
    break;
  case 2:
    player2Score++;
    break;
  }
}

void createBoard()
{ // initalize array to 0
  for (int i = 0; i < sizeof(board) / sizeof(int); i++)
  {
    for (int j = 0; j < sizeof(board[0]) / sizeof(int); j++)
    {
      board[i][j] = 0;
    }
  }
}

void clearBoard()
{ // initalize array to 0
  for (int i = 0; i < sizeof(board) / sizeof(int); i++)
  {
    for (int j = 0; j < sizeof(board[0]) / sizeof(int); j++)
    {
      board[i][j] = 0;
    }
  }
}

int checkForWin()
{
  for (int i = 0; i < sizeof(board); i++)
  {
    for (int j = 0; j < sizeof(board[0]); j++)
    {
      // check diagonals
      if (checkDiagonalUpAndRight(i, j) == 1)
      {
        return 1;
      }
      if (checkDiagonalUpAndRight(i, j) == 2)
      {
        return 2;
      }
      if (checkDiagonalDownAndRight(i, j) == 1)
      {
        return 1;
      }
      if (checkDiagonalDownAndRight(i, j) == 2)
      {
        return 2;
      }

      // check rows
      if (checkRow(i, j) == 1)
      {
        return 1;
      }
      if (checkRow(i, j) == 2)
      {
        return 2;
      }

      // check columns
      if (checkColumn(i, j) == 1)
      {
        return 1;
      }
      if (checkColumn(i, j) == 2)
      {
        return 2;
      }
    }
  }
  return 0;
}

int checkColumn(int row, int col)
{
  bool rowOutOfBounds = row > sizeof(board)/sizeof(int) - 4;
  if (rowOutOfBounds)
  {
    return 0;
  }

  int x = 0;
  int o = 0;

  for (int k = 0; k < 4; k++)
  { // cycle through column to check for 4 in a row
    if (board[row + k][col] == 1)
    {
      x++;
      o = 0;
    }
    else if (board[row + k][col] == 2)
    {
      x = 0;
      o++;
    }
    else
    {
      x = 0;
      o = 0;
    }
  }

  // check if either X or O has 4 in a row;
  if (x == 4)
  {
    return 1;
  }
  else if (o == 4)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

int checkRow(int row, int col)
{
  // end if out of bounds
  bool colOutOfBounds = (col > sizeof(board[0])/sizeof(int) - 4) || col < 0;
  if (colOutOfBounds)
  {
    return 0;
  }

  int x = 0;
  int o = 0;

  for (int k = 0; k < 4; k++)
  { // cycle through row to check for 4 in a row

    if (board[row][col + k] == 1)
    {
      x++;
      o = 0;
    }
    else if (board[row][col + k] == 2)
    {
      x = 0;
      o++;
    }
    else
    {
      x = 0;
      o = 0;
    }
  }

  // check if either X or O has 4 in a row;
  if (x == 4)
  {
    return 1;
  }
  else if (o == 4)
  {
    return 2;
  }
  else
  {
    return 0; // return 0 if nothing is matches
  }
}

int checkDiagonalUpAndRight(int row, int col)
{
  // end if out of bounds
  bool rowOutOfBounds = (row > sizeof(board) / sizeof(int) - 4) || row < 0;
  bool colOutOfBounds = (col > sizeof(board) / sizeof(int) - 4) || col < 0;
  if (rowOutOfBounds || colOutOfBounds)
  {
    return 0;
  }

  int x = 0;
  int o = 0;

  for (int k = 0; k < 4; k++)
  { // cycle through checking columns/rows
    if (board[row + k][col + k] == 1)
    {
      x++;
      o = 0;
    }
    else if (board[row + k][col + k] == 2)
    {
      x = 0;
      o++;
    }
    else if (board[row + k][col + k] == 0)
    {
      x = 0;
      o = 0;
    }
  }

  if (x == 4)
  {
    return 1;
  }
  else if (o == 4)
  {
    return 2;
  }

  return 0;
}

int checkDiagonalDownAndRight(int row, int col)
{
  // end if out of bounds
  bool rowOutOfBounds = row < 3 || row < 0;
  bool colOutOfBounds = (col > sizeof(board[0]) / sizeof(int) - 4) || col < 0;
  if (rowOutOfBounds || colOutOfBounds)
  {
    return 0;
  }

  int x = 0;
  int o = 0;

  for (int k = 0; k < 4; k++)
  { // cycle through checking columns/rows
    if (board[row - k][col + k] == 1)
    {
      x++;
      o = 0;
    }
    else if (board[row - k][col + k] == 2)
    {
      x = 0;
      o++;
    }
    else if (board[row - k][col + k] == 0)
    {
      x = 0;
      o = 0;
    }
  }

  if (x == 4)
  {
    return 1;
  }
  else if (o == 4)
  {
    return 2;
  }

  return 0;
}

bool fullCol(int col)
{
  bool colFULL = false;
  for (int row = 0; row < sizeof(board) / sizeof(int) - 1; row++)
  {
    if (board[row][col] != 0)
    {
      colFULL = true;
    }
  }
}

bool fullTable()
{
  for (int row = 0; row < sizeof(board) / sizeof(int) - 1; row++)
  {
    for (int col = 0; col < sizeof(board[0]) / sizeof(int); col++)
    {
      if (board[row][col] == 0)
      {
        return false;
      }
    }
  }
  return true;
}

void oneTurn(int player)
{

  pickCol(player);

  switch (checkForWin())
  {
  case 1:
    addWin(1);
    gameOver = true;
    break;

  case 2:
    addWin(2);
    gameOver = true;
    break;
  }

  if (fullTable())
  {
    gameOver = true;;
  }
}

/*
 * actual arduino running code
 */
void setup()
{
  // put your setup code here, to run once:
  /*
   * setup the pinmodes
   */
  // initialize segments for Seven Segment Display
  for (int i = segA; i <= segG; i++)
  {
    pinMode(i, OUTPUT);
  }
  // initialize displays for Seven Segement Display
  for (int i = display1; i <= display4; i++)
  {
    pinMode(i, OUTPUT);
  }
  // initialize the player LED indicators
  for (int i = player1LED; i <= player2LED; i++)
  {
    pinMode(i, OUTPUT);
  }
  // initialize the matrix pins
  for (int i = 30; i <= 32; i++)
  {
    pinMode(i, OUTPUT);
  }
  // initialize the joystick pins
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(12, INPUT_PULLUP);

  // clear the display
  clearSevSeg();

  /*
   * setup the matrix to work
   */
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 15);
  matrix.clearDisplay(0);
}

void loop()
{
  /*get the X and Y for Joystick*/
  // setJoystickValues();

  // put your main code here, to run repeatedly:
  /*
  for (int display = 1; display <= 4; display++)
  {
    for (int num = 0; num <= 9; num++)
    {
      segDisplay(display, num);
      delay(400);
      clearSevSeg();
    }
  }*/
  /*
  displayPlayer1();
  delay(1000);
  displayPlayer2();
  delay(1000);

  drop(1, 1);
  drop(1, 2);
  addWin(1);

  displayPlayer1();
  pickCol(1);


      displayPlayer1();
      delay(500);
      displayPlayer2();
      delay(500);

      if (oneTurn(playerTurn))
      {
        clearBoard();
      }
      


      if (playerTurn == 1)
      {
        playerTurn = 2;
      }
      else{
        playerTurn = 1;
      }
      
*/

      displayPlayer1();
      oneTurn(1);

  delay(500);

  displayPlayer2();
  oneTurn(2);
      
      if (gameOver)
      {
                winDisplay();

        clearBoard();
        gameOver = false;
      }
      


}
