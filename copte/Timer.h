#ifndef COPTE_GLOBAL_H
#define COPTE_GLOBAL_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

namespace cop {

class Timer : protected sf::Clock {
public:

    sf::Time tick    { sf::microseconds(0) };
    sf::Time elapsed { sf::microseconds(0) };
    bool     timeout {        false        };

    Timer ( sf::Time __tick ): tick { __tick }
    {
        restart();
    }

    void update() {
        elapsed = getElapsedTime();

        if ( tick <= sf::microseconds(0) ) return;

        if ( elapsed >= tick ) {
            restart();
            timeout = true;
        } else {
            timeout = false;
        }
    }

    inline void restart() { sf::Clock::restart(); }

    ~Timer () {}

};

}

#endif
