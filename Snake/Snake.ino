#include <FastLED.h>
#include <stdlib.h>
#define NUM_LEDS 25
#define DATA_PIN 9
CRGB leds[NUM_LEDS];  

/* 
  4, 5, 6, 7 : up, down, left, right
 */

//snake
int snake[25][2]; //carries x, y, and direction
int snakeLen = 1;

//movement
int lightMap[5][5] = {{20, 21, 22, 23, 24}, {19, 18, 17, 16, 15}, {10, 11, 12, 13, 14}, {9, 8, 7, 6, 5}, {0, 1, 2, 3, 4}};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int direc = 3;

int prevStates[] = {LOW, LOW, LOW, LOW}; //for button pressed

boolean dead = false;
int counter = 0;

int appX;
int appY;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(1000000);

  //Coundown
  show5x5();
  FastLED.show();
  delay(1000);

  clearMap();
  FastLED.show();
  delay(1000);

  show3x3();
  FastLED.show();
  delay(1000);

  clearMap();
  FastLED.show();
  delay(1000);

  leds[12] = CHSV(0, 0, 10); //mid
  FastLED.show();
  delay(1000);

  leds[12] = CHSV(0, 0, 0);
  FastLED.show();
  delay(1000);
  

  snake[0][0] = 2;
  snake[0][1] = 2;
  leds[lightMap[snake[0][0]][snake[0][1]]] = CHSV(0, 0, 30);

  setApple();
  
  FastLED.show();
}
void clearMap() {
  for (int i = 0; i < 25; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (counter > 2) {
    return;
  }
  if (!dead) {
    for (int i = 0; i < 500; i++) {
      checkIfClicked(4);
      checkIfClicked(5);
      checkIfClicked(6);
      checkIfClicked(7);
      delay(1);
    }
    move();
  } else { //dead
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        leds[lightMap[i][j]] = CHSV(0, 0, 50);
      }
      FastLED.show();
      delay(400);
      
      clearMap();
      FastLED.show();
      delay(400);
    }
    
    //convey score with morse
    int dots = snakeLen % 5;
    int dashes = (snakeLen - dots) / 5;
    for (int i = 0 ; i < dashes; i++) {
      show3x3();
      FastLED.show();
      delay(700);

      clearMap();
      FastLED.show();
      delay(200);
    }
    for (int i = 0 ; i < dots; i++) {
      show3x3();
      FastLED.show();
      delay(200);

      clearMap();
      FastLED.show();
      delay(200);
    }
    counter++;
  }
}
void checkIfClicked(int port) {
  int currState = digitalRead(port);
  if (currState != prevStates[port - 4]) {
    if (currState == HIGH) {
      if (port == 4) {
        direc = 2;
      } else if (port == 5) {
        direc = 3;
      } else if (port == 6) {
        direc = 1;
      } else {
        direc = 0;
      }
      delay(50);
    }
  }
  prevStates[port - 4] = currState;
}
void move() {
  Serial.print("CurrPos: ");
  Serial.print(snake[0][0]);
  Serial.print(", ");
  Serial.print(snake[0][1]);
  Serial.print(" : ");
  Serial.print(snake[1][0]);
  Serial.print(", ");
  Serial.print(snake[1][1]);
  Serial.print(" : ");
  Serial.print(snake[2][0]);
  Serial.print(", ");
  Serial.print(snake[2][1]);
  Serial.println();

  int tailX = snake[snakeLen - 1][0]; //if eats apple, this doesn't dissapear
  int tailY = snake[snakeLen - 1][1];
  
  leds[lightMap[tailX][tailY]] = CHSV(0, 0, 0); //hide tail
  
  int prevX = snake[0][0]; //used to relocate snake's body
  int prevY = snake[0][1];

  int headX = snake[0][0]; //used to detect if there is collision (death)
  int headY = snake[0][1];

  //move the head
  /*
  Serial.print("Move Head: ");
  Serial.print(snake[0][0]);
  Serial.print(", ");
  Serial.print(snake[0][1]);
  Serial.print(" -> ");
  */
  snake[0][0] += dx[direc];
  snake[0][1] += dy[direc];
  /*
  Serial.print(snake[0][0]);
  Serial.print(", ");
  Serial.print(snake[0][1]);
  Serial.println();
  */

  snake[0][0] = getInBounds(snake[0][0]);
  snake[0][1] = getInBounds(snake[0][1]);
  
  for (int i = 1; i < snakeLen; i++) {
    int tempX = snake[i][0];
    int tempY = snake[i][1];
    if (tempX == headX && tempY == headY) { //head collision
      dead = true;
      clearMap();
      FastLED.show();
      delay(200);
      Serial.println("GAME OVER");
      return;
    }
    snake[i][0] = prevX;
    snake[i][1] = prevY;
    prevX = tempX;
    prevY = tempY;
  }

  if (snake[0][0] == appX && snake[0][1] == appY) { //got apple
    Serial.println("Apple ran into");
    snake[snakeLen][0] = tailX;
    snake[snakeLen][1] = tailY;
    leds[lightMap[tailX][tailY]] = CHSV(0, 0, 5);
    snakeLen++;
    setApple();
  }
  
  //move graphically
  leds[lightMap[snake[0][0]][snake[0][1]]] = CHSV(0, 0, 5);

  //Serial.println("===================");
  FastLED.show();
}

void setApple() {
  appX = snake[0][0] + snake[0][0] * snake[snakeLen - 1][1]; //try to make it random
  appY = snake[0][0] - snake[0][1] * snake[snakeLen - 1][0];
  appX = getInBounds(appX);
  appY = getInBounds(appY);
  Serial.println("Running inSnake");
  boolean in = inSnake(appX, appY);
  Serial.println("inSnake ran");
  while (in) {
    appX -= 1;
    appY += 1;
    appX = getInBounds(appX);
    appY = getInBounds(appY);
    Serial.print("Proposed: ");
    Serial.print(appX);
    Serial.print(", ");
    Serial.println(appY);
    in = inSnake(appX, appY);
  }
  Serial.print("Apple set to: ");
  Serial.print(appX);
  Serial.print(", ");

  Serial.println(appY);
  leds[lightMap[appX][appY]].setRGB(30, 10, 10);
}

boolean inSnake(int x, int y) {
  Serial.print("Target: ");
  printCoords(x, y);
  Serial.println(snakeLen);
  for (int i = 0; i < snakeLen; i++) {
    Serial.print("Testing: ");
    printCoords(snake[i][0], snake[i][1]);
    if (x == snake[i][0] && y == snake[i][1]) {
      return true;
    }
  }
  return false;
}

int getInBounds(int test) {
  if (test < 0) {
    test += 5;
    return getInBounds(test);
  } else if (test > 4) {
    test -= 5;
    return getInBounds(test);
  }
  return test;
}

//graphical displays
void show5x5() {
  for (int i = 0; i < 25; i++) {
    leds[i] = CHSV(0, 0, 10);
  }
}
void show3x3() {
  for (int i = 1; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      leds[lightMap[i][j]] = CHSV(0, 0, 10);
    }
  }
}

void printCoords(int x, int y) { //only for debugging
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);
}

