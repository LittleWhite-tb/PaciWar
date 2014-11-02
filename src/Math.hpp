#ifndef __MATH_HPP__
#define __MATH_HPP__

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
    protected:
        static T get(const T& begin, const T& end, float interp)
        {
            return (end - begin) * interp + begin;
        }
    };

    template <typename T>
    class EaseInEaseOutInterpolation
    {
    protected:
        static T get(const T& begin, const T& end, float interp)
        {
            // http://math.stackexchange.com/questions/121720/ease-in-out-function
            float interp2 = interp*interp;
            return (interp2 / (interp2 + (1 - interp)*(1 - interp))) * (end-begin)+begin;
        }
    };


    // Since C++11
    template <typename T>
    using Lerp = Interpolation<LinearInterpolation<T>,T>;

    template <typename T>
    using EaseInEaseOut = Interpolation<EaseInEaseOutInterpolation<T>,T>;
}

#endif
