#ifndef LOW_PASS_HPP_
#define LOW_PASS_HPP_

#include <stdint.h>

#include "Filter.hpp"

class Lowpass : public Filter {
    private:
        float prev_output = 0;
        float beta = 1.0;
        float ateb = 0.0;

    public:
        explicit Lowpass(float beta);
        float next(float value) override;
        void set_beta(float beta);
};

#endif // LOW_PASS_HPP_
