#ifndef PID_CONTROLLER_HPP_
#define PID_CONTROLLER_HPP_

#include <stdint.h>

#include "Arduino.h"

#include "Filter.hpp"

typedef enum { ERROR, SETPOINT, MEASUREMENT } derivative_type;
typedef enum { NONE, MOVING_AVERAGE, LOWPASS } filter_type;

template <typename T>
void clamp(T &value, const T &low, const T &high) {
    value = value < low  ? low :
            value > high ? high : value;
}

class PIDController {
    private:
        bool enabled = true;

        float p_gain;
        float i_gain;
        float d_gain;

        float integral = 0.0f;
        float integral_limit;

        float derivative = 0.0f;

        derivative_type d_type = ERROR;

        /* For derivative-on-error */
        float last_error = 0.0f;

        /* For derivative-on-setpoint */
        float last_setpoint = 0.0f;

        /* For derivative-on-measured */
        float last_measured = 0.0f;

        float output_limit;

        uint64_t last_time = 0.0f;

        filter_type derivative_filter_type = NONE;

        Filter *deriv_filter = nullptr;
        bool deriv_filter_enabled = false;

    public:
        PIDController(float p_gain, float i_gain, float d_gain,
                float integral_limit, float output_limit);

        /* En/Disable Passthrough of setpoint */
        void set_enabled(bool enable);

        float compute(const float measured, const float setpoint);

        void set_p(const float _p_gain);
        void set_i(const float _i_gain);
        void set_d(const float _d_gain);

        float get_p();
        float get_i();
        float get_d();

        void integral_reset();

        void set_derivative_type(derivative_type type);

        void set_integral_limit(float limit);
        void set_output_limit(float limit);

        void set_filter(Filter *filter);
        void set_enable_derivative_filter(bool enable);
};

#endif // PID_CONTROLLER_HPP_
