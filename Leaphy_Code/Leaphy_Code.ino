/*
 * This code is written by: Kevin Dohmen.
 * 
 * I know i made it a bit unnecessarily complicated.
 * (I'm just 14 years old and coppied half of the code from github XD)
 * 
 * Please look at the wiring.
 * 
 * ########################################################################
 * 1x Arduino uno R3
 * 2x HC-SR-04
 * 2x Hobby motor
 * 2x Mosfet/Transistor (If you don't want to kill your arduino)
 * ########################################################################
 * [wiring]
 * Sensor 1(left):
 *  vcc  > +5v
 *  echo > 5
 *  trig > 4
 *  gnd  > gnd
 *  
 * Sensor 2(right):
 *  vcc  > +5v
 *  echo > 7
 *  trig > 6
 *  gnd  > gnd
 *  
 * Motor left:
 *  +    > 8  (Use mosfet or transistor)
 *  -    > gnd
 *  
 * Motor right:
 *  +    > 10 (Use mosfet or transistor)
 *  -    > gnd
 *  
 * Image of wireing is on github
 * ########################################################################
 */

int MinDistance = 30;

bool Left;
bool Right;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
}

bool Sensor_Read(int Trig, int Echo){ //############################################################### Sensor Read

  // Clears the trigPin condition
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(Echo, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  if(distance < 0){
    distance = 100;
  }
  
  Serial.println();
  Serial.println(distance);

  if(distance < MinDistance){
    return true;
  }
  else{
    return false;
  }
}

void Drive(bool L, bool R){ //######################################################################### Drive
  if(L == true && R == true){
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
  }

  else if(L == true){ //########################################################## Left
    digitalWrite(10, HIGH);
    digitalWrite(8, LOW);
  }

  else if(R == true){ //########################################################## Right
    digitalWrite(8, HIGH);
    digitalWrite(10, LOW);
  }

  else if(L == false && R == false){ //########################################### Straight
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Sensor_Read( 4, 5) == true){ //############################################## Read Sensor 1 (turn right)
    Serial.println("[Turn_Right]");
  }
 
  else if(Sensor_Read(6, 7) == true){ //########################################## Read Sensor 2 (turn left)
    Serial.println("[Turn_Left]");
    Left = true;
    Right = false;
  }

  else{ //######################################################################## If nothing = true (go straight)
  Left = false;
  Right = false;
  Serial.println("[Straight]");
  }

  Drive(Left, Right);
}
