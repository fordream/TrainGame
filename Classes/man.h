//
// Created by KeigoOgawa on 9/19/15.
//

#ifndef TRAINGAME_MAN_H
#define TRAINGAME_MAN_H


#include "MainGameScene.h"

class man {
private:
public:
    int out;
    cocos2d::Sprite *pas;
    man(cocos2d::SpriteBatchNode *sman, cocos2d::SpriteBatchNode *kid, int i, cocos2d::Vector<cocos2d::Sprite *> men);

};


#endif //TRAINGAME_MAN_H
