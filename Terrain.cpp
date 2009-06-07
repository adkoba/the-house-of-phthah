#include "Terrain.h"
#include "HouseOfPhthah.h"

CTerrain::CTerrain(  ) :
	mRaySceneQuery(NULL)
{
	
}

CTerrain::~CTerrain()
{
	//SceneManager::destroyQuery(mRaySceneQuery);
	if (mRaySceneQuery) delete mRaySceneQuery;
}

void CTerrain::Init( const std::string& terrain_cfg )
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
}
