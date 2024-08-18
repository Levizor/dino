#include "SFML/Graphics/Rect.hpp"
#include "Object.h"

class Dino:public Object{
    public:
        Dino();
        void jump();
        void update(const float& deltaTime);

        sf::FloatRect getHitbox();

        bool isJumping=false;

    private:
        void setHeight(const float& y);

        float _offset;

        float timeFromJump;
};


