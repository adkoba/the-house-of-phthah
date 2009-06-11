#include "Terrain.h"

#include <OgreRenderSystem.h> 
#include <OgreRoot.h>

#include "Macros.h"

CTerrainListener::CTerrainListener(Camera* camera):
	mCamera(camera),
	mRaySceneQuery(NULL)
{
}

CTerrainListener::~CTerrainListener()
{
	// make sure not to delete the camera!!
	mCamera = NULL;
	// is it really clean?
	//SceneManager::destroyQuery(mRaySceneQuery);
	SAFE_DELETE( mRaySceneQuery )
}
bool CTerrainListener::frameRenderingQueued(const FrameEvent& evt)
{
    if( FrameListener::frameRenderingQueued(evt) == false )
	return false;

	assert(mCamera&&mRaySceneQuery&&"Problem in CTerrainListener::frameRenderingQueued()");

    // clamp to terrain
    mUpdateRay.setOrigin(mCamera->getPosition());
    mUpdateRay.setDirection(Vector3::NEGATIVE_UNIT_Y);
    mRaySceneQuery->setRay(mUpdateRay);
    RaySceneQueryResult& qryResult = mRaySceneQuery->execute();
    RaySceneQueryResult::iterator i = qryResult.begin();
    if (i != qryResult.end() && i->worldFragment)
    {
        mCamera->setPosition(mCamera->getPosition().x, 
							i->worldFragment->singleIntersection.y + 10, 
							mCamera->getPosition().z);
    }

    return true;
}

CTerrain::CTerrain():
	mListener(NULL),
	mTerrainId("")
{
}

CTerrain::~CTerrain()
{
	// do I have to detach it from Ogre::Root first?
	SAFE_DELETE( mListener )
	// do I have to detach something from any tree?
}

void CTerrain::createTerrain(const String TerrainId)
{
	assert(TerrainId!=""&&"Problem in CTerrain::createTerrain()");

	mTerrainId = TerrainId;

	Root* root = Root::getSingletonPtr();
	SceneManager* sceneMgr = root->getSceneManager("MainScene");
	Camera* camera = sceneMgr->getCamera("PlayerCam");

	mListener = new CTerrainListener(camera);
	mListener->setRaySceneQuery( sceneMgr->createRayQuery( Ray(camera->getPosition(), Vector3::NEGATIVE_UNIT_Y) ) );
	root->addFrameListener(mListener);

	sceneMgr->setWorldGeometry( mTerrainId );
    // Infinite far plane?
    if (root->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
    {
        camera->setFarClipDistance(0);
    }
}
