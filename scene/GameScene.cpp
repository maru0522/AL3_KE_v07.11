#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
    delete model_;
    delete debugCamera_;
    delete modelSkyDome_;
    delete reticleModel_;
    delete enemyOctopusModel_;
    delete enemyCrabModel_;
    delete enemySquidModel_;
    delete enemyUFOModel_;
    delete playerModel_;
    delete playerBulletModel_;
}

void GameScene::Initialize() {

    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();
    audio_ = Audio::GetInstance();
    debugText_ = DebugText::GetInstance();
    model_ = Model::Create();
    reticleModel_ = Model::CreateFromOBJ("reticle2");
    enemyOctopusModel_ = Model::CreateFromOBJ("enemyOctopus");
    enemyCrabModel_ = Model::CreateFromOBJ("enemyCrab");
    enemySquidModel_ = Model::CreateFromOBJ("enemySquid");
    enemyUFOModel_ = Model::CreateFromOBJ("enemyUFO");
    playerModel_ = Model::CreateFromOBJ("player");
    playerBulletModel_ = Model::CreateFromOBJ("playerBullet");
    //ファイル名を指定してテクスチャを読み込む
    textureHandle_ = TextureManager::Load("Task1_2Resources/player.png");
    //texUFOYellow_ = TextureManager::Load("Task1_2Resources/enemyUFOYellow.png");

    // スプライト
    uint32_t texTitleSCORE = TextureManager::Load("Task1_2Resources/invaders/invadersSCORE.png");
    uint32_t texTitlePLAY = TextureManager::Load("Task1_2Resources/invaders/invadersPLAY.png");
    uint32_t texTitleSPACEINVADERS = TextureManager::Load("Task1_2Resources/invaders/invadersSPACEINVADERS.png");
    uint32_t texTitleSCOREADVANCETABLE = TextureManager::Load("Task1_2Resources/invaders/invadersSCOREADVANCETABLE.png");
    uint32_t texTitleOCTOPUS = TextureManager::Load("Task1_2Resources/invaders/invadersOCTOPUSPOINT.png");
    uint32_t texTitleCRAB = TextureManager::Load("Task1_2Resources/invaders/invadersCRABPOINT.png");
    uint32_t texTitleSQUID = TextureManager::Load("Task1_2Resources/invaders/invadersSQUIDPOINT.png");
    uint32_t texTitleUFO = TextureManager::Load("Task1_2Resources/invaders/invadersUFOPOINT.png");
    uint32_t texTitleRIGHTCURSOR = TextureManager::Load("Task1_2Resources/invaders/invadersRIGHTCURSOR.png");
    uint32_t texEndGAMEOVER = TextureManager::Load("Task1_2Resources/invaders/invadersGAMEOVER.png");
    uint32_t texEndGAMEOVER2 = TextureManager::Load("Task1_2Resources/invaders/invadersGAMEOVER2.png");

    texSCORE0 = TextureManager::Load("Task1_2Resources/invaders/invaders0.png");
    texSCORE1 = TextureManager::Load("Task1_2Resources/invaders/invaders1.png");
    texSCORE2 = TextureManager::Load("Task1_2Resources/invaders/invaders2.png");
    texSCORE3 = TextureManager::Load("Task1_2Resources/invaders/invaders3.png");
    texSCORE4 = TextureManager::Load("Task1_2Resources/invaders/invaders4.png");
    texSCORE5 = TextureManager::Load("Task1_2Resources/invaders/invaders5.png");
    texSCORE6 = TextureManager::Load("Task1_2Resources/invaders/invaders6.png");
    texSCORE7 = TextureManager::Load("Task1_2Resources/invaders/invaders7.png");
    texSCORE8 = TextureManager::Load("Task1_2Resources/invaders/invaders8.png");
    texSCORE9 = TextureManager::Load("Task1_2Resources/invaders/invaders9.png");

    titleSCORE_.reset(Sprite::Create(texTitleSCORE, { 350,100 }));
    titleSCORE_->SetSize({ 160,32 });
    titlePLAY_.reset(Sprite::Create(texTitlePLAY, { 550,200 }));
    titlePLAY_->SetSize({ 128,32 });
    titleSPACEINVADERS_.reset(Sprite::Create(texTitleSPACEINVADERS, { 400,275 }));
    titleSPACEINVADERS_->SetSize({ 448,32 });
    titleSCOREADVANCETABLE_.reset(Sprite::Create(texTitleSCOREADVANCETABLE, { 300,350 }));
    titleSCOREADVANCETABLE_->SetSize({ 672,32 });

    titleUFOPOINT_.reset(Sprite::Create(texTitleUFO, { 475,450 }));
    titleUFOPOINT_->SetSize({ 352, 32 });
    titleSQUIDPOINT_.reset(Sprite::Create(texTitleSQUID, { 475,500 }));
    titleSQUIDPOINT_->SetSize({ 352, 32 });
    titleCRABPOINT_.reset(Sprite::Create(texTitleCRAB, { 475,550 }));
    titleCRABPOINT_->SetSize({ 352, 32 });
    titleOCTOPUSPOINT_.reset(Sprite::Create(texTitleOCTOPUS, { 475,600 }));
    titleOCTOPUSPOINT_->SetSize({ 352, 32 });

    titleRIGHTCURSOR_.reset(Sprite::Create(texTitleRIGHTCURSOR, { 500,200 }));
    titleRIGHTCURSOR_->SetSize({ 32,32 });

    for (int i = 0; i < 7; i++) {
        gameScoreNum_[i].reset(Sprite::Create(texSCORE0, { 328.0f + 25.0f * i,135 }));
        gameScoreNum_[i]->SetSize({ 32,32 });
    }

    endGAMEOVER_.reset(Sprite::Create(texEndGAMEOVER, { 380,275 }));
    endGAMEOVER2_.reset(Sprite::Create(texEndGAMEOVER2, { 380,400 }));

    // 音
    eMoveSound1_ = audio_->LoadWave("Task1_2Resources/sounds/fastinvader1.wav");
    eMoveSound2_ = audio_->LoadWave("Task1_2Resources/sounds/fastinvader2.wav");
    eMoveSound3_ = audio_->LoadWave("Task1_2Resources/sounds/fastinvader3.wav");
    eMoveSound4_ = audio_->LoadWave("Task1_2Resources/sounds/fastinvader4.wav");

    // レティクルのテクスチャ
    TextureManager::Load("Task1_2Resources/reticle.jpg");

    //デバックカメラの生成
    debugCamera_ = new DebugCamera(1280, 720);

    viewProjection_.Initialize();

    //軸方向表示の有効化
    AxisIndicator::GetInstance()->SetVisible(false);
    //軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
    AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
    //ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
    PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

    // レールカメラの生成
    railCamera_ = std::make_unique<RailCamera>();
    Vector3 pos(0, 10, -30);
    Vector3 rad(0.2617, 0, 0);
    // レールカメラの初期化
    railCamera_->Initialize(pos, rad);

    // 自キャラの生成
    player_ = std::make_unique<Player>();
    // 自キャラの初期化
    player_->Initialize(playerModel_, reticleModel_, playerBulletModel_);
    //player_->SetParent(railCamera_->GetWorldTransform());

    guidLine_ = std::make_unique<GuidLine>();
    guidLine_->Initialize(playerBulletModel_);

    // 最初の敵の配置初期化
    int32_t i = 0;
    for (int32_t y = 0; y < 5; y++) {
        for (int32_t x = 0; x < 9; x++) {
            Vector3 pos(-21 + 6 * x, -5, 8 * y + 50);
            if (y < 2) {
                PopEnemy(pos, Octopus);
            }
            else if (2 <= y && y < 4) {
                PopEnemy(pos, Crab);
            }
            else if (4 <= y) {
                PopEnemy(pos, Squid);
            }
            i++;
        }
    }


    // 敵の生成コマンドの読み込み
    LoadEnemyPopData();

    // 3Dモデルの生成
    modelSkyDome_ = Model::CreateFromOBJ("skydome", true);

    // 天球の生成
    skydome_ = std::make_unique<Skydome>();
    // 天球の初期化
    skydome_->Initialize(modelSkyDome_);
    skydome_->SetParent(railCamera_->GetWorldTransform());
}

void GameScene::Update() {

    uint32_t scoreCopy = score_;
    for (int i = 0; i < 7; i++) {
        int num = pow(10, 7 - i - 1);
        indexScore_[i] = scoreCopy / num;
        scoreCopy = scoreCopy % num;
    }

    for (int i = 0; i < 7; i++) {
        if (indexScore_[i] == 0) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE0, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 1) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE1, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 2) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE2, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 3) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE3, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 4) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE4, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 5) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE5, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 6) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE6, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 7) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE7, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 8) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE8, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }
        else if (indexScore_[i] == 9) {
            gameScoreNum_[i].reset(Sprite::Create(texSCORE9, { 328.0f + 25.0f * i,135 }));
            gameScoreNum_[i]->SetSize({ 32,32 });
        }

    }

    if (phase_ == Title) {
        if (input_->TriggerKey(DIK_SPACE)) {
            phase_ = Game;
        }
    }
    else if (phase_ == Game) {
        // 自キャラの更新
        player_->Update();

        if (player_->isDead_ == true) {
            isGameOver = true;
        }

        guidLine_->Update();

        /*if (phase == 1) {
            UpdateEnemyPopCommands();
        }*/

        // 敵の更新
        // デスフラグの立った敵を削除
        enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->isDead(); });

        // 敵更新
        float left = 0, right = 0;
        for (std::unique_ptr<Enemy>& enemy : enemys_) {
            Vector3 pos = enemy->GetPosition();
            if (time_ % 120 == 0) {
                if (pos.x < left) {
                    left = pos.x;
                }
                if (pos.x > right) {
                    right = pos.x;
                }
            }
            if (approach) {
                Vector3 newPos = { pos.x, pos.y, pos.z + velocity_.z };
                enemy->SetWorldPosition(newPos);
            }

            // 敵移動
            if (time_ % 120 == static_cast<uint32_t>(pos.z + 10)) {

                Vector3 newPos = { pos.x + velocity_.x, pos.y, pos.z };
                enemy->SetWorldPosition(newPos);
            }
            enemy->Update();
            if (enemy->GetPosition().z <= 7) {
                isGameOver = true;
            }

            if (isGameOver) {
                phase_ = End;
            }
        }

        if (time_ % 120 == 60) {
            if (indexSound_ == 1) {
                audio_->PlayWave(eMoveSound1_, false, 0.02);
                indexSound_ = 2;
            }
            else if (indexSound_ == 2) {
                audio_->PlayWave(eMoveSound2_, false, 0.02);
                indexSound_ = 3;
            }
            else if (indexSound_ == 3) {
                audio_->PlayWave(eMoveSound3_, false, 0.02);
                indexSound_ = 4;
            }
            else if (indexSound_ == 4) {
                audio_->PlayWave(eMoveSound4_, false, 0.02);
                indexSound_ = 1;
            }
        }

        approach = false;

        if (time_ % 120 == 0) {
            if (left <= -30 && velocity_.x < 0 || right >= 30 && velocity_.x > 0) {
                velocity_.x = -velocity_.x;
                approach = true;
            }
        }

        /*if (time_%60 == 0) {
            Enemy* lineFront[9];
            Vector2* rowCol;
            int x, y;
            for (std::unique_ptr<Enemy>& enemy : enemys_) {
                rowCol = enemy->GetRowCol();
                x = rowCol->y;
                y = rowCol->x;
                if ( lineFront[x] != nullptr || lineFront[x]->GetPosition().y < enemy->GetPosition().y) {
                    lineFront[x] = enemy.get();
                }
            }
            for (int i = 0; i < 9; i++) {
                if (lineFront[x] != nullptr) {
                    lineFront[x]->Fire();
                }
            }
        }*/

        //debugText_->SetPos(50, 100);
        //debugText_->Printf("isEnemyFire:%d", isEnemyFire);

        isEnemyFire = false;

        // 天球の更新
        skydome_->Update();
        // レールカメラの更新
        railCamera_->Update();

        CheckAllCollision();

#ifdef _DEBUG
        if (input_->TriggerKey(DIK_C)) {
            if (isDebugCameraActive_) {
                isDebugCameraActive_ = false;
            }
            else {
                isDebugCameraActive_ = true;
            }
        }

        // カメラの処理
        if (isDebugCameraActive_) {
            //デバックカメラの更新
            debugCamera_->Update();
            debugViewProjection_ = debugCamera_->GetViewProjection();
            viewProjection_.matView = debugViewProjection_.matView;
            viewProjection_.matProjection = debugViewProjection_.matProjection;
        }
        else {
            viewProjection_.UpdateMatrix();
        }
#endif

        time_++;
    }
    else if (phase_ == End) {
        if (input_->TriggerKey(DIK_SPACE)) {
            phase_ = Title;
            viewProjection_.Initialize();
            Vector3 pos(0, 10, -30);
            Vector3 rad(0.2617, 0, 0);
            // レールカメラの初期化
            railCamera_->Initialize(pos, rad);
            // 自キャラの初期化
            player_->Initialize(playerModel_, reticleModel_, playerBulletModel_);
            guidLine_->Initialize(playerBulletModel_);

            for (std::unique_ptr<Enemy>& enemy : enemys_) {
                enemy->SetIsDead();
            }
            enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->isDead(); });

            // 最初の敵の配置初期化
            int32_t i = 0;
            for (int32_t y = 0; y < 5; y++) {
                for (int32_t x = 0; x < 9; x++) {
                    Vector3 pos(-21 + 6 * x, -5, 8 * y + 50);
                    if (y < 2) {
                        PopEnemy(pos, Octopus);
                    }
                    else if (2 <= y && y < 4) {
                        PopEnemy(pos, Crab);
                    }
                    else if (4 <= y) {
                        PopEnemy(pos, Squid);
                    }
                    i++;
                }
            }

            score_ = 0;
            velocity_ = { -2, 0, -4 };
            indexSound_ = 1;
            //texSCORE0 = 0;
            //texSCORE1 = 0;
            //texSCORE2 = 0;
            //texSCORE3 = 0;
            //texSCORE4 = 0;
            //texSCORE5 = 0;
            //texSCORE6 = 0;
            //texSCORE7 = 0;
            //texSCORE8 = 0;
            //texSCORE9 = 0;
            approach = false;
            enemyFireCoolTime_ = 80;
            isGameOver = false;
        }
    }
}

void GameScene::Draw() {

    // コマンドリストの取得
    ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
    // 背景スプライト描画前処理
    Sprite::PreDraw(commandList);

    /// <summary>
    /// ここに背景スプライトの描画処理を追加できる
    /// </summary>

    // スプライト描画後処理
    Sprite::PostDraw();
    // 深度バッファクリア
    dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
    // 3Dオブジェクト描画前処理
    Model::PreDraw(commandList);

    /// <summary>
    /// ここに3Dオブジェクトの描画処理を追加できる
    /// </summary>
    ////3Dモデルの描画
    // model_->Draw(worldTransform_,viewProjection_,textureHandle_);
    ////モデルと連動させるカメラの描画
     //model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

    // 天球の描画
    skydome_->Draw(railCamera_->GetViewProjection());

    if (phase_ == Title) {

    }
    else if (phase_ == Game) {
        // 自キャラの描画
        player_->Draw(railCamera_->GetViewProjection());

        guidLine_->Draw(railCamera_->GetViewProjection());

        // 敵の描画
        for (std::unique_ptr<Enemy>& enemy : enemys_) {
            enemy->Draw(railCamera_->GetViewProjection());
        }
    }
    else if (phase_ == End) {

    }

    //ラインの描画

    // 3Dオブジェクト描画後処理
    Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
    // 前景スプライト描画前処理
    Sprite::PreDraw(commandList);

    /// <summary>
    /// ここに前景スプライトの描画処理を追加できる
    /// </summary>

    titleSCORE_->Draw();
    for (int i = 0; i < 7; i++) {
        gameScoreNum_[i]->Draw();
    }
    if (phase_ == Title) {
        titlePLAY_->Draw();
        titleSPACEINVADERS_->Draw();
        titleSCOREADVANCETABLE_->Draw();
        titleOCTOPUSPOINT_->Draw();
        titleCRABPOINT_->Draw();
        titleSQUIDPOINT_->Draw();
        titleUFOPOINT_->Draw();

        titleRIGHTCURSOR_->Draw();
    }
    if (phase_ == End) {
        endGAMEOVER_->Draw();
        endGAMEOVER2_->Draw();
    }


    // デバッグテキストの描画
    debugText_->DrawAll(commandList);
    //
    // スプライト描画後処理
    Sprite::PostDraw();

#pragma endregion
}

void GameScene::PopEnemy(Vector3& pos, int indexEnemy)
{
    // 敵の生成
    std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
    // 敵の初期化
    switch (indexEnemy) {
        case Octopus:
            newEnemy->Initialize(enemyOctopusModel_, pos, 10);
            break;
        case Crab:
            newEnemy->Initialize(enemyCrabModel_, pos, 20);
            break;
        case Squid:
            newEnemy->Initialize(enemySquidModel_, pos, 30);
            break;
        case UFO:
            newEnemy->Initialize(enemyUFOModel_, pos, 300);
            break;
        default:
            newEnemy->Initialize(enemyOctopusModel_, pos, 10);
            break;
    }
    newEnemy->SetPlayer(player_.get());
    //newEnemy->SetParent(railCamera_->GetWorldTransform());
    // 敵の登録
    enemys_.push_back(std::move(newEnemy));
}

void GameScene::CheckAllCollision()
{
    // 判定対象AとBの座標
    Vector3 posA, posB;

    // 自弾リストの取得
    const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

    // 自キャラ半径
    const double pR = 1;

    // 敵キャラ半径
    const double eR = 1;

    // 自弾半径
    const double pBR = 1;

    // 敵弾半径
    const double eBR = 1;
#pragma region 自キャラと敵弾の当たり判定
    // 自キャラの座標
    posA = player_->GetWorldPosition();

    // 敵弾リストの取得
    for (std::unique_ptr<Enemy>& enemy : enemys_) {
        const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
        // 自キャラと敵弾すべての当たり判定
        for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
            // 敵弾の座標
            posB = bullet->GetWorldPosition();

            // 座標AとBの距離を求める
            double diffPosAB =
                std::pow(posB.x - posA.x, 2) +
                std::pow(posB.y - posA.y, 2) +
                std::pow(posB.z - posA.z, 2);

            // 球と球の交差判定
            if (diffPosAB <= std::pow(pR + eBR, 2)) {
                // 自キャラの衝突時コールバックを呼び出す
                player_->OnCollision();
                // 敵弾の衝突時コールバックを呼び出す
                bullet->OnCollision();
            }
        }
    }
#pragma endregion

#pragma region 敵キャラと自弾の当たり判定
    for (std::unique_ptr<Enemy>& enemy : enemys_) {
        // 敵キャラの座標
        posA = enemy->GetWorldPosition();

        // 敵キャラと自弾すべての当たり判定
        for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
            // 自弾の座標
            posB = bullet->GetWorldPosition();

            // 座標AとBの距離を求める
            double diffPosAB =
                std::pow(posB.x - posA.x, 2) +
                std::pow(posB.y - posA.y, 2) +
                std::pow(posB.z - posA.z, 2);

            // 球と球の交差判定
            if (diffPosAB <= std::pow(eR + pBR, 2)) {
                // 自弾弾の衝突時コールバックを呼び出す
                bullet->OnCollision();
                // 敵キャラの衝突時コールバックを呼び出す
                enemy->OnCollision();
                score_ += enemy->GetPoint();

            }
        }
    }
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
    for (std::unique_ptr<Enemy>& enemy : enemys_) {
        // 敵弾リストの取得
        const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
        // 自弾全てと敵弾すべての当たり判定
        for (const std::unique_ptr<PlayerBullet>& pBullet : playerBullets) {
            for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets) {
                // 自弾の座標
                posA = pBullet->GetWorldPosition();

                // 敵弾の座標
                posB = eBullet->GetWorldPosition();

                // 座標AとBの距離を求める
                double diffPosAB =
                    std::pow(posB.x - posA.x, 2) +
                    std::pow(posB.y - posA.y, 2) +
                    std::pow(posB.z - posA.z, 2);

                // 球と球の交差判定
                if (diffPosAB <= std::pow(pBR + eBR, 2)) {
                    // 自キャラの衝突時コールバックを呼び出す
                    pBullet->OnCollision();
                    // 敵弾の衝突時コールバックを呼び出す
                    eBullet->OnCollision();
                }
            }
        }
    }
#pragma endregion
}

void GameScene::LoadEnemyPopData()
{
    // ファイルを開く
    std::ifstream file;
    file.open("Resources/Task1_2Resources/enemyPos.csv");
    assert(file.is_open());

    // ファイルの内容を文字列ストリームにコピー
    enemyPosCommands_ << file.rdbuf();

    // ファイルを閉じる
    file.close();
}

void GameScene::UpdateEnemyPopCommands()
{
    // 待機処理
    if (isWaitEnemyPop_) {
        waitTime_--;
        if (waitTime_ <= 0) {
            // 待機完了
            isWaitEnemyPop_ = false;
        }
        return;
    }

    // 1行分の文字列を入れる変数
    std::string line;

    // コマンド実行ループ
    while (std::getline(enemyPosCommands_, line)) {
        // 1行分の文字列をストリームに変換して解析しやすくする
        std::istringstream line_stream(line);

        std::string word;
        // ,区切りで行の先頭文字列を取得
        std::getline(line_stream, word, ',');

        // "//"から始まる行はコメント
        if (word.find("//") == 0) {
            // コメント行を飛ばす
            continue;
        }

        // POPコマンド
        if (word.find("POP") == 0) {
            // x座標
            std::getline(line_stream, word, ',');
            float x = static_cast<float>(std::atof(word.c_str()));

            // y座標
            std::getline(line_stream, word, ',');
            float y = static_cast<float>(std::atof(word.c_str()));

            // z座標
            std::getline(line_stream, word, ',');
            float z = static_cast<float>(std::atof(word.c_str()));

            Vector3 pos(x, y, z);

            // 敵を発生させる
            Vector2 yx(0, 0);
            PopEnemy(pos, Octopus);
        }
        // WAITコマンド
        else if (word.find("WAIT") == 0) {
            std::getline(line_stream, word, ',');

            // 待ち時間
            int32_t waitTime = atoi(word.c_str());

            // 待機開始
            isWaitEnemyPop_ = true;
            waitTime_ = waitTime;

            // コマンドループを抜ける
            break;
        }
    }
}
