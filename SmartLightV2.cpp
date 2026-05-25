const int flashing = 9, Sun = 10, light = 11;
const int Photo = 3, sensor = 2, battery = A0;
unsigned long motionTimer = 0;
void setup() {
    pinMode(Photo, INPUT);
    pinMode(sensor, INPUT);
    pinMode(battery, INPUT);

    pinMode(flashing, OUTPUT);
    pinMode(Sun, OUTPUT);
    pinMode(light, OUTPUT);
}

void loop() {
    int sunstate = digitalRead(Photo);
    int motion = digitalRead(sensor);
    int charge = analogRead(battery);
    if (sunstate == LOW) {
        digitalWrite(Sun, HIGH);
        digitalWrite(flashing, LOW);
        digitalWrite(light, LOW);
        if (charge < 153) {
            int blinkState = (millis() / 500) % 2;
            digitalWrite(flashing, blinkState);
        }
    }
    else {
        digitalWrite(Sun, LOW);
        digitalWrite(flashing, LOW);
        if (motion == HIGH) {
            motionTimer = millis();
        }
        if (millis() - motionTimer < 10000) {
            if (charge < 153) {
                analogWrite(light, 120);
            }
            else {
                digitalWrite(light, HIGH);
            }
        }
        else {
            analogWrite(light, 45);
        }
        if (charge < 153) {
            int blinkState = (millis() / 500) % 2;
            digitalWrite(flashing, blinkState);
        }
    }
}