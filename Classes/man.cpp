//
// Created by KeigoOgawa on 9/19/15.
//

#include "man.h"
#include "MainGameScene.h"

using namespace cocos2d;

man::man(SpriteBatchNode * sman, SpriteBatchNode * kid, int i, cocos2d::Vector<cocos2d::Sprite *> men) {
    this->out = (int)(rand() %2);
    if (this->out == 0) {
        auto manT = Sprite::createWithTexture(sman->getTexture());
        manT->setScale(0.5f, 0.5f);
        manT->setPosition(150 + i * 2, 125);
        auto pMan = PhysicsBody::createCircle(10.0f);
        pMan->setDynamic(true);
        pMan->setRotationEnable(true);
        manT->setPhysicsBody(pMan);
        this->pas = manT;
    } else {
        auto kidT = Sprite::createWithTexture(kid->getTexture());
        kidT->setScale(0.5f, 0.5f);
        kidT->setPosition(150 + i * 2, 125);
        auto pMan = PhysicsBody::createCircle(10.0f);
        pMan->setDynamic(true);
        pMan->setRotationEnable(true);
        kidT->setPhysicsBody(pMan);
        this->pas = kidT;
    }
}
#include "man.h"
