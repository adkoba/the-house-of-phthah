#include "SkyDome.h"

#include <OgreEntity.h>
#include <OgreMaterialManager.h> 
#include <OgreRoot.h>

#include "Macros.h"

CSkyDomeListener::CSkyDomeListener(Camera* camera, SceneNode* skyDomeNode):
	mCamera(camera),
	mSkyDomeNode(skyDomeNode),
	mCaelumSystem(NULL)
{
	//Root* root = Root::getSingletonPtr();
 //   SceneManager* sceneMgr = root->getSceneManager("MainScene");

 //   // Pick components to create in the demo.
 //   // You can comment any of those and it should still work
 //   // Trying to disable one of these can be useful in finding problems.
 //   Caelum::CaelumSystem::CaelumComponent componentMask;
 //   componentMask = static_cast<Caelum::CaelumSystem::CaelumComponent> (
 //           Caelum::CaelumSystem::CAELUM_COMPONENT_SUN |				
 //           Caelum::CaelumSystem::CAELUM_COMPONENT_MOON |
 //           Caelum::CaelumSystem::CAELUM_COMPONENT_SKY_DOME |
 //           //Caelum::CaelumSystem::CAELUM_COMPONENT_IMAGE_STARFIELD |
 //           Caelum::CaelumSystem::CAELUM_COMPONENT_POINT_STARFIELD |
 //           Caelum::CaelumSystem::CAELUM_COMPONENT_CLOUDS |
 //           0);
 //   componentMask = Caelum::CaelumSystem::CAELUM_COMPONENTS_DEFAULT;

 //   // Initialise CaelumSystem.
 //   mCaelumSystem = new Caelum::CaelumSystem (root, sceneMgr, componentMask);

 //   // Set time acceleration.
 //   mCaelumSystem->getUniversalClock()->setTimeScale (512);

 //   // Register caelum as a listener.
	//RenderWindow* mWindow = root->getAutoCreatedWindow();
 //   mWindow->addListener (mCaelumSystem);
 //   Root::getSingletonPtr()->addFrameListener (mCaelumSystem);
}

CSkyDomeListener::~CSkyDomeListener()
{
	// I don't want to delete these things since CSkyDome can handle it
	mCamera = NULL;
	mSkyDomeNode = NULL;
    if (mCaelumSystem)
	{
        mCaelumSystem->shutdown(false);
        mCaelumSystem = NULL;
    }
}

bool  CSkyDomeListener::frameStarted(const Ogre::FrameEvent& evt)
{
	assert(mCamera&&mSkyDomeNode&&"Problem in CSkyDomeListener::frameStarted()");
	// position the skydome at camera position as frequently as possible (I should assert that SkyDomeNode exists)
	// trick to make the sky closer to the camera, thus player can't easily see the void under the terrain unless he's very close to the border
	mSkyDomeNode->setPosition(mCamera->getPosition() - Ogre::Vector3(0,50,0)); 
	return true;
}

CSkyDome::CSkyDome():
	mListener(NULL),
	mSkyDomeEntity(NULL),
	mEntityId(""),
	mMaterialName(""),
	mMeshName(""),
	mNodeId("")
{
}

CSkyDome::CSkyDome(const CSkyDome& copy):
	mListener(NULL),
	mSkyDomeEntity(NULL),
	mEntityId(copy.mEntityId),
	mMaterialName(copy.mMaterialName),
	mMeshName(copy.mMeshName),
	mNodeId(copy.mNodeId)
{
}

CSkyDome::~CSkyDome()
{
	// do I have to detach it from Ogre::Root first?
	SAFE_DELETE( mListener )
	// do I have to detach something from any tree?
}

void CSkyDome::createSkyDome(const Ogre::String MeshName, const Ogre::String MaterialName, const Ogre::String EntityId, const Ogre::String NodeId)
{
	assert(MeshName!=""&&MaterialName!=""&&EntityId!=""&&NodeId!=""&&"Problem in CSkyDome::createSkyDome()");

	mMaterialName = MaterialName;
	mMeshName = MeshName;
	mNodeId = NodeId;
	mEntityId = EntityId;

	Root* root = Root::getSingletonPtr();
	SceneManager* sceneMgr = root->getSceneManager("MainScene");

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

	// create the listener
	mListener = new CSkyDomeListener( sceneMgr->getCamera("PlayerCam"), sceneMgr->getSceneNode(mNodeId) );
	root->addFrameListener(mListener);
	//mSkyDomeNode->attachObject(mSkyDomeEntity);
}