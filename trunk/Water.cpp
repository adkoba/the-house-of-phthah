#include "Water.h"
#include "Macros.h"
#include "HouseOfPhthah.h"

CWater::CWater() :
	mPlane(NULL),
	mPlaneEnt(NULL),
	mPlaneNode(NULL),
	mFrameListener(NULL)
{
	
}

CWater::~CWater()
{
	SAFE_DELETE( mPlane )
	SAFE_DELETE( mPlaneEnt )
	SAFE_DELETE( mPlaneNode )
	SAFE_DELETE( mReflectCam )
	SAFE_DELETE( mFrameListener )

	Root::getSingleton().removeFrameListener(mFrameListener);
}

void CWater::init()
{
	Ogre::SceneManager* sceneMgr = CHouseOfPhthah::getSingleton().mSceneMgr;

	// Create a prefab plane
	mPlane = new MovablePlane("ReflectPlane");
	mPlane->d = 0;
	mPlane->normal = Vector3::UNIT_Y;
	MeshManager::getSingleton().createPlane("ReflectionPlane", 
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		*mPlane, 2000, 2000, 
		1, 1, true, 1, 1, 1, Vector3::UNIT_Z);
	mPlaneEnt = sceneMgr->createEntity( "Plane", "ReflectionPlane" );

	// Attach the rtt entity to the root of the scene
	SceneNode* rootNode = sceneMgr->getRootSceneNode();
	mPlaneNode = rootNode->createChildSceneNode("waterNode");

	// Attach both the plane entity, and the plane definition
	mPlaneNode->attachObject(mPlaneEnt);
	mPlaneNode->attachObject(mPlane);
	mPlaneNode->translate(1000, 6, 1000);


	// Create Render Texture to be associated with the reflected rendering
	mReflectionTex = TextureManager::getSingleton().createManual( "ReflectionRttTex", 
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 
		512, 512, 0, PF_R8G8B8, TU_RENDERTARGET );

	// Create a Camera for the reflection computation	
	RenderWindow* window = CHouseOfPhthah::getSingleton().mWindow;
	Camera* camera = CHouseOfPhthah::getSingleton().mCamera;

	RenderTarget *rttTex = mReflectionTex->getBuffer()->getRenderTarget();
	{
		mReflectCam = sceneMgr->createCamera("ReflectCam");
		mReflectCam->setNearClipDistance(camera->getNearClipDistance());
		mReflectCam->setFarClipDistance(camera->getFarClipDistance());
		mReflectCam->setAspectRatio(
			(Real)window->getViewport(0)->getActualWidth() / 
			(Real)window->getViewport(0)->getActualHeight());
		mReflectCam->setFOVy (camera->getFOVy());


		Viewport *v = rttTex->addViewport( mReflectCam );
		v->setClearEveryFrame( true );
		v->setBackgroundColour( ColourValue::Black );

		mMat = MaterialManager::getSingleton().create("ReflectRttMat",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		TextureUnitState* t = mMat->getTechnique(0)->getPass(0)->createTextureUnitState("RustedMetal.jpg");
		t = mMat->getTechnique(0)->getPass(0)->createTextureUnitState("ReflectionRttTex");
		// Blend with base texture
		t->setColourOperationEx(LBX_BLEND_MANUAL, LBS_TEXTURE, LBS_CURRENT, ColourValue::White, 
			ColourValue::White, 0.35);
		t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
		t->setProjectiveTexturing(true, mReflectCam);
		rttTex->addListener(this);
		// set up linked reflection
		mReflectCam->enableReflection(mPlane);
		// Also clip
		mReflectCam->enableCustomNearClipPlane(mPlane);
	}

	// Give the plane a texture
	mPlaneEnt->setMaterialName("ReflectRttMat");

	createFrameListener();
}

void CWater::createFrameListener()
{
	mFrameListener= new RenderToTextureFrameListener(
			CHouseOfPhthah::getSingleton().mCamera, 
			mReflectCam, 
			mPlaneNode);
	Root::getSingleton().addFrameListener(mFrameListener);
}