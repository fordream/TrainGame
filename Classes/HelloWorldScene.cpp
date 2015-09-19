#include "HelloWorldScene.h"
#include "MainGameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    Sprite *background = Sprite::create("分別_背景.png");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(background, 0);


    sprite = Sprite::create("分別_発車.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 1);

    auto startListener = EventListenerTouchOneByOne::create();
    startListener->onTouchBegan = [this](cocos2d::Touch *touch, cocos2d::Event* event)-> bool {
        Point p = touch->getLocation();
        Rect r = sprite->getBoundingBox();
        if(r.containsPoint(p)) {
            Director::getInstance()->replaceScene(MainGameScene::createScene());
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(startListener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
