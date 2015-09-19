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
    world->setGravity(Vec2(0, 0));
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
    men = Vector<Sprite *>();
    door_open = false;
    walls = Vector<Node *>();

    Sprite *background = Sprite::create("ホームと線路セット.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(background, 0);

    auto man = SpriteBatchNode::create("man_sarary.png");
    for (int i= 0; i < 2; i++) {
        auto manT = Sprite::createWithTexture(man->getTexture());
        manT->setScale(0.5f, 0.5f);
        manT->setPosition(150+i*2, 125);
        auto pMan = PhysicsBody::createCircle(10.0f);
        pMan->setDynamic(true);
        pMan->setRotationEnable(true);
        manT->setPhysicsBody(pMan);
        this->addChild(manT, 100);
        men.pushBack(manT);
    }

    auto wall0 = Node::create();
    auto wall1 = Node::create();
    auto wall2 = Node::create();
    auto wall3 = Node::create();
    auto wall4 = Node::create();
    Vec2 wallVec0[2] = {
            Vec2(0,0),
            Vec2(-50/2, 0)
    };
    Vec2 wallVec1[2] = {
            Vec2(-50/2,0),
            Vec2(-50/2,-200/2)
    };
    Vec2 wallVec2[2] = {
            Vec2(-50/2,-200/2),
            Vec2(550/2,-200/2),
    };
    Vec2 wallVec3[2] = {
            Vec2(550/2,-200/2),
            Vec2(550/2,0),
    };
    Vec2 wallVec4[2] = {
            Vec2(550/2,0),
            Vec2(500/2,0)
    };
    wall0->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec0, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    wall1->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec1, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    wall2->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec2, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    wall3->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec3, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    wall4->setPhysicsBody(
            PhysicsBody::createEdgeChain(wallVec4, 2,
                    PhysicsMaterial(0.1f, 1.0f, 0.0f)
            )
    );
    auto sukima = Node::create();
    Vec2 sukimaVec[2] = {
            Vec2(150/2,0),
            Vec2(350/2, 0)
    };
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
        walls.pushBack(d);

    }
    walls.pushBack(wall0);
    walls.pushBack(wall1);
    walls.pushBack(wall2);
    walls.pushBack(wall3);
    walls.pushBack(wall4);
    walls.pushBack(sukima);

    doors.at(0)->setPosition(100,205);
    doors.at(1)->setPosition(135,205);
    doors.at(2)->setPosition(275,205);
    doors.at(3)->setPosition(310,205);

    wall0->setPosition(100, 200);
    wall1->setPosition(100, 200);
    wall2->setPosition(100, 200);
    wall3->setPosition(100, 200);
    wall4->setPosition(100, 200);

    sukima->setPosition(100,200);

    auto wallback = Sprite::create("箱-2.png");
    wallback->setAnchorPoint(Vec2(0,0));
    wallback-> setPosition(50,100);



    addChild(wall0);
    addChild(wall1);
    addChild(wall2);
    addChild(wall3);
    addChild(wall4);

    addChild(wallback,10);
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

//    this->addChild(man);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool MainGameScene::onTouchBegan(Touch *touch, Event *unused_event) {

    touchedMan = nullptr;
    Point p = touch->getLocation();

    // door
    if(!door_open) {
//        doors.at(0)->runAction(MoveTo::create(1.0f, Point(65,205)));
//        doors.at(1)->runAction(MoveTo::create(1.0f, Point(170,205)));
//        doors.at(2)->runAction(MoveTo::create(1.0f, Point(240,205)));
//        doors.at(3)->runAction(MoveTo::create(1.0f, Point(345,205)));
//        door_open = true;
    } else {
        doors.at(0)->runAction(MoveTo::create(1.0f, Point(100,205)));
        doors.at(1)->runAction(MoveTo::create(1.0f, Point(135,205)));
        doors.at(2)->runAction(MoveTo::create(1.0f, Point(275,205)));
        doors.at(3)->runAction(MoveTo::create(1.0f, Point(310,205)));
        door_open = false;
    }
    if(manExists(p)) {
        touchedMan = getMan(p);
        if (collisionWithWalls()) {

        }
    }
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


    return true;
}

void MainGameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    Point p = touch->getLocation();
    if(touchedMan != nullptr) {
        // 衝突したらTouchedManをnullにする
        if(collisionWithWalls()) {
            touchedMan = nullptr;

        } else {
            touchedMan->setPosition(p);
        }
    }
}

bool MainGameScene::onContactBegin(PhysicsContact& contact) {
    touchedMan = nullptr;
}

void MainGameScene::onTouchEnded(Touch *touch, Event *unused_event) {
}


bool MainGameScene::manExists(Point p) {
    return getMan(p) != nullptr;
}

Sprite *MainGameScene::getMan(Point p) {
    Sprite *target = nullptr;
    for(Sprite *man : men) {
        Rect manBox = man->getBoundingBox();
        if(manBox.containsPoint(p)) {
            target = man;
        }
    }
    return target;
}

bool MainGameScene::collisionWithWalls() {
//    for(Node *wall : walls) {
//        Rect wallBox = wall->getBoundingBox();
//        Rect manBox = touchedMan->getBoundingBox();
//        if(wallBox.intersectsRect(manBox)) {
//            return true;
//        }
//    }
    return false;
}
