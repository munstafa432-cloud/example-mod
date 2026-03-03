#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto alert = FLAlertLayer::create(
            "Geode Mod", 
            "It worked! This is running on 32-bit Android!", 
            "OK"
        );
        alert->show();

        return true;
    }
};
