#ifndef COPTE_CONFIG_H
#define COPTE_CONFIG_H

#include <string>
#include <cstdio>
#include <cstring>
#include <filesystem>

#define BUF_SIZE 256
#define FIELD_I(__field) if ( strcmp(#__field, field) == 0 ) __field = atol(value); else
#define FIELD_S(__field) if ( strcmp(#__field, field) == 0 ) __field = value; else

namespace cop {

class Config {
public:

    typedef unsigned int                Size;
    typedef std::string                 String;
    typedef std::filesystem::path       Path;

    Size
        tileSize,
        winWidth,
        winHeight;

    Path
        imgPath,
        objPath,
        sndPath,
        curPath,
        savePath;

    String lang;

    Config ():
        tileSize  { 32 },
        winWidth  { 640 },
        winHeight { 480 },
        curPath   { std::filesystem::current_path() },
        lang      { "eng" }
    {}

    bool loadFromFile( const Path& path_to_file ) {
        FILE* file;
        char buf[BUF_SIZE],
            field[BUF_SIZE],
            value[BUF_SIZE];

        if ( (file = fopen(path_to_file.c_str(), "r")) == NULL ) return false;

        while ( fgets(buf, BUF_SIZE, file) )
        {
            if ( sscanf(buf, "%s %s", field, value) != 2 ) continue;
            if ( field[0] == '#' ) continue;

            FIELD_I( tileSize )
            FIELD_I( winWidth )
            FIELD_I( winHeight )

            FIELD_S( imgPath )
            FIELD_S( objPath )
            FIELD_S( sndPath )
            FIELD_S( savePath )

            FIELD_S( lang )
            /* else */
            { return false; }
        }


        return true;
    }

    ~Config () {}
};

}

#undef BUF_SIZE
#undef FIELD_I
#undef FIELD_S

#endif
