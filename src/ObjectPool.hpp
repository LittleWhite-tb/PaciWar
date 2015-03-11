#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class Pool
{
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

    void apply(std::function<void(T&)> fct)
    {
        std::for_each(m_pool.begin(),m_pool.end(), fct);
    }

    void update(std::function<void(T&)> fct)
    {
        std::for_each(m_pool.begin(),m_pool.end(), fct);
    }

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
};

#endif
