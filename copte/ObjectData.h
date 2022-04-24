#ifndef COPTE_OBJECTDATA_H
#define COPTE_OBJECTDATA_H

#include <map>
#include <vector>
#include <string_view>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace cop {

struct ObjectData {

    typedef std::string_view                         name_t;
    typedef sf::Sprite                               image_t;
    typedef sf::IntRect                              frame_t;
    typedef sf::Vector2f                             hitboxVector_t;
    typedef std::map< name_t, std::vector<frame_t> > animationSet_t;

    name_t         name;
    image_t        image;
    animationSet_t anims;
    hitboxVector_t hitvec;
};

}

#endif
