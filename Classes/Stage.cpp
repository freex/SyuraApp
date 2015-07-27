//
//  Stage.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Stage.h"
USING_NS_CC;

/*  */
int ADD_ENEMY_RATE = 20;

Stage::Stage()
:_tiledMap(nullptr)
,_player(nullptr)
{
    
}
Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tiledMap);
    CC_SAFE_RELEASE_NULL(_player);
}

bool Stage::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    /* マップファイルからノードを作成 */
    auto map = TMXTiledMap::create("map/stage1.tmx");
    this->addChild(map);
    this->setTiledMap(map);
    
    /*　地形レイヤーを取得 */
    //    auto terrainLayer = map->getLayer("Tile");
    // オブジェクトレイヤーを取得する
    auto objectLayer = map->getLayer("Object");
    
    // マップのサイズ
    auto mapSize = map->getMapSize();
    for (int i = 0; i < mapSize.width; i++) {
        for (int j = 0; j < mapSize.height; j++) {
            auto coordinate = Vec2(i, j);
            //            this->addPhysicsBody(terrainLayer, coordinate);
            this->addPhysicsBodyTMX(objectLayer, coordinate);
            
        }
    }
    
    /* プレイヤーの設置 */
    auto player = Player::create();
    this->addChild(player);
    this->setPlayer(player);
    
    /* プレイヤーに画面を追従させる */
    winSize = Director::getInstance()->getWinSize();
    /*Rectは追従する範囲を決めている Rectは左下を原点としている*/
    
    this ->runAction(CustomFollow::create(player,Rect(0, 0, _tiledMap->getContentSize().width, _tiledMap->getContentSize().height) ));
    /* x軸だけ、y軸だけと指定をする場合　この場合だとマップの範囲が扱えない */
    //    CustomFollowType type = kCustomFollowNone;
    //    this ->runAction(CustomFollow::create(player,type));
    
    this->scheduleUpdate();
    
    return true;
}

/*
 *
 *
 */
Sprite* Stage::addPhysicsBodyTMX(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate){
    /*タイルのスプライトを取り出す*/
    auto sprite = layer -> getTileAt(coordinate);
    if(sprite){
        /* 剛体用のマテリアル */
        auto material = PhysicsMaterial();
        /* 引っかからないように摩擦をゼロに */
        material.friction = 0;
        /* 剛体を設置 */
        auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(),material);
        /* 剛体を固定する */
        physicsBody->setDynamic(false);
        /* 剛体をつけるSpriteのアンカーポイントを中心にする */
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        /* 剛体をSpriteに付ける */
        sprite->setPhysicsBody(physicsBody);
        return sprite;
    }
    return nullptr;
}

/*
 *敵をマップに配置
 *@return 配置した敵のSpriteクラスを返す
 *
 */
Sprite* Stage::addEnemy(){
    auto enemy = Enemy::create();
    Vec2  nowPos = _player->getPosition();
    /* 配置する場所を指定 */
    
    /* プレイヤーからある程度離れた位置に敵追加する */
    /* x軸のランダムな位置 */
    float enemyXPos = rand() % static_cast<int>(winSize.width);
    auto enemySize = enemy -> getContentSize();
    
    /* 敵の初期位置 */
    enemy->setPosition(Vec2(enemyXPos,winSize.height - enemySize.height/2.0 - 40));
    /* 速度の設定 */
    enemy->setSpeed((int)rand()%6);
    
    /* ステージに敵を追加 */
    this -> addChild(enemy);
    /* _enemyベクターに敵を追加する */
    _enemys.pushBack(enemy);
    
    return enemy;
}

void Stage::moveEnemys(){
    auto iterator = _enemys.begin();
    while (iterator != _enemys.end()) {
        Enemy* enemy = (Enemy*)(*iterator);
        
        /* 現在の敵の座標を取得 */
        Vec2 Epos = enemy->getPosition();
        /* 現在のプレイヤーの座標を取得する */
        Vec2 Ppos = _player->getPosition();
        
        /* プレイヤーとの座標の差をベクトルで取得 */
        Vec2 delta = Ppos - Epos;
        /* 角度を算出 */
        auto angle = atan2f(delta.y, delta.x);
        /* 動作量 */
        float enemyMoveX =  cosf(angle)*enemy->getSpeed();
        float enemyMoveY =  sinf(angle)*enemy->getSpeed();
        
        /* 新しい座標へセット */
        Vec2 newPosition = Vec2(enemy->getPositionX() + enemyMoveX, enemy->getPositionY() + enemyMoveY);
        
        /* マップの敵へ反映 */
        enemy->setPosition(newPosition);
        /* マップ外へ出ないように丸める */
        auto position = enemy->getPosition().getClampPoint(Vec2(0,0), this->getTiledMap()->getContentSize());
        enemy->setPosition(position);

        iterator++;
        
    }
    return;
    
}


void Stage::update(float dt)
{
    /* 敵の発生確率を設定 */
    int random = rand() % ADD_ENEMY_RATE;
    /* 20分の１の確率で敵を追加 */
    if(random == 0 ){
        this ->addEnemy();
    }
    /* 敵キャラの位置を更新 */
    moveEnemys();
    

    
    /* 敵とプレイヤーの当たり判定 */
    /* 修羅場エリアに入った時の処理 */
    /* 敵の削除 */
}