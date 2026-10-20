// src/PauseMenuHook.cpp
#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "EchoMenu.hpp"

using namespace geode::prelude;
using namespace cocos2d; // <-- FIX: Brings CCSprite into scope

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = this->getChildByID("button-menu");
        if (!menu) return;

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), // Now works
            this,
            menu_selector(MyPauseLayer::onEchoButton)
        );
        menu->addChild(button);
    }

    void onEchoButton(CCObject*) {
        EchoMenu::get().setOpen(!EchoMenu::get().isOpen());
    }
};
