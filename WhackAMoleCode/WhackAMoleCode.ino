// assign LEDs and button to pins
int ledPin[] = {4,5,6};
int playerOneButton = 2;
int whiteLED = 9;

// declare variables
int delayTime = 1000; // time delay between lights on/off
int randNumber;
int whiteLEDOn; 

bool wasIncreased = false;
int score = 0;

//setup interrupt, button input and LED outputs
void setup() {
  Serial.begin(9600);
  attachInterrupt(0, playerOneInput, FALLING); // specify interrupt routine
  for (int i=0; i<3; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(playerOneButton, INPUT);
  pinMode(whiteLED, OUTPUT);
}

//run main program loop
void loop() {
  randNumber = random(3); // select a random number
  digitalWrite(ledPin[randNumber], HIGH); // light the LED with this number
  delay(delayTime);
  digitalWrite(ledPin[randNumber], LOW);

  if (wasIncreased == true) {
    score += 1;
    
    Serial.print("Score! Current score:");
    Serial.println(score);
  } else if (randNumber == 1) {
    Serial.print("Missed! Current score:");
    Serial.println(score);
  }
  
  delay(delayTime);

  wasIncreased = false;
  whiteLEDOn = digitalRead(whiteLED);
  if(whiteLEDOn=HIGH){
    digitalWrite(whiteLED, LOW);
  }  //if whiteLED on = turn it off
}

void playerOneInput() {
  if (randNumber == 1) {
    wasIncreased = true;
  }
  
  digitalWrite(whiteLED, HIGH); 
  /*change this code so that white LED only switches on when button is pressed 
  at the right time*/
}
