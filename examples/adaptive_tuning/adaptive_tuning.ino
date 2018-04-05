/*
 * PID Adaptive Tuning Example adapted from:
 * https://github.com/br3ttb/Arduino-PID-Library/tree/master/examples/PID_AdaptiveTunings
 * Adapt PID parameters to the situation by using a more aggressive controller when the error is large.
 */

#include <PIDController.hpp>

#define INPUT_PIN 0
#define OUTPUT_PIN 3

float measurement;
float setpoint = 100.0;
float output;

// Aggressive and conservative tuning parameters
float agg_kp  = 4, agg_ki  = 0.2, agg_kd   = 1;
float cons_kp = 1, cons_ki = 0.05, cons_kd = 0.25;

// Specify tuning parameters
PIDController controller(cons_kp, cons_ki, cons_kd, 15.0, 25.0);

void setup() {
    Serial.begin(9600);
    pinMode(INPUT_PIN, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
    measurement = 255.0 / analogRead(INPUT_PIN);
    // TODO: add set_params method
    if (abs(setpoint - measurement) < 10) {
        controller.set_p(cons_kp);
        controller.set_i(cons_ki);
        controller.set_d(cons_kd);
    } else {
        controller.set_p(agg_kp);
        controller.set_i(agg_ki);
        controller.set_d(agg_kd);
    }
    output = controller.compute(measurement, setpoint);
    Serial.println(output);
    analogWrite(OUTPUT_PIN, output);
}
