#ifndef COPTE_CONFIG_H
#define COPTE_CONFIG_H

#include <string>
#include <cstdio>
#include <cstring>
#include <filesystem>

#define BUF_SIZE 256
#define FIELD_I(__field) if ( strcmp(#__field, field) == 0 ) __field = atol(value); else
#define FIELD_S(__field) if ( strcmp(#__field, field) == 0 ) __field = value; else
#define FIELD_B(__field) if ( strcmp(#__field, field) == 0 )                                       \
{                                                                                                  \
    if ( strcmp(value, "true") == 0 )  __field = true; else                                        \
    if ( strcmp(value, "false") == 0 ) __field = false; else                                       \
    return false;                                                                                  \
} else

namespace cop {

class Config {
public:

    typedef unsigned int                Size;
    typedef std::string                 String;
    typedef std::filesystem::path       Path;

    Size
        tileSize, tileSize_unscaled,
        winWidth,
        winHeight,
        atlasWidth,
        atlasHeight,
        animDelay,  // delay between the frames as milliseconds
        FPS;

    Path
        imgPath,
        objPath,
        sndPath,
        shdPath,    // shaders
        curPath,
        savePath;

    String lang;
    float scale;
    bool fullscreen;

    Config ():
        tileSize    { 32 },  tileSize_unscaled { 32 },
        winWidth    { 640 },
        winHeight   { 480 },
        atlasWidth  { 640 },
        atlasHeight { 480 },
        curPath     { std::filesystem::current_path() },
        lang        { "eng" },
        fullscreen  { false }
    {
        updateScale();
    }

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

            FIELD_B( fullscreen )

            FIELD_I( tileSize )
            FIELD_I( winWidth )
            FIELD_I( winHeight )
            FIELD_I( atlasWidth )
            FIELD_I( atlasHeight )
            FIELD_I( animDelay )
            FIELD_I( FPS )

            FIELD_S( imgPath )
            FIELD_S( objPath )
            FIELD_S( sndPath )
            FIELD_S( shdPath )
            FIELD_S( curPath )
            FIELD_S( savePath )

            FIELD_S( lang )
            /* else */
            { return false; }
        }

        tileSize_unscaled = tileSize;
        updateScale();
        return true;
    }

    inline void updateScale () {
        scale = (
            (float)winWidth/atlasWidth +
            (float)winHeight/atlasHeight
            )
            / 2.0f;

        tileSize *= scale;
    }

    ~Config () {}
};

}

#undef BUF_SIZE
#undef FIELD_I
#undef FIELD_S

#endif
