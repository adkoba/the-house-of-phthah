#include "SkyDome.h"
#include "HouseOfPhthah.h"

#include <assert.h>

CSkyDome::CSkyDome():
	mMaterialName(""),
	mMeshName(""),
	mSkyDomeNode(NULL),
	mSkyDomeEntity(NULL),
	mNodeId("PhthahSkyDomeNode"),
	mEntityId("PhthahSkyDomeEntity")
{
}

CSkyDome::CSkyDome(const CSkyDome& copy):
	mMaterialName(copy.mMaterialName),
	mMeshName(copy.mMeshName),
	mSkyDomeNode(NULL),
	mSkyDomeEntity(NULL),
	mNodeId(copy.mNodeId),
	mEntityId(copy.mEntityId)
{
}

CSkyDome::~CSkyDome()
{
	delete mSkyDomeNode; mSkyDomeNode = NULL;
	delete mSkyDomeEntity; mSkyDomeEntity = NULL;
	// one must maybe also destroy something in the mSceneManager tree?
}

void CSkyDome::createSkyDome()
{
	Ogre::SceneManager* sceneMgr = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;
	Ogre::Camera* camera = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera;

	assert(mMeshName!=""&&mMaterialName!=""&&"Problem in CSkyDome::createSkyDome()");

	// there should be an exception if can't find mesh or material

  //  // Create node 
  //  if (!mSkyDomeNode)
  //  {
  //      mSkyDomeNode = sceneMgr->createSceneNode(mNodeId);
		//mSkyDomeNode->scale(100,100,100);
		////// initial position of the skydome
		////mSkyDomeNode->setPosition(camera->getPosition());
  //  }
  //  else
  //  {
  //      mSkyDomeNode->detachAllObjects();
  //  }

    // Create entity 
    if (mSkyDomeEntity) sceneMgr->destroyEntity(mEntityId);
	
	mSkyDomeEntity = sceneMgr->createEntity(mEntityId, mMeshName);
	mSkyDomeEntity->setMaterialName(mMaterialName);
	mSkyDomeEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_EARLY);
	MaterialPtr m = MaterialManager::getSingleton().getByName(mMaterialName);
    // Make sure the material doesn't update the depth buffer
    m->setDepthWriteEnabled(false);
    // Ensure loaded
    m->load();

	sceneMgr->getRootSceneNode()->createChildSceneNode(mNodeId)->attachObject(mSkyDomeEntity);
	sceneMgr->getSceneNode(mNodeId)->scale(100,100,100);

	//mSkyDomeNode->attachObject(mSkyDomeEntity);
}