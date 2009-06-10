#include "SkyDome.h"
#include "HouseOfPhthah.h"

CSkyDomeListener::CSkyDomeListener():
	mNodeId(NULL)
{
}

CSkyDomeListener::~CSkyDomeListener()
{
	// I don't want to delete it since CSkyDome can handle it
	mNodeId = NULL;
}

bool  CSkyDomeListener::frameStarted(const Ogre::FrameEvent& evt)
{
	SceneManager* sceneMgr = Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;
	Ogre::Camera* camera = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mCamera;
	// position the skydome at camera position as frequently as possible (I should assert that SkyDomeNode exists)
	sceneMgr->getSceneNode(*mNodeId)->setPosition(camera->getPosition() - Ogre::Vector3(0,50,0)); // trick to make the sky closer to the camera, thus camera can't easily see the void under the terrain
	return true;
}

bool  CSkyDomeListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return frameStarted(evt);
}

bool  CSkyDomeListener::frameEnded(const Ogre::FrameEvent& evt)
{
	return frameStarted(evt);
}

CSkyDome::CSkyDome():
	mListener(NULL),
	mSkyDomeEntity(NULL),
	mEntityId(""),
	mMaterialName(""),
	mMeshName(""),
	mNodeId("")
{
	mListener = new CSkyDomeListener();
}

CSkyDome::CSkyDome(const CSkyDome& copy):
	mListener(NULL),
	mSkyDomeEntity(NULL),
	mEntityId(copy.mEntityId),
	mMaterialName(copy.mMaterialName),
	mMeshName(copy.mMeshName),
	mNodeId(copy.mNodeId)
{
	mListener = new CSkyDomeListener();
}

CSkyDome::~CSkyDome()
{
	// do I have to detach it from Ogre::Root first?
	delete mListener; mListener = NULL;
	// do I have to detach something from any tree?
}

void CSkyDome::createSkyDome(const Ogre::String MeshName, const Ogre::String MaterialName, const Ogre::String EntityId, const Ogre::String NodeId)
{
	assert(MeshName!=""&&MaterialName!=""&&EntityId!=""&&NodeId!=""&&"Problem in CSkyDome::createSkyDome()");

	mMaterialName = MaterialName;
	mMeshName = MeshName;
	mNodeId = NodeId;
	mEntityId = EntityId;
	mListener->setNodeId(mNodeId);

	Ogre::Root* root = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mRoot;
	Ogre::SceneManager* sceneMgr = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;

	root->addFrameListener(mListener);

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

    // Destroy previous entity
	if (mSkyDomeEntity) sceneMgr->destroyEntity(mEntityId);
	// Create new sentity
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