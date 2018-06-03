#include "EngineController.h"
#include "../Scene/AssetManager.h"
#include "../Material/MaterialManager.h"
#include "../Interactive/InputManager.h"
#include "../Interactive/ThirdPersonCamera.h"
#include "../Entity/StaticEntity.h"
#include "../Mesh/Model.h"
#include "../Lighting/DirLight.h"
#include "../Lighting/PointLight.h"
#include <vector>
#include "../Context.h"

EngineController::EngineController()
{
    scene = nullptr;
    render = nullptr;
    renderMgr = nullptr;
}

EngineController::~EngineController()
{
    MaterialManager::Release();
    AssetManager::Release();
    delete scene; scene = nullptr;
    delete render; render = nullptr;
    delete renderMgr; renderMgr = nullptr;
}

void EngineController::init()
{
    render = new Render();

    AssetManager::Init();
    MaterialManager::Init();

    scene = new Scene();
    renderMgr = new RenderManager(QVector3D(-1, -1, -1));
    renderMgr->setShadow(2048,2048);
    m_timer.start();
}

void EngineController::draw()
{
    //1. shadow rendering
    render->setFrameBuffer(renderMgr->getShadow()->getFramebuffer());
    renderMgr->renderShadow(render,*camera,renderMgr->getLighting("sun"));
    //2. geometry rendering
    render->setFrameBuffer(renderMgr->getDeferredFramebuffer());
    renderMgr->renderScene(render, *camera, scene);
    //3. deferred rendering
    render->setFrameBuffer(nullptr);
    renderMgr->renderDeferred(render,*camera);
    //4. bloom blur
//    render->setFrameBuffer(nullptr);
//    renderMgr->renderBloom(render,*camera);
}

void EngineController::update(long startTime, long currentTime)
{
    Q_UNUSED(startTime);
    Q_UNUSED(currentTime);
    qint64 elapsedTime = m_timer.elapsed();
    renderMgr->animateQueue(0,elapsedTime);
    renderMgr->getShadow()->update(/*camera->getPosition() +*/
                                   500.0f*renderMgr->getLighting("sun")->getDirection(),
                                   -renderMgr->getLighting("sun")->getDirection());
    camera->setLightSpaceMatrix(renderMgr->getShadow()->lightSpaceMatrix);
}

void EngineController::prepare()
{
}

void EngineController::resize(int width, int height)
{
    renderMgr->resize(render,width,height);
    camera->initPerspectProject(45.0f,(float)width/(float)height,0.1f,1000.0f);
    render->setProjectPlane(camera->zNear,camera->zFar);
}

void EngineController::setDefaultFramebuffer(GLuint fbo)
{
    render->setDefaultFramebuffer(fbo);
}

void EngineController::initScene()
{
    AssetManager* assetMgr = AssetManager::assetManager;
    MaterialManager* mtlMgr = MaterialManager::materials;

    // load textures
    std::vector<QString> cubemaps = {"right.png","left.png","top.png",
                                     "bottom.png","back.png","front.png"};

    assetMgr->textures->addToTextureArray("cube",".bmp");
    assetMgr->textures->addToTextureArray("ground",".bmp");
    assetMgr->textures->addToTextureArray("mud",".png","terrain/");
    assetMgr->textures->loadCubeTexture("sky","../textures/skybox/night",cubemaps);

    // materials
    Material *boxMat = new Material("box_mat");
    boxMat->texture.setX(assetMgr->textures->findTexture("cube"));
    mtlMgr->add(boxMat);

    Material *groundMat = new Material("ground_mat");
    groundMat->texture.setX(assetMgr->textures->findTexture("ground"));
    mtlMgr->add(groundMat);

    Material *sphereMat = new Material("sphere_mat");
    sphereMat->texture.setX(assetMgr->textures->findTexture("mud"));
    mtlMgr->add(sphereMat);

    // add meshes
    AssetManager::assetManager->addMesh("tank", new Model("../models/tank.obj",
                                                          "../models/tank.mtl"));
    AssetManager::assetManager->addMesh("player", new Model("../models/person.obj",
                                                            "../models/person.mtl"));
    AssetManager::assetManager->addMesh("lamp", new Model("../models/lamp.obj",
                                                          "../models/lamp.mtl"));
    AssetManager::assetManager->addMesh("tree", new Model("../models/tree.obj",
                                                          "../models/tree.mtl"));
    AssetManager::assetManager->addMesh("lowPolyTree", new Model("../models/lowPolyTree.obj",
                                                                 "../models/lowPolyTree.mtl"));
    AssetManager::assetManager->addAnimation("runningman",
                                             new AnimationLoader("../models/people.dae"));

    std::map<QString,Mesh*>& meshes = assetMgr->meshes;

    scene->addStaticEntity(QObject::tr("sphere0"),"sphere_draw"
                           ,meshes["sphere"], sphereMat);
    scene->setEntityTranslate("sphere0",QVector3D(2,2,0));
    scene->addStaticEntity(QObject::tr("cube0"),"cube_draw"
                           ,meshes["cube"], boxMat);
    scene->setEntityTranslate("cube0",QVector3D(2,0.5,0));

    scene->addStaticEntity(QObject::tr("sphere1"),"sphere_draw"
                           ,meshes["sphere"], sphereMat);
    scene->setEntityTranslate("sphere1",QVector3D(-2,2,0));
    scene->addStaticEntity(QObject::tr("cube1"),"cube_draw"
                           ,meshes["cube"], boxMat);
    scene->setEntityTranslate("cube1",QVector3D(-2,0.5,0));

    scene->addStaticEntity(QObject::tr("sphere2"),"sphere_draw"
                           ,meshes["sphere"], sphereMat);
    scene->setEntityTranslate("sphere2",QVector3D(0,2,-2));
    scene->addStaticEntity(QObject::tr("cube2"),"cube_draw"
                           ,meshes["cube"], boxMat);
    scene->setEntityTranslate("cube2",QVector3D(0,0.5,-2));

    scene->addStaticEntity(QObject::tr("sphere3"),"sphere_draw"
                           ,meshes["sphere"], sphereMat);
    scene->setEntityTranslate("sphere3",QVector3D(0,2,2));
    scene->addStaticEntity(QObject::tr("cube3"),"cube_draw"
                           ,meshes["cube"], boxMat);
    scene->setEntityTranslate("cube3",QVector3D(0,0.5,2));

    //tank model
    scene->addStaticEntity(QObject::tr("tank"),"tank_draw"
                           ,meshes["tank"],nullptr);
    scene->setEntityTranslate("tank",QVector3D(10,0,10));
    scene->setEntityScale("tank",QVector3D(0.3,0.3,0.3));

    // player model
    scene->addStaticEntity(QObject::tr("player"),"player_draw"
                           ,meshes["player"],nullptr);
    scene->setEntityTranslate("player",QVector3D(-5,0,-5));


    // add lighting here
    renderMgr->addLighting("sun",new DirLight(QVector3D(1,1,0)));
    // lamp model and add point light
    int ord = 0;
    for(float x = 0.0f;x <= 360.0f;x += 15.0f)
    {
        QString name = QObject::tr("lamp%1").arg(ord);
        scene->addStaticEntity(name,"lamp_draw",meshes["lamp"],nullptr);
        float px = 30.0f*cos(3.1415/180.0*x);
        float pz = 30.0f*sin(3.1415/180.0*x);
        scene->setEntityTranslate(name,QVector3D(px,0.0f,pz));
        scene->pushEntityToRender(name,this->renderMgr);
        renderMgr->addLighting(name,new PointLight(QVector3D(px,12,pz)));
        ++ord;
    }
    scene->addStaticEntity("lampcenter","lamp_draw",meshes["lamp"],nullptr);
    scene->setEntityScale("lampcenter",QVector3D(1.5f,1.5f,1.5f));
    scene->pushEntityToRender("lampcenter",this->renderMgr);
    renderMgr->addLighting("lampcenter",new PointLight(QVector3D(0,20,0)));
    renderMgr->setAllLightToUniform(render);

    // tree model
    scene->addStaticEntity(QObject::tr("tree"),"tree_draw_ins"
                           ,meshes["tree"],nullptr);
    scene->addStaticEntity(QObject::tr("lowPolyTree"),"lowPolyTree_draw_ins"
                           ,meshes["lowPolyTree"],nullptr);

    // soilder animation
    scene->addAnimateEntity(QObject::tr("runningman"),"runningman_draw_ani",
                            assetMgr->animations["runningman"],nullptr);
    scene->setEntityTranslate("runningman",QVector3D(0,0,-20));
    scene->setEntityScale("runningman",QVector3D(1.8,1.8,1.8));
    scene->setEntityRotation("runningman",-90.0f,QVector3D(1,0,0));

    // floor
    scene->addStaticEntity(QObject::tr("floor"),"quad_draw"
                           ,meshes["quad"], groundMat);
    scene->setEntityScale("floor",QVector3D(1000,1000,1000));

    scene->pushEntityToRender("sphere0",this->renderMgr);
    scene->pushEntityToRender("cube0",this->renderMgr);
    scene->pushEntityToRender("sphere1",this->renderMgr);
    scene->pushEntityToRender("cube1",this->renderMgr);
    scene->pushEntityToRender("sphere2",this->renderMgr);
    scene->pushEntityToRender("cube2",this->renderMgr);
    scene->pushEntityToRender("sphere3",this->renderMgr);
    scene->pushEntityToRender("cube3",this->renderMgr);
    scene->pushEntityToRender("floor",this->renderMgr);
    scene->pushEntityToRender("tank",this->renderMgr);
    scene->pushEntityToRender("player",this->renderMgr);
    scene->pushEntityToRender("tree",this->renderMgr,INSTANCE_DC);
    scene->pushEntityToRender("lowPolyTree",this->renderMgr,INSTANCE_DC);
    scene->pushEntityToRender("runningman",this->renderMgr,ANIMATE_DC);

    render->addStaticDrawcall("tank_draw",meshes["tank"],nullptr);
    render->addStaticDrawcall("player_draw",meshes["player"],nullptr);
    render->addStaticDrawcall("lamp_draw",meshes["lamp"],nullptr);
    render->addStaticDrawcall("cube_draw",meshes["cube"],boxMat);
    render->addStaticDrawcall("sphere_draw",meshes["sphere"],sphereMat);
    render->addStaticDrawcall("board_draw",meshes["board"],groundMat);
    render->addStaticDrawcall("quad_draw",meshes["quad"],groundMat);
    render->addAnimateDrawcall("runningman_draw_ani",assetMgr->animations["runningman"],
            nullptr);

    // set instance drawcall -tree
    std::vector<QMatrix4x4> treeInstance(500);
    srand(time(nullptr));
    for(uint x = 0;x < 500;++ x){
        treeInstance[x].setToIdentity();
        float x1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        float z1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        while((x1*x1 + z1*z1) < 900.0f){
            x1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
            z1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        }
        treeInstance[x].translate(x1,0,z1);
        treeInstance[x].scale(10,10,10);
    }
    render->addInstanceDrawcall("tree_draw_ins",meshes["tree"],
            nullptr,treeInstance);

    // lowPolyTree
    for(uint x = 0;x < 500;++ x){
        treeInstance[x].setToIdentity();
        float x1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        float z1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        while((x1*x1 + z1*z1) < 900.0f){
            x1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
            z1 = (2.0f*(float)rand()/(float)RAND_MAX-1.0f)*500;
        }
        treeInstance[x].translate(x1,0,z1);
        treeInstance[x].scale(0.8,0.8,0.8);
    }
    render->addInstanceDrawcall("lowPolyTree_draw_ins",meshes["lowPolyTree"],
            nullptr,treeInstance);


    scene->skyBox = new Sky(meshes["sphere"],
            assetMgr->textures->findCubeTexture("sky"));

    // load all the textures finally
    assetMgr->initTextureArray("../textures");

    // camera and player
    player = new Player(scene->getEntity("player"));
    camera = new ThirdPersonCamera(player);
}
