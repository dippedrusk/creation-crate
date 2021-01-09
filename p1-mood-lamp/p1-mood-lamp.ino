int redLED = 11;
int greenLED = 10;
int blueLED = 9;
int LDR = 0;

unsigned int pulseSpeed = 5;
int power = 150; // why? (their comment says 2-255? also why?)
float rad_multiplier = 180/PI;

float RGB[3] = {0.0, 0.0, 0.0};

void setup() {
    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
}

void loop() {
    for (float x = 0; x < PI; x += 0.00001) {
        // why? this looks vaguely familiar - what math is it? why isn't this simpler?
        RGB[0] = power * abs(sin(x *rad_multiplier));
        RGB[1] = power * abs(sin((x + PI/3) * rad_multiplier));
        RGB[2] = power * abs(sin((x + 2*PI)/3) * rad_multiplier);
        if (analogRead(LDR) > 600) { // why 600?
            analogWrite(redLED, RGB[0]);
            analogWrite(greenLED, RGB[1]);
            analogWrite(blueLED, RGB[2]);
        } else {
            // Lights go on, lamp goes off
            digitalWrite(redLED, LOW);
            digitalWrite(blueLED, LOW);
            digitalWrite(greenLED, LOW);
        }

        for (int i = 0; i < 3; i++) {
            if (RGB[i] < 1) {
                delay(20 * pulseSpeed);
            } else if (RGB[i] < 5) {
                delay(10 * pulseSpeed);
            } else if (RGB[i] < 10) {
                delay(2 * pulseSpeed);
            } else if (RGB[i] < 100) {
                delay(pulseSpeed);
            } // why an empty else? can i simplify this?
            delay(1);
        }
    }

}
