#include "GamePCH.h"

#include "Events/GameEventTypes.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"
#include "Game/ImguiManager.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/SceneManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/PlayerController.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "SceneSample/SceneSample.h"
#include "Audio/SoundPlayer.h"
#include "Audio/SoundCue.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/HudScene.h"
#include "../Scenes/MainGameScene.h"
#include "../Scenes/OptionsMenuScene.h"
#include "../Scenes/PauseMenu.h"
#include "../Scenes/TitleScene.h"
#include "../Scenes/GunScene.h"

Game::Game(Framework* pFramework)
: GameCore( pFramework, new EventManager() )
{
    m_pImGuiManager = nullptr;
    m_bDrawImGui = false;

    m_pResources = nullptr;

    m_SoundPlayer = nullptr;         

    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = nullptr;
    }

}

Game::~Game()
{
    delete m_pSceneManager;

    for( int i=0; i<4; i++ )
    {
        delete m_pControllers[i];
    }

    delete m_SoundPlayer;

    delete m_pResources;

    delete m_pImGuiManager;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport( 0, 0, width, height );
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval( 1 );
#endif

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Enable back-face culling.
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CW );

    // Create our resource manager.
    m_pResources = new ResourceManager();

    // Create our meshes.
    {
        m_pResources->AddMesh( "Box", new Mesh() )->CreateBox( vec2(1,1), vec2(0,0) );
        m_pResources->AddMesh("Plane", new Mesh())->CreatePlane(vec2(10.0f, 10.0f), ivec2(5, 5), vec2(5.0f, 5.0f));
        m_pResources->AddMesh("Cube", new Mesh())->CreateOBJ("Data/OBJs/cube.obj", vec3(0.5f));
        m_pResources->AddMesh("Sphere", new Mesh())->CreateOBJ("Data/OBJs/UnitSphere.obj", vec3(1.0f));
        m_pResources->AddMesh("Handgun", new Mesh())->CreateOBJ("Data/OBJs/Colt_Tris.obj", vec3(1.0f));
        m_pResources->AddMesh("Cylinder", new Mesh())->CreateOBJ("Data/OBJs/Cylinder.obj", vec3(1.0f));
    }

    // Create our shaders.
    {
        m_pResources->AddShader("TextureUnlit", new ShaderProgram("Data/Shaders/TextureUnlit.vert", "Data/Shaders/TextureUnlit.frag"));
        m_pResources->AddShader( "Texture", new ShaderProgram( "Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag" ) );
        m_pResources->AddShader("Color", new ShaderProgram("Data/Shaders/Color.vert", "Data/Shaders/Color.frag"));
        m_pResources->AddShader("FlatColor", new ShaderProgram("Data/Shaders/Color.vert", "Data/Shaders/FlatColor.frag"));
        m_pResources->AddShader("CubeMap", new ShaderProgram("Data/Shaders/CubeMap.vert", "Data/Shaders/CubeMap.frag"));
        m_pResources->AddShader("TextureUnlitTint", new ShaderProgram("Data/Shaders/TextureUnlitTint.vert", "Data/Shaders/TextureUnlitTint.frag"));
        m_pResources->AddShader("TextureUnlitTintOnMask", new ShaderProgram("Data/Shaders/TextureUnlitTintOnMask.vert", "Data/Shaders/TextureUnlitTintOnMask.frag"));
    }

    // Load some textures.
    {
        m_pResources->AddTexture( "Megaman", new Texture( "Data/Textures/Megaman.png" ) );
        m_pResources->AddTexture( "Handgun", new Texture("Data/Textures/Colt/diffuse.png") );
        m_pResources->AddTexture( "Eye", new Texture("Data/Textures/EyeTexture.png") );
        m_pResources->AddTexture("StartGameButton", new Texture("Data/Textures/UI/StartGameButton.png"));
        m_pResources->AddTexture("BackButton", new Texture("Data/Textures/UI/BackButton.png"));
        m_pResources->AddTexture("ExitGameButton", new Texture("Data/Textures/UI/ExitGameButton.png"));
        m_pResources->AddTexture("OptionsButton", new Texture("Data/Textures/UI/OptionsButton.png"));
        m_pResources->AddTexture("QuitToMainMenuButton", new Texture("Data/Textures/UI/QuitToMainMenuButton.png"));
        m_pResources->AddTexture("RestartGameButton", new Texture("Data/Textures/UI/RestartGameButton.png"));
        m_pResources->AddTexture("FullBG", new Texture("Data/Textures/UI/FullBG.png"));
        m_pResources->AddTexture("OverlayBG", new Texture("Data/Textures/UI/OverlayBG.png"));
        m_pResources->AddTexture("Health", new Texture("Data/Textures/UI/Health.png"));
        m_pResources->AddTexture("Aim", new Texture("Data/Textures/UI/Aim.png"));
        m_pResources->AddTexture("EasyButton", new Texture("Data/Textures/UI/EasyButton.png"));
        m_pResources->AddTexture("MediumButton", new Texture("Data/Textures/UI/MediumButton.png"));
        m_pResources->AddTexture("HardButton", new Texture("Data/Textures/UI/HardButton.png"));
        m_pResources->AddTexture("WelpButton", new Texture("Data/Textures/UI/WelpButton.png"));
        m_pResources->AddTexture("StoneWall", new Texture("Data/Textures/StoneWall.png"));
        m_pResources->AddTexture("PlyWood", new Texture("Data/Textures/PlyWood.png"));

        /*
        const char* cubePath[6] = 
        {
            "Data/Textures/TestCubemap/posx.png",
            "Data/Textures/TestCubemap/negx.png",
            "Data/Textures/TestCubemap/posy.png",
            "Data/Textures/TestCubemap/negy.png",
            "Data/Textures/TestCubemap/posz.png",
            "Data/Textures/TestCubemap/negz.png"
        };
        /*/
        const char* cubePath[6] =
        {
            "Data/Textures/Yokohama2/posx.png",
            "Data/Textures/Yokohama2/negx.png",
            "Data/Textures/Yokohama2/posy.png",
            "Data/Textures/Yokohama2/negy.png",
            "Data/Textures/Yokohama2/posz.png",
            "Data/Textures/Yokohama2/negz.png"
        };
        //*/
        m_pResources->AddTexture("CubeMap", new Texture(cubePath));
    }

    // Create some materials.
    {
        m_pResources->AddMaterial( "Megaman", new Material( m_pResources->GetShader( "Texture" ), m_pResources->GetTexture( "Megaman" ) ) );
        m_pResources->AddMaterial("Color", new Material(m_pResources->GetShader("Color"), nullptr));
        m_pResources->AddMaterial("FlatColor", new Material(m_pResources->GetShader("FlatColor"), nullptr));
        m_pResources->AddMaterial("Handgun", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Handgun")));
        //UI MATERIALS
        m_pResources->AddMaterial("StartGameButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("StartGameButton")));
        m_pResources->AddMaterial("BackButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("BackButton")));
        m_pResources->AddMaterial("ExitGameButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("ExitGameButton")));
        m_pResources->AddMaterial("OptionsButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("OptionsButton")));
        m_pResources->AddMaterial("QuitToMainMenuButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("QuitToMainMenuButton")));
        m_pResources->AddMaterial("RestartGameButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("RestartGameButton")));
        m_pResources->AddMaterial("EasyButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("EasyButton")));
        m_pResources->AddMaterial("MediumButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("MediumButton")));
        m_pResources->AddMaterial("HardButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("HardButton")));
        m_pResources->AddMaterial("WelpButton", new Material(m_pResources->GetShader("TextureUnlitTint"), m_pResources->GetTexture("WelpButton")));
        m_pResources->AddMaterial("FullBG", new Material(m_pResources->GetShader("TextureUnlit"), m_pResources->GetTexture("FullBG")));
        m_pResources->AddMaterial("OverlayBG", new Material(m_pResources->GetShader("TextureUnlit"), m_pResources->GetTexture("OverlayBG")));
        m_pResources->AddMaterial("Health", new Material(m_pResources->GetShader("TextureUnlitTintOnMask"), m_pResources->GetTexture("Health")));
        m_pResources->AddMaterial("Aim", new Material(m_pResources->GetShader("TextureUnlit"), m_pResources->GetTexture("Aim")));
        //UI MATERIALS END
        m_pResources->AddMaterial("Eye", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Eye")));
        m_pResources->AddMaterial("CubeMap", new Material(m_pResources->GetShader("CubeMap"), m_pResources->GetTexture("Eye"), m_pResources->GetTexture("CubeMap")));
        m_pResources->AddMaterial("StoneWall", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("StoneWall")));
        m_pResources->AddMaterial("PlyWood", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("PlyWood")));
    }

    // Create our controllers.
    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = new PlayerController(GetEventManager());
    }

    //Create the Sound Player
    m_SoundPlayer = new SoundPlayer();

    //Load Sounds
    {
        m_pResources->AddSound("ButtonResponseClick", m_SoundPlayer->LoadSound("Data/Audio/ButtonResponseClick.wav"));
        m_pResources->AddSound("ButtonResponseConfirm", m_SoundPlayer->LoadSound("Data/Audio/ButtonResponseConfirm.wav"));
        m_pResources->AddSound("EmptyGunShot", m_SoundPlayer->LoadSound("Data/Audio/EmptyGunShot.wav"));
        m_pResources->AddSound("GunShot1", m_SoundPlayer->LoadSound("Data/Audio/GunShot1.wav"));
        m_pResources->AddSound("GunShot2", m_SoundPlayer->LoadSound("Data/Audio/GunShot2.wav"));
        m_pResources->AddSound("GunShot3", m_SoundPlayer->LoadSound("Data/Audio/GunShot3.wav"));
        m_pResources->AddSound("GunShot4", m_SoundPlayer->LoadSound("Data/Audio/GunShot4.wav"));
        m_pResources->AddSound("Hurt1", m_SoundPlayer->LoadSound("Data/Audio/Hurt1.wav"));
        m_pResources->AddSound("Hurt2", m_SoundPlayer->LoadSound("Data/Audio/Hurt2.wav"));
        m_pResources->AddSound("Hurt3", m_SoundPlayer->LoadSound("Data/Audio/Hurt3.wav"));
        m_pResources->AddSound("Hurt4", m_SoundPlayer->LoadSound("Data/Audio/Hurt4.wav"));
        m_pResources->AddSound("Hurt5", m_SoundPlayer->LoadSound("Data/Audio/Hurt5.wav"));
        m_pResources->AddSound("JumpVocal1", m_SoundPlayer->LoadSound("Data/Audio/JumpVocal1.wav"));
        m_pResources->AddSound("JumpVocal2", m_SoundPlayer->LoadSound("Data/Audio/JumpVocal2.wav"));
        m_pResources->AddSound("JumpVocal3", m_SoundPlayer->LoadSound("Data/Audio/JumpVocal3.wav"));
        m_pResources->AddSound("JumpVocal4", m_SoundPlayer->LoadSound("Data/Audio/JumpVocal4.wav"));
        m_pResources->AddSound("Ray1", m_SoundPlayer->LoadSound("Data/Audio/Ray1.wav"));
        m_pResources->AddSound("Ray2", m_SoundPlayer->LoadSound("Data/Audio/Ray2.wav"));
        m_pResources->AddSound("Ray3", m_SoundPlayer->LoadSound("Data/Audio/Ray3.wav"));
        m_pResources->AddSound("Ray4", m_SoundPlayer->LoadSound("Data/Audio/Ray4.wav"));
        m_pResources->AddSound("Sphosh1", m_SoundPlayer->LoadSound("Data/Audio/Sphosh1.wav"));
        m_pResources->AddSound("Sphosh2", m_SoundPlayer->LoadSound("Data/Audio/Sphosh2.wav"));
        m_pResources->AddSound("Sphosh3", m_SoundPlayer->LoadSound("Data/Audio/Sphosh3.wav"));
        m_pResources->AddSound("Sphosh4", m_SoundPlayer->LoadSound("Data/Audio/Sphosh4.wav"));
    }

    //Make sound cues
    {
        //player cues
        SoundCue* cue = new SoundCue(m_SoundPlayer, "JumpVocalCue");
        cue->SetMode(ECueModes::ECM_Shuffle_No_Repeats);
        cue->AddSound(m_pResources->GetSound("JumpVocal1"), 20);
        cue->AddSound(m_pResources->GetSound("JumpVocal2"), 20);
        cue->AddSound(m_pResources->GetSound("JumpVocal3"), 20);
        cue->AddSound(m_pResources->GetSound("JumpVocal4"), 20);
        m_pResources->AddSoundCue(cue->GetName(), cue);

        cue = new SoundCue(m_SoundPlayer, "HurtCue");
        cue->SetMode(ECueModes::ECM_Random_Weighted);
        cue->AddSound(m_pResources->GetSound("Hurt1"), 250);
        cue->AddSound(m_pResources->GetSound("Hurt2"), 250);
        cue->AddSound(m_pResources->GetSound("Hurt3"), 250);
        cue->AddSound(m_pResources->GetSound("Hurt4"), 250);
        cue->AddSound(m_pResources->GetSound("Hurt5"), 1);
        m_pResources->AddSoundCue(cue->GetName(), cue);

        //Gun cues
        cue = new SoundCue(m_SoundPlayer, "GunShotCue");
        cue->SetMode(ECueModes::ECM_Shuffle_No_Repeats);
        cue->AddSound(m_pResources->GetSound("GunShot1"), 20);
        cue->AddSound(m_pResources->GetSound("GunShot2"), 20);
        cue->AddSound(m_pResources->GetSound("GunShot3"), 40);
        cue->AddSound(m_pResources->GetSound("GunShot4"), 20);
        m_pResources->AddSoundCue(cue->GetName(), cue);

        cue = new SoundCue(m_SoundPlayer, "EmptyGunShotCue");
        cue->SetMode(ECueModes::ECM_Shuffle_No_Repeats);
        cue->AddSound(m_pResources->GetSound("EmptyGunShot"), 100);
        m_pResources->AddSoundCue(cue->GetName(), cue);

        //enemy cues
        cue = new SoundCue(m_SoundPlayer, "EnemyRayCue");
        cue->SetMode(ECueModes::ECM_Shuffle_No_Repeats);
        cue->AddSound(m_pResources->GetSound("Ray1"), 20);
        cue->AddSound(m_pResources->GetSound("Ray2"), 20);
        cue->AddSound(m_pResources->GetSound("Ray3"), 40);
        cue->AddSound(m_pResources->GetSound("Ray4"), 20);
        m_pResources->AddSoundCue(cue->GetName(), cue);

        cue = new SoundCue(m_SoundPlayer, "EnemyDeathCue");
        cue->SetMode(ECueModes::ECM_Shuffle_No_Repeats);
        cue->AddSound(m_pResources->GetSound("Sphosh1"), 20);
        cue->AddSound(m_pResources->GetSound("Sphosh2"), 20);
        cue->AddSound(m_pResources->GetSound("Sphosh3"), 40);
        cue->AddSound(m_pResources->GetSound("Sphosh4"), 20);
        m_pResources->AddSoundCue(cue->GetName(), cue);
    }

    //Create any needed Collision Shapes
    {
#undef  new
        //Player+Box Collider
        btCollisionShape* bodyShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
        m_pResources->AddCollisionShape("1x1x1 Box", bodyShape);

        bodyShape = new btBoxShape(btVector3(5.0f, 5.0f, 5.0f));
        m_pResources->AddCollisionShape("10x10x10 Box", bodyShape);

        bodyShape = new btBoxShape(btVector3(2.5f, 5.0f, 2.5f));
        m_pResources->AddCollisionShape("5x10x5 Box", bodyShape);

        bodyShape = new btSphereShape(0.5f);
        m_pResources->AddCollisionShape("0.5f Sphere", bodyShape);

#define new new(__FILE__, __LINE__)
    }

    //Handle Scenes
    {
        //Create the Scene Manager
        m_pSceneManager = new SceneManager(m_pResources);

        // Create our scenes.
        Scene* scene = new SceneSample("SceneSample", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);

        //A title screen/main menu
        scene = new TitleScene("TitleScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);
        //A game scene
        scene = new MainGameScene("MainGameScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);
        //An options menu with at least 2 options that are hooked up to the game
        scene = new OptionsMenuScene("OptionsMenuScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);
        //Hud / score display
        scene = new HudScene("HudScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);
        //A pause menu
        scene = new PauseMenu("PauseMenu", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);
        //A game over scene that shows results
        scene = new GameOverScene("GameOverScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);

        scene = new GunScene("GunScene", this, m_pResources, m_SoundPlayer);
        scene->LoadContent();
        m_pSceneManager->AddNewScene(scene->GetName(), scene);

        //Push the start scene
        //m_pSceneManager->PushScene("SceneSample");
        //m_pSceneManager->PushScene("GunScene");
        m_pSceneManager->PushScene("TitleScene");
        //Setup SubScenes
        m_pSceneManager->GetScene("MainGameScene")->AddSubScene(m_pSceneManager->GetScene("GunScene"));
        m_pSceneManager->GetScene("MainGameScene")->AddSubScene(m_pSceneManager->GetScene("HudScene"));
    }

    // Create an ImGui object.
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();
    m_bDrawImGui = true;

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_RemoveFromScene)
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = static_cast<RemoveFromSceneEvent*>(pEvent);

        Scene* pScene = pRemoveFromSceneEvent->GetScene();
        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();

        if (pScene->IsGameObjectInScene(pGameObject))
        {
            pGameObject->RemoveFromScene();
            return; // true;
        }
    }

    m_pImGuiManager->OnEvent( pEvent );

    m_pControllers[0]->OnEvent( pEvent );

    m_pSceneManager->OnEvent( pEvent );

#if WIN32
    // Enable/Disable V-Sync with F1 and F2.
    if( pEvent->GetEventType() == EventType_Input )
    {
        InputEvent* pInput = static_cast<InputEvent*>( pEvent );

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            if (pInput->GetInputState() == InputState_Pressed)
            {
                // Enable V-Sync.
                if (pInput->GetID() == VK_F1)
                    wglSwapInterval(1);

                // Disable V-Sync.
                else if (pInput->GetID() == VK_F2)
                    wglSwapInterval(0);

                //Swap drawing of ImGui debug
                else if (pInput->GetID() == VK_F9)
                    m_bDrawImGui = !m_bDrawImGui;

                // Reset active scene.
                else if (pInput->GetID() == 'R')
                    m_pSceneManager->Reset();
            }
        }
    }
#endif //WIN32
}

void Game::Update(float deltaTime)
{
    // Once our events are processed, tell ImGui we're starting a new frame.
    m_pImGuiManager->StartFrame((float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime);

    m_pSceneManager->Update(deltaTime);
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // (red, green, blue, alpha) - dark blue.
#if WIN32
    glClearDepth( 1 ); // 1 is maximum depth.
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_pSceneManager->Draw();

    if (m_bDrawImGui)
        m_pResources->GenerateImGuiWindow();

    // Tell imgui we're at the end of our frame, so it will draw all queued objects.if (m_DrawImGui)
    m_pImGuiManager->EndFrame();

    CheckForGLErrors();
}
