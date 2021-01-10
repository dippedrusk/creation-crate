// hardware
int LDR = 0;
int LEDs[3] = {11, 10, 9};

// mood lamp config
float x_increment = 0.00001; // controls granularity of colour changes, also affects speed
unsigned int pulseDelay = 1; // controls speed of transition between RGB values
unsigned int power = 25; // positive integer 2-255, controls brightness
int minDarkness = 900; // prod - calibrated to my room
// int minDarkness = 600; // dev, I tend to code with the lights on :P

float RGB[3] = {0.0, 0.0, 0.0};
float x = 0.0;
float radMultiplier = 180/PI;

void setup() {
    for (int i = 0; i < 3; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    analogWriteToLEDs(RGB, LEDs);
}

void analogWriteToLEDs(float values[3], int LEDs[3]) {
    for (int i = 0; i < 3; i++) {
        analogWrite(LEDs[i], values[i]);
    }
}

void loop() {
    if ((x >= PI) || (x < 0.0)) {
        x_increment = 0 - x_increment;
    }

    for (int i = 0; i < 3; i++) {
        RGB[i] = power * abs(sin((x + (i*PI)/3) * radMultiplier));
    }

    if (analogRead(LDR) <= minDarkness) {
        RGB[0] = RGB[1] = RGB[2] = 0.0;
    }
    analogWriteToLEDs(RGB, LEDs);

    delay(pulseDelay);
    x += x_increment;
}
