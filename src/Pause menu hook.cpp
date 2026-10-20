// Hooking into the Pause Menu
#include <Geode/modify/PauseLayer.hpp>
#include "EchoMenu.hpp"

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        // Add a button to the pause menu to open Echo
        auto menu = this->getChildByID("button-menu");
        if (!menu) return;

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), // placeholder icon
            this,
            menu_selector(MyPauseLayer::onEchoButton)
        );
        menu->addChild(button);
    }

    void onEchoButton(CCObject*) {
        EchoMenu::get().setOpen(true);
    }
};
