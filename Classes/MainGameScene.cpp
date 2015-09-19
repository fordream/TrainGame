//
//  MainGameScene.cpp
//  TrainGame
//
//  Created by KeigoOgawa on 9/17/15.
//
//

#include "MainGameScene.h"
#include "man.h"

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
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    man_count = 0;
    men = Vector<Sprite *>();
    door_open = false;
    walls = Vector<Node *>();
    score = 0;
//    passenger = Vector<man* >();


    Sprite *background = Sprite::create("ホームと線路セット.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(background, 0);

    sman = SpriteBatchNode::create("man_sarary.png");
    auto kid = SpriteBatchNode::create("子供.png");
    for (int i= 0; i < 10; i++) {
        man newMan = man(sman, kid, i, men);
        this->addChild(newMan.pas, 100);
        men.pushBack(newMan.pas);
        manOut[i] = newMan.out;
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


    doorimg0 = Sprite::create("ドア-4.png");
    doorimg1 = Sprite::create("ドア-4.png");
    doorimg2 = Sprite::create("ドア-4.png");
    doorimg3 = Sprite::create("ドア-4.png");

    doorimg0->setAnchorPoint(Vec2(0,0));
    doorimg1->setAnchorPoint(Vec2(0,0));
    doorimg2->setAnchorPoint(Vec2(0,0));
    doorimg3->setAnchorPoint(Vec2(0,0));

    doorimg0->setPosition(100,205);
    doorimg1->setPosition(135,205);
    doorimg2->setPosition(275,205);
    doorimg3->setPosition(310,205);

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
    wallback-> setPosition(80, 100);



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
    addChild(doorimg0);
    addChild(doorimg1);
    addChild(doorimg2);
    addChild(doorimg3);


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


    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this](){
        doors.at(0)->runAction(MoveTo::create(1.0f, Point(65,205)));
        doors.at(1)->runAction(MoveTo::create(1.0f, Point(170,205)));
        doors.at(2)->runAction(MoveTo::create(1.0f, Point(240,205)));
        doors.at(3)->runAction(MoveTo::create(1.0f, Point(345,205)));
        doorimg0->runAction(MoveTo::create(1.0f, Point(65,205)));
        doorimg1->runAction(MoveTo::create(1.0f, Point(170,205)));
        doorimg2->runAction(MoveTo::create(1.0f, Point(240,205)));
        doorimg3->runAction(MoveTo::create(1.0f, Point(345,205)));

        door_open = true;
    }), NULL));


    this->runAction(Sequence::create(DelayTime::create(8),CallFunc::create([this](){
        doors.at(0)->runAction(MoveTo::create(1.0f, Point(100,205)));
        doors.at(1)->runAction(MoveTo::create(1.0f, Point(135,205)));
        doors.at(2)->runAction(MoveTo::create(1.0f, Point(275,205)));
        doors.at(3)->runAction(MoveTo::create(1.0f, Point(310,205)));
        doorimg0->runAction(MoveTo::create(1.0f, Point(100,205)));
        doorimg1->runAction(MoveTo::create(1.0f, Point(135,205)));
        doorimg2->runAction(MoveTo::create(1.0f, Point(275,205)));
        doorimg3->runAction(MoveTo::create(1.0f, Point(310,205)));
        door_open = false;

        //score
        for (int i = 0; i < men.size(); ++i) {
            if(manOut[i] == 0 ) {
                //kid
                if(inGoodPosition0(men.at(i))) {
                    // 大人は外
                    score += 100;
                } else {
                    score -= 7;
                }
            } else {
                //man
                if(inGoodPosition1(men.at(i))) {
                    //子供は中
                    score += 100;
                } else {
                    score -= 10;
                }

            }
        }
        auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);

        label->setColor(ccc3(255, 0, 127));
        auto str = StringUtils::format("SCORE: %d", score);
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                origin.y + visibleSize.height/2));
        this->addChild(label, 1000);
        label->setString(str);

    }), NULL));

    bool flg = true;
//    if(flg){
//        //3秒後に移動してくる
//    for (int i = 10; i < 18; ++i) {
//        Vector<Sprite *> afterman;
//        auto manT = Sprite::createWithTexture(sman->getTexture());
//        manT->setScale(0.5f, 0.5f);
//        manT->setPosition(100, 200);
//        auto pMan = PhysicsBody::createCircle(10.0f);
//        pMan->setDynamic(true);
//        pMan->setRotationEnable(true);
//        manT->setPhysicsBody(pMan);
//        manOut[i+10] = 0;
//        afterman.pushBack(manT);
//        men.push
//        this->addChild(manT);
//        manT->runAction(move);
//    }
//    this->runAction(Sequence::create(DelayTime::create(3),CallFunc::create([this](){
//            MoveTo* move = MoveTo::create(2.0f, Point(0, -50));
//            // after man
//
//            for(Sprite *aman: afterman) {
//
//            }
//            // アクションの実行
//
//        }), NULL));


        //当たり判定をとって止める
        // if(当たり判定){
        //     flg = false;
        // }

//    }

    return true;
}

bool MainGameScene::onTouchBegan(Touch *touch, Event *unused_event) {

    touchedMan = nullptr;
    Point p = touch->getLocation();

    // door
    if(!door_open) {

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

bool MainGameScene::inGoodPosition0(cocos2d::Sprite *pSprite) {
    // 大人は外
    auto p = pSprite->getPosition();
    if(inTheTrain(p)) {
        return false;
    } else {
        return true;
    }
}

bool MainGameScene::inGoodPosition1(cocos2d::Sprite *pSprite) {
    // 子供は中
    auto p = pSprite->getPosition();
    if(inTheTrain(p)) {
        return true;
    } else {
        return false;
    }
}

bool MainGameScene::inTheTrain(const cocos2d::Vec2 vec2) {
    if (vec2.x >-25 && vec2.x <325 && vec2.y>100 && vec2.x <200) {
        return true;
    } else {
        return false;
    }
}
