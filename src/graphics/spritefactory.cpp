#include "spritefactory.h"
#include "rectangularsprite.h"

std::shared_ptr<Sprite> SpriteFactory::createRectangularSprite(SpriteType type, Rectangle rect, RGBA rgba){

    if (type == SpriteFactory::SpriteType::RECTANGULAR ) {
        return std::make_shared<RectangularSprite>(rect, rgba);
    } else {
        return nullptr;
    }
}