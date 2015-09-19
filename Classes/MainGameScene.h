//
//  MainGameScene.h
//  TrainGame
//
//  Created by KeigoOgawa on 9/17/15.
//
//

#ifndef __TrainGame__MainGameScene__
#define __TrainGame__MainGameScene__

#include "cocos2d.h"
#include "man.h"

class MainGameScene : public cocos2d::Layer
{
private:
    int man_count;
    cocos2d::Label * label;
    cocos2d::Vector<cocos2d::Sprite *> men;
    cocos2d::Vector<cocos2d::Node *> doors;
    bool door_open;
    cocos2d::Sprite *touchedMan;
    cocos2d::Vector<cocos2d::Node *>walls;
    cocos2d::Size visibleSize;
    cocos2d::Size winSize;
    cocos2d::Vec2 origin;
    int manOut[100];
    int score;
    cocos2d::Sprite * doorimg0;
    cocos2d::Sprite * doorimg1;
    cocos2d::Sprite * doorimg2;
    cocos2d::Sprite * doorimg3;
    cocos2d::SpriteBatchNode * sman;

public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(MainGameScene);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    cocos2d::Sprite *getMan(cocos2d::Point p);

    bool manExists(cocos2d::Point p);

    bool collisionWithWalls();

    bool onContactBegin(cocos2d::PhysicsContact &contact);


    bool inGoodPosition0(cocos2d::Sprite *pSprite);

    bool inGoodPosition1(cocos2d::Sprite *pSprite);

    bool inTheTrain(const cocos2d::Vec2 vec2);
};

#endif /* defined(__TrainGame__MainGameScene__) */