#include "Sky.h"
#include "SkyListener.h"

#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreMaterialManager.h> 
#include <OgreRoot.h>

#include "../../Macros.h"

using namespace Caelum;

CSky::CSky():
	mListener(NULL),
	mSkyType(OGRE_SKY_PLANE),
	mCaelumSystem(NULL),
	mSkyDomeEntity(NULL),
	mEntityId(""),
	mMaterialName(""),
	mMeshName(""),
	mNodeId("")
{
}

CSky::~CSky()
{
	SAFE_DELETE( mListener )
	deleteSky();
}

//void CSky::createSkyDome(const Ogre::String MeshName, const Ogre::String MaterialName, const Ogre::String EntityId, const Ogre::String NodeId)
//{
//	assert(MeshName!=""&&MaterialName!=""&&EntityId!=""&&NodeId!=""&&"Problem in CSky::createSkyDome()");
//
//	mMaterialName = MaterialName;
//	mMeshName = MeshName;
//	mNodeId = NodeId;
//	mEntityId = EntityId;
//
//	Root* root = Root::getSingletonPtr();
//	SceneManager* sceneMgr = root->getSceneManager("MainScene");
//
//    // Destroy previous entity
//	if (mSkyDomeEntity) sceneMgr->destroyEntity(mEntityId);
//	// Create new sentity
//	mSkyDomeEntity = sceneMgr->createEntity(mEntityId, mMeshName);
//	mSkyDomeEntity->setMaterialName(mMaterialName);
//	mSkyDomeEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_EARLY);
//	MaterialPtr m = MaterialManager::getSingleton().getByName(mMaterialName);
//    // Make sure the material doesn't update the depth buffer
//    m->setDepthWriteEnabled(false);
//    // Ensure loaded
//    m->load();
//
//	sceneMgr->getRootSceneNode()->createChildSceneNode(mNodeId)->attachObject(mSkyDomeEntity);
//	sceneMgr->getSceneNode(mNodeId)->scale(100,100,100);
//
//	// create the listener
//	mListener = new CSkyListener( sceneMgr->getCamera("PlayerCam"), sceneMgr->getSceneNode(mNodeId), this);
//	root->addFrameListener(mListener);
//	//mSkyDomeNode->attachObject(mSkyDomeEntity);
//}

void CSky::createSky(const eSkyType& SkyType)
{
	mSkyType = SkyType;
	assert(!mListener&&"Problem in CSky::createSky(const eSkyType& SkyType)");
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
	switch ( SkyType )
	{
	case OGRE_SKY_PLANE:
		createOgreSkyPlane();
		mListener = new CSkyListener( this );
	break;
	case OGRE_SKY_BOX:
		createOgreSkyBox();
		mListener = new CSkyListener( this );
	break;
	case OGRE_SKY_DOME:
		createOgreSkyDome();
		mListener = new CSkyListener( this );
	break;
	case PHTHAH_SKY_DOME:
		createPhthahSkyDome();
		mListener = new CSkyListener( this, sceneMgr->getCamera("PlayerCam"), sceneMgr->getSceneNode(mNodeId) );
	break;
	case CAELUM_SKY_DOME:
		createCaelumSkyDome();
		mListener = new CSkyListener( this, sceneMgr->getCamera("PlayerCam") );
	break;
	default:
		assert(false&&"Wrong SkyType in CSky::createSky(const eSkyType& SkyType)");
	break;
	}
	// register the listener
	root->addFrameListener(mListener);
}

void CSky::createCaelumSkyDome()
{
	if ( !mCaelumSystem )
	{
		Root* root = Root::getSingletonPtr();
		SceneManager* sceneMgr = root->getSceneManager("MainScene");
		Viewport* viewport = sceneMgr->getCamera("PlayerCam")->getViewport();

		//// Pick components to create in the demo.
		//// You can comment any of those and it should still work
		//// Trying to disable one of these can be useful in finding problems.
		//Caelum::CaelumSystem::CaelumComponent componentMask;
		//componentMask = static_cast<Caelum::CaelumSystem::CaelumComponent> (
		//		Caelum::CaelumSystem::CAELUM_COMPONENT_SUN |				
		//		Caelum::CaelumSystem::CAELUM_COMPONENT_MOON |
		//		Caelum::CaelumSystem::CAELUM_COMPONENT_SKY_DOME |
		//		//Caelum::CaelumSystem::CAELUM_COMPONENT_IMAGE_STARFIELD |
		//		Caelum::CaelumSystem::CAELUM_COMPONENT_POINT_STARFIELD |
		//		Caelum::CaelumSystem::CAELUM_COMPONENT_CLOUDS |
		//		0);
		//componentMask = Caelum::CaelumSystem::CAELUM_COMPONENTS_DEFAULT;

		//// Initialise CaelumSystem.
		//mCaelumSystem = new Caelum::CaelumSystem (root, sceneMgr, componentMask);

		//// Set time acceleration.
		//mCaelumSystem->getUniversalClock()->setTimeScale (512);

		//// Register caelum as a listener.
		//RenderWindow* mWindow = root->getAutoCreatedWindow();
		//mWindow->addListener(mCaelumSystem);
		//Root::getSingletonPtr()->addFrameListener(mCaelumSystem);
		////mCaelumSystem->setAutoMoveCameraNode(false);

		//WARNING TEST PURPOSES ONLY
		// Initialise Caelum
		mCaelumSystem = new CaelumSystem (
				root,
				sceneMgr,
				CaelumSystem::CAELUM_COMPONENTS_NONE);

		// Create subcomponents (and allow individual subcomponents to fail).
		try {
			mCaelumSystem->setSkyDome (new SkyDome (sceneMgr, mCaelumSystem->getCaelumCameraNode ()));
		} catch (Caelum::UnsupportedException& ex) {
			Ogre::LogManager::getSingletonPtr()->logMessage("CaelumLab: UnsupportedException: " + ex.getFullDescription ());
		}
		try {
			mCaelumSystem->setSun (new Caelum::SphereSun(sceneMgr, mCaelumSystem->getCaelumCameraNode ()));
		} catch (Caelum::UnsupportedException& ex) {
			Ogre::LogManager::getSingletonPtr()->logMessage("CaelumLab: UnsupportedException: " + ex.getFullDescription ());
		}
		try {
			mCaelumSystem->setMoon (new Caelum::Moon(sceneMgr, mCaelumSystem->getCaelumCameraNode ()));
		} catch (Caelum::UnsupportedException& ex) {
			Ogre::LogManager::getSingletonPtr()->logMessage("CaelumLab: UnsupportedException: " + ex.getFullDescription ());
		}
		try {
			mCaelumSystem->setCloudSystem (new Caelum::CloudSystem (sceneMgr, mCaelumSystem->getCaelumGroundNode ()));
		} catch (Caelum::UnsupportedException& ex) {
			Ogre::LogManager::getSingletonPtr()->logMessage("CaelumLab: UnsupportedException: " + ex.getFullDescription ());
		}
		try {
			mCaelumSystem->setPointStarfield (new PointStarfield (sceneMgr, mCaelumSystem->getCaelumCameraNode ()));
		} catch (Caelum::UnsupportedException& ex) {
			Ogre::LogManager::getSingletonPtr()->logMessage("CaelumLab: UnsupportedException: " + ex.getFullDescription ());
		}

		// Register caelum.
		// Don't make it a frame listener; update it by hand.
		//Root::getSingletonPtr ()->addFrameListener (mCaelumSystem.get ());
		mCaelumSystem->attachViewport(viewport);

		mCaelumSystem->setPrecipitationController (new PrecipitationController (sceneMgr));

		mCaelumSystem->setSceneFogDensityMultiplier (0.0015);
		mCaelumSystem->setManageAmbientLight (true);
		mCaelumSystem->setMinimumAmbientLight (Ogre::ColourValue (0.1, 0.1, 0.1));

		// Test spinning the caelum root node. Looks wrong in the demo;
		// but at least the sky components are aligned with each other.
		if (false) {
			mCaelumSystem->getCaelumCameraNode ()->setOrientation(
					Ogre::Quaternion (Ogre::Radian (Ogre::Math::PI), Ogre::Vector3::UNIT_Z) *
					Ogre::Quaternion (Ogre::Radian (Ogre::Math::PI / 2), Ogre::Vector3::UNIT_X));
			mCaelumSystem->getCaelumCameraNode ()->_update (true, true);
		}

		// Setup sun options
		if (mCaelumSystem->getSun ()) {
			// Make the sun very obvious:
			//mCaelumSystem->getSun ()->setDiffuseMultiplier (Ogre::ColourValue (1, 10, 1));

			mCaelumSystem->getSun ()->setAutoDisableThreshold (0.05);
			mCaelumSystem->getSun ()->setAutoDisable (false);
		}

		if (mCaelumSystem->getMoon ()) {
			// Make the moon very obvious:
			//mCaelumSystem->getMoon ()->setDiffuseMultiplier (Ogre::ColourValue (1, 1, 10));

			mCaelumSystem->getMoon ()->setAutoDisableThreshold (0.05);
			mCaelumSystem->getMoon ()->setAutoDisable (false);
		}

		if (mCaelumSystem->getCloudSystem ()) {
			mCaelumSystem->getCloudSystem ()->createLayerAtHeight(2000);
			mCaelumSystem->getCloudSystem ()->createLayerAtHeight(5000);
			mCaelumSystem->getCloudSystem ()->getLayer(0)->setCloudSpeed(Ogre::Vector2(0.000005, -0.000009));
			mCaelumSystem->getCloudSystem ()->getLayer(1)->setCloudSpeed(Ogre::Vector2(0.0000045, -0.0000085));
		}

		if (mCaelumSystem->getPrecipitationController ()) {
			mCaelumSystem->getPrecipitationController ()->setIntensity (0);
		}

		// Set time acceleration.
		//mCaelumSystem->getUniversalClock ()->setTimeScale (0);

		// Sunrise with visible moon.
		mCaelumSystem->getUniversalClock ()->setGregorianDateTime (2007, 4, 9, 9, 33, 0);
	}
}

void CSky::createOgreSkyPlane()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
    // Define the required skyplane
    Plane plane;
    // 5000 world units from the camera
    plane.d = 5000;
    // Above the camera, facing down
    plane.normal = -Vector3::UNIT_Y;
    // Create the plane 10000 units wide, tile the texture 3 times
    sceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane",10000,3);
}

void CSky::createOgreSkyBox()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
    // Create a skybox
    sceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 50 );
}

void CSky::createOgreSkyDome()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
    // Create a skydome
	sceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
}

void CSky::createPhthahSkyDome()
{
	// all string attributes must be equal to ""
	assert(mMeshName==""&&mMaterialName==""&&mEntityId==""&&mNodeId==""&&"Problem in CSky::createSkyDome()");
	// mSkyDomeEntity must be NULL
	assert(!mSkyDomeEntity&&"Problem in CSky::createSkyDome()");
	// name of the resources are given
	mMeshName = "PhthahSkyDome.mesh";
	mMaterialName = "Examples/CloudySky";
	mEntityId = mNodeId = "PhthahSkyDome";

	Root* root = Root::getSingletonPtr();
	SceneManager* sceneMgr = root->getSceneManager("MainScene");

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

void CSky::deleteSky()
{
	assert(mListener&&"Problem in CSky::deleteSky()");
	Root* root = Root::getSingletonPtr();
	switch ( mSkyType )
	{
	case OGRE_SKY_PLANE:
		deleteOgreSkyPlane();
	break;
	case OGRE_SKY_BOX:
		deleteOgreSkyBox();
	break;
	case OGRE_SKY_DOME:
		deleteOgreSkyDome();
	break;
	case PHTHAH_SKY_DOME:
		deletePhthahSkyDome();
	break;
	case CAELUM_SKY_DOME:
		deleteCaelumSkyDome();
	break;
	default:
		assert(false&&"Wrong SkyType in CSky::deleteSky()");
	break;
	}
	root->removeFrameListener(mListener);
	// don't delete the frameListener since root will manage this itself
	//SAFE_DELETE( mListener )
	mListener = NULL;

}

void CSky::deleteCaelumSkyDome()
{
    assert(mCaelumSystem&&"Problem in CSky::deleteCaelumSkyDome()");
    //mCaelumSystem->shutdown(false);
	SAFE_DELETE( mCaelumSystem )
}

void CSky::deleteOgreSkyPlane()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
	// OgreSkyPlane enabled?
	assert(sceneMgr->isSkyPlaneEnabled()&&"Problem in CSky::deleteOgreSkyPlane()");
    sceneMgr->setSkyPlane(false, Plane(), "");
}

void CSky::deleteOgreSkyBox()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
	// OgreSkyBox enabled?
	assert(sceneMgr->isSkyBoxEnabled()&&"Problem in CSky::deleteOgreSkyBox()");
    sceneMgr->setSkyBox(false, "");
}

void CSky::deleteOgreSkyDome()
{
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
	// OgreSkyDome enabled?
	assert(sceneMgr->isSkyDomeEnabled()&&"Problem in CSky::deleteOgreSkyDome()");
	sceneMgr->setSkyDome(false, "Examples/CloudySky", 5, 8);
}

void CSky::deletePhthahSkyDome()
{
	assert(mSkyDomeEntity&&"Problem in CSky::deletePhthahSkyDome()");
	assert(mMeshName!=""&&mMaterialName!=""&&mEntityId!=""&&mNodeId!=""&&"Problem in CSky::deletePhthahSkyDome()");
	Root* root = Root::getSingletonPtr();
    SceneManager* sceneMgr = root->getSceneManager("MainScene");
	sceneMgr->destroyEntity(mEntityId);
	mSkyDomeEntity = NULL;
	sceneMgr->destroySceneNode(mNodeId);
	mEntityId =	mMaterialName = mMeshName = mNodeId = "";
}

void CSky::switchSkyType()
{
	deleteSky();
	switch ( mSkyType )
	{
	case OGRE_SKY_PLANE:
		mSkyType = OGRE_SKY_BOX;
	break;
	case OGRE_SKY_BOX:
		mSkyType = OGRE_SKY_DOME;
	break;
	case OGRE_SKY_DOME:
		mSkyType = PHTHAH_SKY_DOME;
	break;
	case PHTHAH_SKY_DOME:
		mSkyType = CAELUM_SKY_DOME;
	break;
	case CAELUM_SKY_DOME:
		mSkyType = OGRE_SKY_PLANE;
	break;
	default:
	break;
	}
	createSky(mSkyType);
}