//
//  ClearModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/02.
//
//

#ifndef __SyuraProject__ClearModal__
#define __SyuraProject__ClearModal__

#include <stdio.h>
#include "cocos2d.h"
#include "cocosGUI.h"
class ClearModal : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(ClearModal);
};


#endif /* defined(__SyuraProject__ClearModal__) */
