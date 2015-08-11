//
//  SyuraEnemy.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__SyuraEnemy__
#define __SyuraProject__SyuraEnemy__

#include <stdio.h>
#include "cocos2d.h"
#include "Enemy.h"

class SyuraEnemy :public Enemy{
protected:
    SyuraEnemy();
    virtual ~SyuraEnemy();
public:
    
    bool init() override;
    void update(float dt) override;
    CREATE_FUNC(SyuraEnemy);
    
    bool setSyuraBody();
};




#endif /* defined(__SyuraProject__SyuraEnemy__) */
