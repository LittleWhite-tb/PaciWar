/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2015 LittleWhite (lw.demoscene@gmail.com)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
            return (interp2 / (interp2 + (1.f - interp)*(1.f - interp))) * (end-begin)+begin;
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
            if ( diff > 180.f ) // Here, normal interpolation will take the longest path
            {
                fixedBegin += 360.f;
            }
            else if ( diff < -180.f )
            {
                fixedEnd += 360.f;
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
