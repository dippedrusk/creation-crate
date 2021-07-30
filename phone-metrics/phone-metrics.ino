// hardware
int LDR = 0;
int LEDs[3] = {11, 10, 9};

unsigned int power = 25; // positive integer 2-255, controls brightness
int minDarkness = 900; // prod - calibrated to my room
// int minDarkness = 600; // dev, I tend to code with the lights on :P
bool dark = false;

unsigned long phone_time = 0.0;
unsigned long start_time;
unsigned long end_time;
unsigned long diff;

float RGB[3] = {0.0, 0.0, 0.0};

void setup() {
    for (int i = 0; i < 3; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    analogWriteToLEDs(RGB, LEDs);
    Serial.begin(9600);
    start_time = millis();
}

void analogWriteToLEDs(float values[3], int LEDs[3]) {
    for (int i = 0; i < 3; i++) {
        analogWrite(LEDs[i], values[i]);
    }
}

void loop() {
    if (analogRead(LDR) <= minDarkness) {
        if (dark) {
            start_time = millis();
        }
        dark = false;
        RGB[0] = RGB[1] = RGB[2] = 0.0;
        analogWriteToLEDs(RGB, LEDs);
    } else {
        if (!dark) {
            // hello darkness my old friend
            end_time = millis();
            diff = (end_time - start_time) / 1000;
            phone_time += diff;
            Serial.println(phone_time);
        }
        dark = true;
        RGB[0] = RGB[1] = RGB[2] = power;
        analogWriteToLEDs(RGB, LEDs);
    }
}
