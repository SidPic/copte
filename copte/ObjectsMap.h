#ifndef COPTE_OBJECTSMAP_H
#define COPTE_OBJECTSMAP_H

#include <map>
#include <fstream>
#include <filesystem>
#include <json/json.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ObjectData.h"
#include "Config.h"

namespace cop {

class ObjectsMap : public std::map< ObjectData::name_t, ObjectData > {
public:

    const Config& cfg;

    ObjectsMap () = delete;
    ObjectsMap ( const Config& __cfg ): cfg { __cfg }
    {}

    bool addFromFile ( const Config::Path& path_to_file ) {
        enum { X, Y, W, H };
        sf::Texture*  texture;
        ObjectData*   object;
        Json::Value   value;
        std::ifstream file;

        file.open( path_to_file, std::ifstream::binary );
        if ( !file.is_open() ) return false;

        file >> value;
        file.close();

        object = &(*this)[value["name"]["eng"].asString()];

        object->name = value["name"][cfg.lang].asString();

        object->hitvec.x = value["hitvec"]["x"].asFloat();
        object->hitvec.y = value["hitvec"]["y"].asFloat();

        texture = new sf::Texture;
        if ( !texture->loadFromFile(
            cfg.imgPath/value["sprite"]["src"].asString(),
            sf::IntRect{
                value["sprite"]["rect"][X].asInt(),
                value["sprite"]["rect"][Y].asInt(),
                value["sprite"]["rect"][W].asInt(),
                value["sprite"]["rect"][H].asInt()
            })
        ) { return false; }
        object->image.setTexture( *texture );
        object->image.setScale( cfg.scale, cfg.scale );

        for ( int anim = 0; anim < value["anims"].size(); ++anim )
        for ( int frame = 0; frame < value["anims"][anim]["frames"].size(); ++frame )
        {
            object->anims[value["anims"][anim]["name"].asString()].emplace_back(
                value["anims"][anim]["frames"][frame][X].asInt(),
                value["anims"][anim]["frames"][frame][Y].asInt(),
                value["anims"][anim]["frames"][frame][W].asInt(),
                value["anims"][anim]["frames"][frame][H].asInt()
            );
        }

        return true;
    }

    bool loadFromDirectory ( Config::Path path_to_dir="" ) {
        if (path_to_dir == "") path_to_dir = cfg.objPath;

        for ( const Config::Path& file : std::filesystem::directory_iterator(path_to_dir) )
            if  ( file.extension() == ".json" ) {
                if ( !addFromFile(file) ) return false;
            }

        return true;
    }

    ~ObjectsMap () {}
};

}

#endif
