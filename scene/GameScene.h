#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "math.h"
#include "Player.h"
#include <memory>
#include "Enemy.h"
#include "SkyDome.h"
#include "RailCamera.h"
#include <sstream>
#include "GuidLine.h"

enum enemy {
    Octopus,	// 0
    Crab,		// 1
    Squid,		// 2
    UFO,		// 3
};

enum phase {
    Title,
    Game,
    End,
};

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
    GameScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    void PopEnemy(Vector3& pos, int indexEnemy);

    // 衝突判定と応答
    void CheckAllCollision();

    void LoadEnemyPopData();

    void UpdateEnemyPopCommands();

private: // メンバ変数
    DirectXCommon* dxCommon_ = nullptr;
    Input* input_ = nullptr;
    Audio* audio_ = nullptr;
    DebugText* debugText_ = nullptr;
    Model* model_ = nullptr;
    Model* playerModel_ = nullptr;
    Model* playerBulletModel_ = nullptr;
    Model* reticleModel_ = nullptr;
    Model* enemyOctopusModel_ = nullptr;
    Model* enemyCrabModel_ = nullptr;
    Model* enemySquidModel_ = nullptr;
    Model* enemyUFOModel_ = nullptr;
    DebugCamera* debugCamera_ = nullptr;
    bool isDebugCameraActive_ = false;

    //テクスチャハンドル
    uint32_t textureHandle_ = 0;
    uint32_t texUFOYellow_ = 0;

    uint32_t reticleHandle_ = 0;

    ViewProjection viewProjection_;
    ViewProjection debugViewProjection_;


    // スプライト
    Sprite* sprite_ = nullptr;
    std::unique_ptr<Sprite> titleSCORE_ = nullptr;
    std::unique_ptr<Sprite> titlePLAY_ = nullptr;
    std::unique_ptr<Sprite> titleSPACEINVADERS_ = nullptr;
    std::unique_ptr<Sprite> titleSCOREADVANCETABLE_ = nullptr;
    std::unique_ptr<Sprite> titleOCTOPUSPOINT_ = nullptr;
    std::unique_ptr<Sprite> titleCRABPOINT_ = nullptr;
    std::unique_ptr<Sprite> titleSQUIDPOINT_ = nullptr;
    std::unique_ptr<Sprite> titleUFOPOINT_ = nullptr;
    std::unique_ptr<Sprite> titleRIGHTCURSOR_ = nullptr;

    std::array<std::unique_ptr<Sprite>, 7> gameScoreNum_;
    std::unique_ptr<Sprite> endGAMEOVER_ = nullptr;
    std::unique_ptr<Sprite> endGAMEOVER2_ = nullptr;

    uint32_t texSCORE0 = 0;
    uint32_t texSCORE1 = 0;
    uint32_t texSCORE2 = 0;
    uint32_t texSCORE3 = 0;
    uint32_t texSCORE4 = 0;
    uint32_t texSCORE5 = 0;
    uint32_t texSCORE6 = 0;
    uint32_t texSCORE7 = 0;
    uint32_t texSCORE8 = 0;
    uint32_t texSCORE9 = 0;


    // 音
    uint8_t indexSound_ = 1;
    uint32_t eMoveSound1_ = 0;
    uint32_t eMoveSound2_ = 0;
    uint32_t eMoveSound3_ = 0;
    uint32_t eMoveSound4_ = 0;

    uint32_t time_ = 0;
    Vector3 velocity_ = { -2, 0, -4 };
    bool approach = false;

    int32_t enemyFireCoolTime_ = 80;
    bool isEnemyFire = false;

    // 敵発生コマンド
    std::stringstream enemyPosCommands_;
    bool isWaitEnemyPop_ = false;
    uint32_t waitTime_ = 0;

    // 判定ライン
    std::unique_ptr<GuidLine> guidLine_;

    std::unique_ptr<Player> player_;
    std::list<std::unique_ptr<Enemy>> enemys_;
    std::unique_ptr<Skydome> skydome_;
    std::unique_ptr<RailCamera> railCamera_;

    // 3Dモデル
    Model* modelSkyDome_ = nullptr;

    std::array<uint32_t, 7> indexScore_;
    uint32_t score_ = 0;
    bool isGameOver = false;
    uint32_t phase_ = 0;

    /// <summary>
    /// ゲームシーン用
    /// </summary>
};