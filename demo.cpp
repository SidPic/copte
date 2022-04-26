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
    ObjectsMap omap;
    if (!omap.loadFromDirectory(cfg, cfg.objPath)) {
        panic( "Coldn't load objects from the directory: \"%s\"", cfg.objPath );
    }

    std::cout << omap["atlas"].name << std::endl;

    return 0;
}
