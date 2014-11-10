#ifndef __ANGLE_HPP__
#define __ANGLE_HPP__

namespace Math
{
    template <typename T>
    struct Angle
    {
        T value;

        Angle(const T& value):value(value) {}
        operator float()const { return this->value; }

        void wrap()
        {
            while ( this->value > 360 )
            {
                this->value -= 360;
            }
            while ( this->value < -360 )
            {
                this->value += 360;
            }
        }
    };
}

#endif // ANGLE_HPP
