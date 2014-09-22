#ifndef __MATH_HPP__
#define __MATH_HPP__

namespace Math
{
    template <class InterpolationAlgorithm, typename T>
    class Interpolation : public InterpolationAlgorithm
    {
        // using InterpolationAlgorithm::update;

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
    };

    template <typename T>
    class LinearInterpolation
    {
    protected:
        T get(const T& begin, const T& end, float interp)const
        {
            return (end - begin) * interp + begin;
        }
    };


    // Since C++11
    template <typename T>
    using Lerp = Interpolation<LinearInterpolation<T>,T>;

}

#endif
