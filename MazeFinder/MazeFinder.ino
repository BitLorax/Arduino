
//THEORETICAL Project: Robot that navigates through a maze (maze turns must be 90 degrees and the passageway must be wide enough for the car to turn 360 degrees)
//Due to the motor not being strong enough, it cannot be implemented in my arduino set

#define MOTOR_R 4
#define MOTOR_L 5

#define SENSE //sensor in front

//These values depend on motor, calibrate as necessary
#define turnSpd 3
#define fwrdSpd 10
#define hitTime 500 //how long it takes for the car to hit the wall to the right, if turned 90 degrees to face it


int wheelR = 0;
int wheelL = 0;


void setup() {
  pinMode(MOTOR_R, OUTPUT);
  pinMode(MOTOR_L, OUTPUT);
}

//At every step, keep turning right until there's no wall, then move foward (right hand rule)

void loop() {
  //no goal condition, if it makes it out of the maze, user turns it off
  
  boolean isWall = true;
  turn90(true);
  stopMove();
  while (isWall) {
    //test if there's wall on the right
  
    //keep going foward until it hits a wall or it goes beyond the wall distance
    analogWrite(MOTOR_R, fwrdSpd);
    analogWrite(MOTOR_L, fwrdSpd);
    int count = 0;
    boolean isWall = true;
    while (analogRead(SENSE) == 0) {
      delay(1);
      count++;
      if (count >= hitTime) { //no wall
        isWall = false;
        break;
      }
    }
    stopMove();
  
    if (isWall) { turn left
      analogWrite(MOTOR_R, -1 * fwrdSpd);
      analogWrite(MOTOR_L, -1 * fwrdSpd);
      delay(count);
      stopMove();
      turn90(false);
    }
  }
  
  analogWrite(MOTOR_R, fwrdSpd);
  analogWrite(MOTOR_L, fwrdSpd);

  delay(500); //how long it should go before it checks again
}

void stopMove() {
  analogWrite(MOTOR_R, 0);
  analogWrite(MOTOR_L, 0);
}

void turn90(boolean right) { //going right or left
  int x = 1;
  int y = 1;
  if (right) {
    x = -1;
  } else {
    y = -1
  }
  analogWrite(MOTOR_R, x * turnSpd);
  analogWrite(MOTOR_L, y * turnSpd);
  delay(1000);
  analogWrite(MOTOR_R, 0);
  analogWrite(MOTOR_L, 0);
}

