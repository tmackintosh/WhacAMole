// assign LEDs and button to pins
int ledPinPlayer1[] = {4,5,6};
int ledPinPlayer2[] = {10, 11, 12};

int playerOneButton = 2;
int playerTwoButton = 3;
int whiteLEDPlayer1 = 7;
int whiteLEDPlayer2 = 13;

int servoPlayer1 = 8;

// declare variables
int delayTime = 1000; // time delay between lights on/off
int randNumberPlayer1;
int randNumberPlayer2;
int whiteLEDOn; 

bool wasIncreasedPlayer1 = false;
bool wasIncreasedPlayer2 = false;

bool player1Complete = false;
bool player2Complete = false;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

//setup interrupt, button input and LED outputs
void setup() {
  // Use entropy to provide a random seed
  randomSeed(analogRead(A3));
  
  Serial.begin(9600);
  attachInterrupt(0, playerOneInput, FALLING); // specify interrupt routine
  attachInterrupt(1, playerTwoInput, FALLING);
  for (int i=0; i<3; i++){
    pinMode(ledPinPlayer1[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(ledPinPlayer2[i], OUTPUT);
  }
  
  pinMode(playerOneButton, INPUT);
  pinMode(playerTwoButton, INPUT);
  pinMode(whiteLEDPlayer1, OUTPUT);
  pinMode(whiteLEDPlayer2, OUTPUT);

  pinMode(servoPlayer1, OUTPUT);
}

//run main program loop
void loop() {
  while (player1Complete == false and player2Complete == false) {
    randNumberPlayer1 = random(3); // select a random number
    randNumberPlayer2 = random(3);
    
    digitalWrite(ledPinPlayer1[randNumberPlayer1], HIGH); // light the LED with this number
    digitalWrite(ledPinPlayer2[randNumberPlayer2], HIGH);
    
    delay(delayTime);

    digitalWrite(ledPinPlayer1[randNumberPlayer1], LOW);
    digitalWrite(ledPinPlayer2[randNumberPlayer2], LOW);

    digitalWrite(servoPlayer1, LOW);

    // When the lights change to another value, check whether the player had pressed the button
    // in that time. If they did, they scored a point.
    if (wasIncreasedPlayer1 == true) {
      scorePlayer1 += 1;
      
      Serial.println("Player 1 Scored");

      if (scorePlayer1 == 3) {
        Serial.println("Player 1 wins!");
        player1Complete = true;
      }
    }

    if (wasIncreasedPlayer2 == true) {
      scorePlayer2 += 1;
      digitalWrite(servoPlayer1, HIGH);

      Serial.print("Player 2 Scored");

      if (scorePlayer2 == 3) {
        Serial.println("Player 2 wins!");
        player2Complete = true;
      }
    }

    wasIncreasedPlayer1 = false;
    wasIncreasedPlayer2 = false;
    
    delay(delayTime);
  
    digitalWrite(whiteLEDPlayer1, LOW);
    digitalWrite(whiteLEDPlayer2, LOW);
  }

  for (int i = 0; i < 3; i++) {
    // Conditional statements are independent so that players
    // have the ability to draw the game
    if (player1Complete == true) {
      digitalWrite(ledPinPlayer1[i], HIGH);
    }

    if (player2Complete == true) {
      digitalWrite(ledPinPlayer2[i], HIGH);
    }
  }

  delay(1000);

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPinPlayer1[i], LOW);
    digitalWrite(ledPinPlayer2[i], LOW);
  }

  delay(1000);
}

void playerOneInput() {
  Serial.println("Button pressed");

  // Variables will always be set to the currently lit LED, therefore we are able
  // to check whether or not the player hit, or whether or not the player missed
  if (randNumberPlayer1 == 1) {
    wasIncreasedPlayer1 = true;
    digitalWrite(whiteLEDPlayer1, HIGH);
  }
  /*change this code so that white LED only switches on when button is pressed 
  at the right time*/
}

void playerTwoInput() {
  if (randNumberPlayer2 == 1) {
    wasIncreasedPlayer2 = true;
    digitalWrite(whiteLEDPlayer2, HIGH);
  }
}
