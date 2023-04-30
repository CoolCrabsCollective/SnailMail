//
// Created by adrien on 29/04/23.
//

#include "world/Path.h"
#include "GameAssets.h"

Path::Path(wiz::AssetLoader &assets,
           GraphNode *node1,
           GraphNode *node2)
    : sprite(),
        slimeSprite(),
        node1(node1),
        node2(node2),
        slimes() {
    sf::Texture* pathTex = assets.get(GameAssets::PATH);
    sf::Texture* slimeTex = assets.get(GameAssets::CUM_PATH);
    pathTex->setRepeated(true);
    slimeTex->setRepeated(true);
    sprite.setTexture(*pathTex);
    slimeSprite.setTexture(*slimeTex);
}

void Path::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

    sf::Vector2f vec = node2->getPosition() - node1->getPosition();
    float dst = vec.length();

    sprite.setPosition(node1->getPosition());
    sprite.setOrigin({ 0.0f, 0.5f * sprite.getTexture()->getSize().y });
    sprite.setScale(sf::Vector2f(2.0f / sprite.getTexture()->getSize().x,
                                     1.0f / sprite.getTexture()->getSize().y));
    sprite.setRotation(vec.angle());
    int sizeY = sprite.getTexture()->getSize().y;
    sprite.setTextureRect(sf::IntRect({0, 0},
                                          {(int)round(dst / 2.0f * sprite.getTexture()->getSize().x), sizeY}));
    target.draw(sprite);

    for(const Slime& slime : slimes) {
        if(!slime.forward && slime.start != 0.0f || slime.end == 1.0f) {
            slimeSprite.setPosition(node2->getPosition() - vec * (1.0f - slime.end));
            slimeSprite.setOrigin({ 0.0f, 0.5f * slimeSprite.getTexture()->getSize().y });
            slimeSprite.setScale(sf::Vector2f(2.0f / slimeSprite.getTexture()->getSize().x,
                                              1.0f / slimeSprite.getTexture()->getSize().y));
            slimeSprite.setRotation((-vec).angle());
            int sizeY = slimeSprite.getTexture()->getSize().y;
            slimeSprite.setTextureRect(sf::IntRect({(int)round((dst * (1.0f - slime.end)) / 2.0f * slimeSprite.getTexture()->getSize().x), 0},
                                                   {(int)round((dst * (slime.end - slime.start)) / 2.0f * slimeSprite.getTexture()->getSize().x), sizeY}));
            slimeSprite.setColor({ slime.color.r, slime.color.g, slime.color.b, 250 });
            target.draw(slimeSprite);
        } else {
            slimeSprite.setPosition(node1->getPosition() + vec * slime.start);
            slimeSprite.setOrigin({ 0.0f, 0.5f * slimeSprite.getTexture()->getSize().y });
            slimeSprite.setScale(sf::Vector2f(2.0f / slimeSprite.getTexture()->getSize().x,
                                              1.0f / slimeSprite.getTexture()->getSize().y));
            slimeSprite.setRotation(vec.angle());
            int sizeY = slimeSprite.getTexture()->getSize().y;
            slimeSprite.setTextureRect(sf::IntRect({(int)round((dst * slime.start) / 2.0f * slimeSprite.getTexture()->getSize().x), 0},
                                                   {(int)round((dst * (slime.end - slime.start)) / 2.0f * slimeSprite.getTexture()->getSize().x), sizeY}));
            slimeSprite.setColor({ slime.color.r, slime.color.g, slime.color.b, 250 });
            target.draw(slimeSprite);
        }
    }
}


bool Path::isBlocked(GraphNode *enterNode, sf::Color color) const {
    if(enterNode != node1 && enterNode != node2)
        return false;

    for(const Slime& slime : slimes) {
        if(slime.color == color) {
            if(enterNode == node1) {
                if(slime.start == 0.0f)
                    return true;
            } else {
                if(slime.end == 1.0f)
                    return true;
            }
        }
    }

    return false;
}

void Path::addSlime(GraphNode* enterNode,
                    float position,
                    float previous,
                    sf::Color color) {
    if(enterNode != node1) {
        position = 1.0f - position;
        previous = 1.0f - previous;
    }

    bool found = false;
    for(int i = 0; i < slimes.size(); i++) {
        Slime& slime = slimes[i];
        if(slime.color == color) {
            if(previous > slime.end || previous < slime.start)
                continue; // not in

            if(enterNode == node1) {
                slime.end = std::max(slime.end, position);
            } else {
                slime.start = std::min(slime.start, position);
            }
            found = true;
        } else {
            if(position > slime.end || position < slime.start)
                continue; // not in

            if(enterNode == node1) {
                slime.start = std::max(slime.start, position);
            } else {
                slime.end = std::min(slime.end, position);
            }

            if(slime.start >= slime.end) {
                slimes.erase(slimes.begin() + i);
                i--;
            }
        }
    }

    if(!found) {
        Slime slime;
        slime.color = color;
        if(enterNode == node1) {
            slime.start = 0.0f;
            slime.end = position;
            slime.forward = true;
        } else {
            slime.end = 1.0f;
            slime.start = position;
            slime.forward = false;
        }

        slimes.push_back(slime);
    }
}
