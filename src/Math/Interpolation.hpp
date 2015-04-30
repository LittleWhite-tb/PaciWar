#ifndef __INTERPOLATION_HPP__
#define __INTERPOLATION_HPP__

#include "Angle.hpp"

namespace Math
{
    template <class InterpolationAlgorithm, typename T>
    class Interpolation : public InterpolationAlgorithm
    {
    private:
        T m_begin;
        T m_end;

    public:
        Interpolation(const T& begin,
                      const T& end)
            :m_begin(begin),m_end(end) {}

        T get(float interp)const
        {
            return InterpolationAlgorithm::get(m_begin, m_end, interp);
        }
        static T get(const T& begin, const T& end, float interp)
        {
            return InterpolationAlgorithm::get(begin, end, interp);
        }
    };

    template <typename T>
    class LinearInterpolation
    {
    public:
        static T get(const T& begin, const T& end, float interp)
        {
            return (end - begin) * interp + begin;
        }
    };


    template <typename T>
    class EaseInEaseOutInterpolation
    {
    public:
        static T get(const T& begin, const T& end, float interp)
        {
            // http://math.stackexchange.com/questions/121720/ease-in-out-function
            float interp2 = interp*interp;
            return (interp2 / (interp2 + (1 - interp)*(1 - interp))) * (end-begin)+begin;
        }
    };

    template <typename T>
    class EaseInEaseOutInterpolation<Angle<T> >
    {
    public:
        static Angle<T> get(const Angle<T>& begin, const Angle<T>& end, float interp)
        {
            // http://stackoverflow.com/questions/2708476/rotation-interpolation
            T diff = end.value-begin.value;
            T fixedBegin = begin.value;
            T fixedEnd = end.value;
            if ( diff > 180 ) // Here, normal interpolation will take the longest path
            {
                fixedBegin += 360;
            }
            else if ( diff < -180 )
            {
                fixedEnd += 360;
            }
            Angle<T> result = EaseInEaseOutInterpolation<float>::get(fixedBegin,fixedEnd,interp);
            result.wrap();
            return result;
        }
    };


    // Since C++11
    template <typename T>
    using Lerp = Interpolation<LinearInterpolation<T>,T>;

    template <typename T>
    using EaseInEaseOut = Interpolation<EaseInEaseOutInterpolation<T>,T>;
}

#endif
