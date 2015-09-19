//
//  MainGameScene.cpp
//  TrainGame
//
//  Created by KeigoOgawa on 9/17/15.
//
//

#include "MainGameScene.h"

using namespace cocos2d;

Scene* MainGameScene::createScene() {
	auto scene = Scene::createWithPhysics();
    PhysicsWorld* world = scene->getPhysicsWorld();
    world->setGravity(Vec2(0, -500));
    world->setSpeed(1.0f);
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = MainGameScene::create();
	scene->addChild(layer);
	
    return scene;
}

bool MainGameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    man_count = 0;
    men = Vector<SpriteBatchNode*>();

    auto wallback = Sprite::create("箱.png");
    auto wall = Node::create();
//    wall->setContentSize(Size(576,160));
    Vec2 wallVec[5] = {
            Vec2(0,100),
            Vec2(0,0),
            Vec2(0, 0),
            Vec2(0,0)
    };
    wall->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec, 5,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
//    wall->setPosition(,0);
    wall-> setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    wallback-> setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(wall);
    addChild(wallback);

    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 0.0f;

//    auto man = Sprite::create("man_sarary.png");
//    man->setContentSize(Size(100, 100));
//    man->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
//    man->setTag(man_count);
//    men.pushBack(man);
//
//        auto pMan = PhysicsBody::createCircle(10.0f);
//        pMan->setDynamic(true);
//        pMan->setRotationEnable(true);
//        man->setPhysicsBody(pMan);
//    this->addChild(man);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool MainGameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    Point p = touch->getLocation();
//    if(ballExists(p)) {
//
//    } else {
        auto man = Sprite::create("man_sarary.png");
        man->setContentSize(Size(50, 50));
        man->setPosition(p.x, p.y);
        man->setTag(man_count);
        man->setScale(0.5f);

//        men.pushBack(man);
//
        auto pMan = PhysicsBody::createCircle(10.0f);
        pMan->setDynamic(true);
        pMan->setRotationEnable(true);
        man->setPhysicsBody(pMan);
        this->addChild(man);
//    }

    return true;
}

void MainGameScene::onTouchMoved(Touch *touch, Event *unused_event) {
//    Point p = touch->getLocation();
//    if (ballExists(p)) {
//        auto ball = getBall(p);
//        auto pball = ball->getPhysicsBody();
//        pball->setEnable(false);
//        ball->setPosition(p.x, p.y);
//    }
}

void MainGameScene::onTouchEnded(Touch *touch, Event *unused_event) {
}


bool MainGameScene::ballExists(Point p) {
//    return getBall(p) != nullptr;
}

//Sprite *MainGameScene::getBall(Point p) {
//    Sprite *target = nullptr;
//    for(Sprite *ball : balls) {
//        Rect ballBox = ball->getBoundingBox();
//        if(ballBox.containsPoint(p)) {
//            target = ball;
//        }
//    }
//    return target;
//}
