#ifndef FILTER_HPP_
#define FILTER_HPP_

class Filter {
    public:
        virtual float next(float value) = 0;
};

#endif // FILTER_HPP_

