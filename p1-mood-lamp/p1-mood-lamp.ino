int redLED = 11;
int greenLED = 10;
int blueLED = 9;
int LDR = 0;
float x = 0.0; // name this better
float x_increment = 0.0001; // also name this better

unsigned int pulseDelay = 1;
int power = 25;
float radMultiplier = 180/PI;
// int minDarkness = 900; // prod - calibrated to my room
int minDarkness = 600; // dev

float RGB[3] = {0.0, 0.0, 0.0};

void setup() {
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
}

void loop() {
    if ((x >= PI) || (x < 0.0)) {
        x_increment = 0 - x_increment;
    }

    // why? this looks vaguely familiar - what math is it? why isn't this simpler?
    RGB[0] = power * abs(sin(x * radMultiplier));
    RGB[1] = power * abs(sin((x + PI/3) * radMultiplier));
    RGB[2] = power * abs(sin(x + (2*PI)/3) * radMultiplier);
    if (analogRead(LDR) > minDarkness) {
        analogWrite(redLED, RGB[0]);
        analogWrite(greenLED, RGB[1]);
        analogWrite(blueLED, RGB[2]);
    } else {
        // Lights go on, lamp goes off
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(blueLED, LOW);
    }

    // calculates a delay that's inversely proportional to the LED's current brightness
    for (int i = 0; i < 3; i++) {
        if (RGB[i] < 1) {
            delay(8 * pulseDelay);
        } else if (RGB[i] < 5) {
            delay(4 * pulseDelay);
        } else if (RGB[i] < 10) {
            delay(2 * pulseDelay);
        } else if (RGB[i] < 100) {
            delay(pulseDelay);
        } // why an empty else? can i simplify this?
    }
    delay(1);
    x += x_increment;
}
