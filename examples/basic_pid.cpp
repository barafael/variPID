/********************************************************
 * Basic PID Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PIDController.hpp>

float input;
float setpoint;
float output;

//Specify the links and initial tuning parameters
PIDController controller(0.5, 0.01, 0.0, 2.5, 1.5);

void setup() {
  input = 255.0 / analogRead(0);
  setpoint = 1.0;
}

void loop() {
  input = 255.0 / analogRead(0);
  output = controller.compute(input, setpoint);
  analogWrite(3, output);
}
