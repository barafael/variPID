/*
 * Basic PID Example adapted from:
 * https://github.com/br3ttb/Arduino-PID-Library/tree/master/examples/PID_Basic
 * Reading analog input 0 to control analog PWM output 3
*/

#include <PIDController.hpp>

#define INPUT_PIN 0
#define OUTPUT_PIN 3

float measurement;
float setpoint = 1.0;
float output;

// Specify tuning parameters
PIDController controller(0.5, 0.01, 0.0, 2.5, 1.5);

void setup() {
    Serial.begin(9600);
    pinMode(INPUT_PIN, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
    measurement = 255.0 / analogRead(INPUT_PIN);
    output = controller.compute(measurement, setpoint);
    Serial.println(output);
    analogWrite(OUTPUT_PIN, output);
}
