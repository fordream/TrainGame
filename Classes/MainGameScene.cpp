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
    door_open = false;

    auto wallback = Sprite::create("箱.png");
    auto wall = Node::create();
//    wall->setContentSize(Size(576,160));
    Vec2 wallVec[6] = {
            Vec2(0,0),
            Vec2(-50/2,0),
            Vec2(-50/2,-200/2),
            Vec2(550/2,-200/2),
            Vec2(550/2,0),
            Vec2(500/2,0)
    };
    auto sukima = Node::create();
    Vec2 sukimaVec[2] = {
            Vec2(150/2,0),
            Vec2(350/2, 0)
    };
    wall->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec, 6,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    sukima->setPhysicsBody(
            PhysicsBody::createEdgeChain(sukimaVec, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );

    doors = Vector<Node *>();
    Vec2 doorVec[2] = {
            Vec2(0, 0),
            Vec2(75/2, 0)
    };
    for (int i = 0; i < 4; i++) {
        auto d = Node::create();
        d->setPhysicsBody(
                PhysicsBody::createEdgeChain(doorVec,2,
                        PhysicsMaterial(0.1f, 1.0f, 0.0f)
                )
        );
        doors.pushBack(d);
    }
    doors.at(0)->setPosition(100,205);
    doors.at(1)->setPosition(135,205);
    doors.at(2)->setPosition(275,205);
    doors.at(3)->setPosition(310,205);

    wall->setPosition(100, 200);
    sukima->setPosition(100,200);
    wallback-> setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(wall);
    addChild(wallback);
    addChild(sukima);
    addChild(doors.at(0));
    addChild(doors.at(1));
    addChild(doors.at(2));
    addChild(doors.at(3));

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
//    Point p = touch->getLocation();
////    if(ballExists(p)) {
////
////    } else {
//        auto man = Sprite::create("man_sarary.png");
//        man->setContentSize(Size(50, 50));
//        man->setPosition(p.x, p.y);
//        man->setTag(man_count);
//        man->setScale(0.5f);
//
////        men.pushBack(man);
////
//        auto pMan = PhysicsBody::createCircle(10.0f);
//        pMan->setDynamic(true);
//        pMan->setRotationEnable(true);
//        man->setPhysicsBody(pMan);
//        this->addChild(man);
////    }
    if(!door_open) {
        doors.at(0)->runAction(MoveTo::create(1.0f, Point(65,205)));
        doors.at(1)->runAction(MoveTo::create(1.0f, Point(170,205)));
        doors.at(2)->runAction(MoveTo::create(1.0f, Point(240,205)));
        doors.at(3)->runAction(MoveTo::create(1.0f, Point(345,205)));
        door_open = true;
    } else {
        doors.at(0)->runAction(MoveTo::create(1.0f, Point(100,205)));
        doors.at(1)->runAction(MoveTo::create(1.0f, Point(135,205)));
        doors.at(2)->runAction(MoveTo::create(1.0f, Point(275,205)));
        doors.at(3)->runAction(MoveTo::create(1.0f, Point(310,205)));
        door_open = false;
    }


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
