#ifndef COPTE_OBJECT_H
#define COPTE_OBJECT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "ObjectData.h"
#include "ObjectsMap.h"
#include "Config.h"
#include "Timer.h"

namespace cop {

class Object : public sf::Drawable {
public:

    typedef sf::Vector2f position_t;

    static Timer timer;

    position_t                     pos;
    const ObjectData*              data;
    const ObjectData::animation_t* anim;
    sf::Sprite*                    sprite;

    Object (): data { nullptr } {}
    Object ( ObjectsMap& omap, const char* key, const position_t& __pos={0,0} ):
        pos { __pos  }
    {
        if ( !setData( omap, key ) ) data = nullptr;
    }

   // virtual void update();

    virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const {
        #ifdef COP_CHECK_OBJECTS
        if ( data == nullptr ) return;
        #endif

        static const ObjectData::animation_t* curanim { anim };
        static ObjectData::animation_t::const_iterator frame { anim->cbegin() };

        if ( timer.timeout ) {
            ++frame;

            if ( frame == anim->end() ) {
                frame = anim->begin();
            }
            if ( curanim != anim ) {
                curanim = anim;
                frame = anim->begin();
            }

            sprite->setTextureRect( *frame );
            sprite->setPosition( pos );
        }

        target.draw( *sprite, states );
    }

    bool setAnim ( const char* key ) {
        try {
            anim = &data->anims.at(key);
        }
        catch ( std::out_of_range ) {
            return false;
        }
        return true;
    }

    bool setData ( ObjectsMap& omap, const char* key ) {
        try {
            data = &omap.at(key);
        }
        catch ( std::out_of_range ) {
            return false;
        }
        if ( !setAnim( "none" ) ) return false;

        sprite = &omap[key].image;
        updateOrigin( omap.cfg );

        return true;
    }

    inline void setPos ( float x, float y ) { pos = { x, y }; }

    void updateOrigin( const Config& cfg ) {
        try {
            sprite->setOrigin( anim->at(0).width/2, anim->at(0).height - cfg.tileSize/2 );
        }
        catch ( std::out_of_range ) {
            #ifdef COP_IMAGE_OBJECT_ENABLE
            sprite->setOrigin( sprite->getSize().x/2, sprite->getSize().y - cfg.tileSize/2 );
            #else
            sprite->setOrigin( cfg.tileSize/2, cfg.tileSize/2 );
            #endif
        }
    }

    ~Object () {}
};

Timer Object::timer { sf::seconds(0) };

}

#endif
