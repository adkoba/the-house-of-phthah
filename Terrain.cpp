#include "Terrain.h"
#include "HouseOfPhthah.h"

CTerrainListener::CTerrainListener()
{
}

CTerrainListener::~CTerrainListener()
{
	// is it really clean?
	//SceneManager::destroyQuery(mRaySceneQuery);
	delete mRaySceneQuery; mRaySceneQuery = NULL;
}
bool CTerrainListener::frameRenderingQueued(const FrameEvent& evt)
{
    if( FrameListener::frameRenderingQueued(evt) == false )
	return false;

	Ogre::Camera* camera = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera;

    // clamp to terrain
    mUpdateRay.setOrigin(camera->getPosition());
    mUpdateRay.setDirection(Vector3::NEGATIVE_UNIT_Y);
    mRaySceneQuery->setRay(mUpdateRay);
    RaySceneQueryResult& qryResult = mRaySceneQuery->execute();
    RaySceneQueryResult::iterator i = qryResult.begin();
    if (i != qryResult.end() && i->worldFragment)
    {
        camera->setPosition(camera->getPosition().x, 
							i->worldFragment->singleIntersection.y + 10, 
							camera->getPosition().z);
    }

    return true;
}

CTerrain::CTerrain():
	mListener(NULL),
	mTerrainId("")
{
	mListener = new CTerrainListener();
}

CTerrain::~CTerrain()
{
	// do I have to detach it from Ogre::Root first?
	delete mListener; mListener = NULL;
	// do I have to detach something from any tree?
}

void CTerrain::createTerrain(const String TerrainId)
{
	assert(TerrainId!=""&&"Problem in CTerrain::createTerrain()");

	mTerrainId = TerrainId;

	Ogre::Root* root = Ogre::Singleton<Root>::getSingletonPtr();
	Ogre::SceneManager* sceneMgr = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;
	Ogre::Camera* camera = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera;

	mListener->setRaySceneQuery( sceneMgr->createRayQuery( Ray(camera->getPosition(), Vector3::NEGATIVE_UNIT_Y) ) );
	root->addFrameListener(mListener);

	sceneMgr->setWorldGeometry( mTerrainId );
    // Infinite far plane?
    if (root->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
    {
        camera->setFarClipDistance(0);
    }
}
