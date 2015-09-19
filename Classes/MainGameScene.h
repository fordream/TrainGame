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

class MainGameScene : public cocos2d::Layer
{
private:
    int man_count;
    cocos2d::Label * label;
    cocos2d::Vector<cocos2d::SpriteBatchNode *> men;
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(MainGameScene);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    cocos2d::Sprite *getBall(cocos2d::Point p);

    bool ballExists(cocos2d::Point p);
};

#endif /* defined(__TrainGame__MainGameScene__) */