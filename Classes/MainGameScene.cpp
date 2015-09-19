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
    ball_count = 0;
    balls = Vector<Sprite*>();

    auto wall = Node::create();
    wall->setPhysicsBody(
            PhysicsBody::createEdgeBox(
                    Size(visibleSize.width, visibleSize.height),
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    wall-> setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(wall);

    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 0.0f;

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool MainGameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    Point p = touch->getLocation();
    if(ballExists(p)) {

    } else {
        auto ball = Sprite::create();
        ball->setPosition(p.x, p.y);
        ball->setColor(Color3B(255, 255, 0));
        ball->setTag(ball_count);
        balls.pushBack(ball);

        auto pBall = PhysicsBody::createCircle(10.0f);
        pBall->setDynamic(true);
        pBall->setRotationEnable(true);
        ball->setPhysicsBody(pBall);
        addChild(ball);
    }

    return true;
}

void MainGameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    Point p = touch->getLocation();
    if (ballExists(p)) {
        auto ball = getBall(p);
        auto pball = ball->getPhysicsBody();
        pball->setEnable(false);
        ball->setPosition(p.x, p.y);
    }
}

void MainGameScene::onTouchEnded(Touch *touch, Event *unused_event) {
}


bool MainGameScene::ballExists(Point p) {
    return getBall(p) != nullptr;
}

Sprite *MainGameScene::getBall(Point p) {
    Sprite *target = nullptr;
    for(Sprite *ball : balls) {
        Rect ballBox = ball->getBoundingBox();
        if(ballBox.containsPoint(p)) {
            target = ball;
        }
    }
    return target;
}
