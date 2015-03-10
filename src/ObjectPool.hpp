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
    std::size_t m_numberObjectsAlive;

public:
    Pool(std::size_t poolSize=1000)
        :m_pool(poolSize),m_numberObjectsAlive(0)
    {};

    T& create()
    {
        if ( m_numberObjectsAlive < m_pool.capacity() )
        {
            m_pool[m_numberObjectsAlive] = T(); // Reinit object

            return m_pool[m_numberObjectsAlive++];
        }
        // Should we throw an exception here ?
    }

    void add(T& newElem)
    {
        if ( m_numberObjectsAlive < m_pool.capacity() )
        {
            m_pool[m_numberObjectsAlive++] = std::move(newElem);
        }
    }

    void destroy(std::size_t index)
    {
        if ( m_numberObjectsAlive > 0 && index < m_numberObjectsAlive)
        {
            std::swap(m_pool[index], m_pool[m_numberObjectsAlive]);
            m_numberObjectsAlive--;
        }
    }

    void apply(std::function<void(T)> fct)const
    {
        std::for_each(std::begin(m_pool),std::begin(m_pool)+m_numberObjectsAlive, fct);
    }

    void update(std::function<void(T&)> fct)
    {
        // Maybe we can wrap this to make a false value, removing the instance
        std::for_each(std::begin(m_pool),std::begin(m_pool)+m_numberObjectsAlive, fct);
    }

    void purge(std::function<bool(T)> fct)
    {
        std::remove_if(std::begin(m_pool),std::begin(m_pool)+m_numberObjectsAlive, [this, fct](T& elem)
        {
            bool result = fct(elem);
            if ( result )
            {
                m_numberObjectsAlive--;
            }
            return result;
        });
    }

    std::size_t nbAlive()const
    {
        return m_numberObjectsAlive;
    }
};

#endif
