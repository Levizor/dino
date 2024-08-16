#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

class Dino:public sf::Sprite{
    public:
        Dino();
        void jump();
        void update(const float& deltaTime);

        sf::FloatRect getHitbox();
    private:
        void setHeight(const float& y);

        float _offset;

        float timeFromJump;
        bool isJumping=false;
        

};


