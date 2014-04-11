#include "HelloWorldScene.h"

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
    auto size = Director::getInstance()->getVisibleSize();
    
    auto label = Label::create();
    label->setString("Click Me, Boy!");
    label->setFontSize(28);
    label->setPosition(Point(size.width/2, size.height/2));
    addChild(label);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [label](Touch *touch, Event *event){
        if (label->cocos2d::Node::getBoundingBox().containsPoint(touch->getLocation())) {
//            MessageBox("Click Me", "Attention");
//            auto action = MoveBy::create(1, Point(100, 100));
//            auto action = Spawn::create(MoveBy::create(1, Point(100, 100)), RotateBy::create(1, 180, 180) , NULL);
            auto action = Sequence::create(
               MoveBy::create(1, Point(100, 100)),
               RotateBy::create(1, 180),
               CallFunc::create([](){
                    MessageBox("CallFun call... ...", "Attention");
                                            }),
                                           NULL);
            label->runAction(action);
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
