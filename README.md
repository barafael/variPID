# Arduino PID library

variPID is an Arduino library that supports irregular update intervals, derivative on error/setpoint/measurement and Lowpass/MovingAverage filters for derivative.

The PID algorithm is adapted and influenced by this series on [Brett Beauregard's blog:](http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/).
An exception to this is that this algorithm does use time difference between invocations to accurately reflect irregular update frequency.
This is important only for the I and D term calculation.

## Functionality

The functions available in the library include

```c
PIDController(float p_gain, float i_gain, float d_gain,
        float integral_limit, float output_limit); // Constructor with the most important PID parameters

void set_enabled(bool enable); // En/Disable Passthrough of setpoint (automatic vs. manual mode)

float compute(const float measured, const float setpoint); // PID calculation, do this somewhat regularly

void set_p(const float _p_gain);
void set_i(const float _i_gain);
void set_d(const float _d_gain);

void set_integral_limit(float limit);
void set_output_limit(float limit);

float get_p();
float get_i();
float get_d();

void integral_reset(); // Resets the integral term, use sparingly, preferrably use integral_limit parameter

void set_derivative_type(derivative_type type); // Supported types are ERROR, SETPOINT, FEEDBACK

void set_filter(Filter *filter); // Supported filters right now are MOVING_AVERAGE, LOWPASS
void set_enable_derivative_filter(bool enable);

```
The supported filters can be extended, any class that implements a `next()` method should work:

```c
class Filter {
    public:
        virtual float next(float value) = 0;
};
```
Filter should be the superclass.

To use the library, copy the download to the Library directory.

## Examples

## Notes:

Floats are used everywhere right now, but it would be simple to generify the implementation (I think). Open issue.
