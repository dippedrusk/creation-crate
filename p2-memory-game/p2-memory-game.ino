// hardware
const int buzzer = 12;
const int LEDs[4] = {10, 9, 8, 7};
const int buttons[4] = {5, 4, 3, 2};

const int frequencies[5] = {1900, 1600, 1300, 1000, 3200};
int buttonPressed[4] = {0, 0, 0, 0}; // could be bool

int gameOn = 0; // change this
int wait = 0;
int currRound = 1;
int LEDTime = 500;
int LEDDelay = 200;
int numRounds = 10;
int correct = 0;
int speed = 5;

void playTone(int tone, int duration) {
    for (long i = 0; i < duration*1000L; i += tone*2) { // whyyyyy
        digitalWrite(buzzer, HIGH);
        delayMicroseconds(tone);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(tone);
    }
}

void setup() {
    randomSeed(analogRead(0));
    for (int i = 0; i < 3; i++) {
        pinMode(buttons[i], INPUT);
        pinMode(LEDs[i], OUTPUT);
    }
    pinMode(buzzer, OUTPUT);
}

void loop() {
    int gamePattern[numRounds];
    int userPattern[numRounds];

    int i;
    if (!gameOn) {
        for (i = 0; i < numRounds; i++) {
            userPattern[i] = 0;
            gamePattern[i] = random(0,4);
        }
        gameOn = 1;
    }

    if (!wait) {
        delay(200);
        for (i = 0; i < currRound; i++) {
            LEDDelay = LEDTime / (1 + (speed/numRounds)*(currRound-1));
            int _i = gamePattern[i];
            digitalWrite(LEDs[_i], HIGH);
            playTone(frequencies[_i], LEDDelay);
            digitalWrite(LEDs[_i], LOW);
            delay(100/speed);
        }
        wait = 1;
    }

    int buttonChange = 0;
    int j = 0;
    for (j = 0; j < currRound; j++) {
        while (!buttonChange) { // shouldn't make a diff
            for (i = 0; i < 4; i++) {
                buttonPressed[i] = digitalRead(buttons[i]);
                buttonChange += buttonPressed[i];
            }
        }

        for (i = 0; i < 4; i++) {
            if (buttonPressed[i] == HIGH) {
                digitalWrite(LEDs[i], HIGH);
                playTone(frequencies[i], LEDTime);
                digitalWrite(LEDs[i], LOW);
                wait = 0;
                userPattern[j] = i;
                buttonPressed[i] = LOW;
                buttonChange = 0;
            }
        }

        if (userPattern[j] == gamePattern[j]) {
            correct = 1;
        } else {
            correct = 0; // or we could just break????
            wait = 0;
            break;
        }
    }

    if (!correct) {
        i = 0;
        gameOn = 0;
        currRound = 1;

        for (int j = 0; j < 2; j++) {
            delay(200);
            for (i = 0; i < 4; i++) {
                digitalWrite(LEDs[i], HIGH);
            }
            playTone(frequencies[4], LEDTime);
            for (i = 0; i < 4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
        }
        delay(500);
    } else {
        currRound++;
        wait = 0;
    }

    if (currRound == numRounds) {
        delay(500);
        // play victory song
        gameOn = 0;
        currRound = 1;
        numRounds += 2;
        speed++;
    }
}
