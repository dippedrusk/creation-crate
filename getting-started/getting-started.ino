// Alternating blinking lights with two LEDs

int LED1 = 5;
int LED2 = 2;

void setup() {
    pinMode(LED1, OUTPUT);
}

void loop() {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(1000);
}
