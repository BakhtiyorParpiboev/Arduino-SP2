#define LED_PIN 9
int pwm_period;
int pwm_duty;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    pwm_period = 10000;
    for (pwm_duty = 0; pwm_duty <= 100; pwm_duty++) {
        int on_time = pwm_period * pwm_duty / 100;
        int off_time = pwm_period - on_time;

        digitalWrite(LED_PIN, HIGH);
        delayMicroseconds(on_time);
        digitalWrite(LED_PIN, LOW);
        delayMicroseconds(off_time);
    }

    for (pwm_duty = 100; pwm_duty >= 0; pwm_duty--) {
        int on_time = pwm_period * pwm_duty / 100;
        int off_time = pwm_period - on_time;

        digitalWrite(LED_PIN, HIGH);
        delayMicroseconds(on_time);
        digitalWrite(LED_PIN, LOW);
        delayMicroseconds(off_time);
    }
}
