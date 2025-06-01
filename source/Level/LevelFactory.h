#ifndef LEVEL_FACTORY_H
#define LEVEL_FACTORY_H

#include "Level1.h"
#include "Level2.h"
#include <memory>

class LevelFactory {
public:
    static std::unique_ptr<Level> createLevel(numberLevel num) {
        switch (num) {
            case numberLevel::L1: return std::make_unique<Level1>();
            case numberLevel::L2: return std::make_unique<Level2>();
            default: return nullptr;
        }
    }
};

#endif