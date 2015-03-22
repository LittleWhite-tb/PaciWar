#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class Pool
{
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
private:
    std::vector<T> m_pool;

public:
    Pool(std::size_t poolSize=1000)
    {
        m_pool.reserve(poolSize);
    };

    T& create()
    {
        if ( m_pool.size() < m_pool.capacity() )
        {
            m_pool.emplace(m_pool.end(), T()); // Reinit object

            return m_pool[m_pool.size()-1];
        }
        // Should we throw an exception here ?
    }

    void add(T& newElem)
    {
        if ( m_pool.size() < m_pool.capacity() )
        {
            m_pool.emplace(m_pool.end(), std::move(newElem));
        }
    }

    void update(std::function<void(T&)> fct)
    {
        std::for_each(m_pool.begin(),m_pool.end(), fct);
    }

    template <typename U>
    U check(std::function<U(T&)> fct)
    {
        for(auto it : m_pool)
        {
            U result = fct(it);
            if ( result == true )
            {
                return result;
            }
        }
        return U();
    }

/*
    template <typename U>
    std::vector<T>::iterator find_if(std::function<U(T&)> fct, U result)
    {
        return std::find_if(m_pool.begin(), m_pool.end(), [fct, result](T& elem) { return fct(elem) == result; } );
    }

    auto end()const
    {
        return m_pool.end();
    }*/

    void purge(std::function<bool(T)> fct)
    {
       // Maybe we can wrap this to make a false value, removing the instance
        m_pool.erase(std::remove_if(m_pool.begin(),m_pool.end(), fct),
                   m_pool.end());
    }

    std::size_t nbAlive()const
    {
        return m_pool.size();
    }

    typename Pool<T>::iterator begin()
    {
        return m_pool.begin();
    }
    typename Pool<T>::const_iterator cbegin()const
    {
        return m_pool.cbegin();
    }

    typename Pool<T>::iterator end()
    {
        return m_pool.end();
    }
    typename Pool<T>::const_iterator cend()const
    {
        return m_pool.cend();
    }
};

#endif
