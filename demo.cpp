#include "copte/copte.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdarg>

using namespace cop;

void panic ( const char* fstr, ... ) {
    va_list l;
    va_start(l, fstr);
    vfprintf(stderr, fstr, l);
    va_end(l);

    exit(EXIT_FAILURE);
}

int main() {

    Config cfg;
    if (!cfg.loadFromFile( "config.cfg" )) {
        panic( "Couldn't read the config file: \"%s\"", "config.h" );
    }

    ObjectsMap omap { cfg };
    if (!omap.loadFromDirectory( cfg.objPath )) {
        panic( "Coldn't load objects from the directory: \"%s\"", cfg.objPath.c_str() );
    }

    Object obj;
    if (!obj.setData( omap, "elf" )) {
        panic( "Current <ObjectsMap> don't contains the object: \"%s\"", "elf" );
    }
    obj.setPos( cfg.winWidth/2, cfg.winHeight/2 );
    obj.setAnim( "idle" );

    Object::timer.tick = sf::milliseconds(cfg.animDelay);

    sf::RenderWindow win { sf::VideoMode(cfg.winWidth, cfg.winHeight), "copte",
                           cfg.fullscreen ? sf::Style::Fullscreen : sf::Style::Default };
    sf::Event event;


    while ( win.isOpen() ) {
        Object::timer.update();

        while ( win.pollEvent(event) )
        switch ( event.type ) {
            case sf::Event::Closed:
                win.close();
            break;
            case sf::Event::KeyPressed:
            switch ( event.key.code ) {
                case sf::Keyboard::Escape: win.close(); break;
            }
            break;
        }

        win.clear();

        win.draw( obj );

        win.display();
    }

    return 0;
}
