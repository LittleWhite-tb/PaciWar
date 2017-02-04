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

#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class Pool
{
public:
    using const_iterator = typename std::vector<T>::const_iterator;
    using iterator = typename std::vector<T>::iterator;

private:
	std::vector<T> m_pool;


public:
    Pool(std::size_t poolSize=1000)
    {
        m_pool.reserve(poolSize);
    }

    T& create()
    {
        if ( m_pool.size() < m_pool.capacity() )
        {
            m_pool.emplace(m_pool.end(), T()); // Reinit object

            return m_pool[m_pool.size()-1];
        }
        // Should we throw an exception here ?
    }

    template< class... Args >
    void add(Args&&... args)
    {
        if ( m_pool.size() < m_pool.capacity() )
        {
            m_pool.emplace_back(std::forward<Args>(args)...);
        }
    }

    void purge(std::function<bool(T)> fct)
    {
       // Maybe we can wrap this to make a false value, removing the instance
        m_pool.erase(std::remove_if(m_pool.begin(),m_pool.end(), fct),
                   m_pool.end());
    }
    void purge()
    {
        m_pool.erase(m_pool.begin(),m_pool.end());
    }

    std::size_t capacity()const
    {
        return m_pool.capacity();
    }

    std::size_t nbAlive()const
    {
        return m_pool.size();
    }

    Pool<T>::iterator begin()
    {
        return m_pool.begin();
    }
    Pool<T>::const_iterator cbegin()const
    {
        return m_pool.cbegin();
    }

    Pool<T>::iterator end()
    {
        return m_pool.end();
    }
    Pool<T>::const_iterator cend()const
    {
        return m_pool.cend();
    }
};

#endif
