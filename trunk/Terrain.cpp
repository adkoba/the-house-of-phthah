#include "Terrain.h"
#include "HouseOfPhthah.h"

CTerrain::CTerrain(  ) :
	mRaySceneQuery(NULL),
	mFrameListener(NULL)
{
	
}

CTerrain::~CTerrain()
{
	//SceneManager::destroyQuery(mRaySceneQuery);
	if (mRaySceneQuery) delete mRaySceneQuery;
	if (mFrameListener) delete mFrameListener;
}

void CTerrain::Init( std::string terrain_cfg )
{
	Ogre::Root* root = Ogre::Singleton<Root>::getSingletonPtr();
	//Ogre::SceneManager* sceneMgr = root->createSceneManager("TerrainSceneManager");
	//Ogre::SceneManager* sceneMgr = root->getSceneManager("TerrainSceneManager");	
	Ogre::SceneManager* sceneMgr = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;
	Ogre::Camera* camera = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera;
	
	sceneMgr->setWorldGeometry( terrain_cfg );
    // Infinite far plane?
    if (root->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
    {
        camera->setFarClipDistance(0);
    }

	mRaySceneQuery = sceneMgr->createRayQuery(
            Ray(camera->getPosition(), Vector3::NEGATIVE_UNIT_Y));

	createFrameListener();
}

// Create new frame listener
void CTerrain::createFrameListener()
{
	mFrameListener= new CTerrainFrameListener( 
		Ogre::Singleton<CHouseOfPhthah>::getSingleton().mWindow, 
		Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera,
		mRaySceneQuery
		);
	//Singleton<Root>::getSingletonPtr()->addFrameListener(mFrameListener);
	Ogre::Singleton<CHouseOfPhthah>::getSingleton().mRoot->addFrameListener(mFrameListener);
}
