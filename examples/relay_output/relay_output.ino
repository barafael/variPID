/*
 * PID RelayOutput Example adapted from:
 * https://github.com/br3ttb/Arduino-PID-Library/tree/master/examples/PID_RelayOutput
 *
 * Similar to basic example, except that the PID output determines the relay 'on-time'.
 * If the PID output is high, the relay should be on for a longer time.
 * The relay never switches faster than the window size, which is 5 seconds here.
 */

#include <PIDController.hpp>

#define INPUT_PIN 0
#define RELAY_PIN 6

const size_t window_size = 5000;
uint64_t     window_start_time;

float measurement;
float setpoint = 1.0;
float output;

// Specify tuning parameters
// (output_limit should start at 0 here)
PIDController controller(2.0, 5.0, 1.0, 100.0, 0.0, window_size);

void setup() {
    Serial.begin(9600);
    pinMode(INPUT_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    window_start_time = millis();

    setpoint = 100.0;
}

void loop() {
    measurement = 255.0 / analogRead(INPUT_PIN);
    output      = controller.compute(measurement, setpoint);
    Serial.println(output);

    if (millis() - window_start_time > window_size) {
        window_start_time += window_size;
    }
    if (output < millis() - window_start_time) {
        digitalWrite(RELAY_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
    }
}
