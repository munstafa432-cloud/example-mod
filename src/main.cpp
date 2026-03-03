#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        FLAlertLayer::create("Geode", "Success! Mod is working!", "OK Concord")->show();

        
        return true;
    }
};
