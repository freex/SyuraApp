//
//  LoseModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/01.
//
//

#ifndef __SyuraProject__LoseModal__
#define __SyuraProject__LoseModal__

#include <stdio.h>
#include "cocos2d.h"
#include "cocosGUI.h"
class LoseModal : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(LoseModal);
};

#endif /* defined(__SyuraProject__LoseModal__) */
