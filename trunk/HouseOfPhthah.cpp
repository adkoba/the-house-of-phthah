#include "HouseOfPhthah.h"

// Init Singleton:
template<> CHouseOfPhthah* Ogre::Singleton<CHouseOfPhthah>::ms_Singleton = 0;
CHouseOfPhthah* CHouseOfPhthah::getSingletonPtr(void)
{
    return ms_Singleton;
}
CHouseOfPhthah& CHouseOfPhthah::getSingleton(void)
{  
    assert( ms_Singleton );  return ( *ms_Singleton );  
}



CHouseOfPhthah::CHouseOfPhthah() :
	mRoot(NULL),
	mSceneMgr(NULL),
	mWindow(NULL),
	mViewport(NULL),
	mCamera(NULL),
	mResourcePath("")
{
}

CHouseOfPhthah::~CHouseOfPhthah()
{
	Exit();
}

void CHouseOfPhthah::Run()
{
	mRoot->startRendering();
}

void CHouseOfPhthah::Start()
{
	Ogre::String pluginsPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
	pluginsPath = mResourcePath + "plugins.cfg";
#endif

	mRoot = OGRE_NEW Ogre::Root(pluginsPath, 
		mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");

	setupResources();

	configure();

	chooseSceneManager();
	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();
}

void CHouseOfPhthah::Exit()
{
	/*if (mSceneMgr) delete mSceneMgr;
	if (mViewport) delete mViewport;
	if (mCamera) delete mCamera;
	if (mWindow) delete mWindow;
	if (mFrameListener) delete mFrameListener;*/
	//if (mRoot!=0) delete mRoot;
}	


/** Configures the application - returns false if the user chooses to abandon configuration. */
void CHouseOfPhthah::configure()
{
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(mRoot->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true);
	}
}

void CHouseOfPhthah::chooseSceneManager()
{
	// Create the SceneManager, in this case a generic one
	//mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "House Of Phthah");
	//mSceneMgr = static_cast<Phthah::CSceneManager*>(mRoot->createSceneManager("TerrainSceneManager"));
	mSceneMgr = mRoot->createSceneManager("TerrainSceneManager");
}
void CHouseOfPhthah::createCamera()
{
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(128,25,128));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);
}

void CHouseOfPhthah::createFrameListener()
{
	mFrameListener = new ExampleFrameListener(mWindow, mCamera);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}

// Init Rendering stuff
void CHouseOfPhthah::createScene()
{
		// Set ambient light
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

        // Create a light
        Light* light = mSceneMgr->createLight("MainLight");
        light->setPosition(20,80,50);

		// Fog
		/*ColourValue fadeColour(0.93, 0.86, 0.76);
        mSceneMgr->setFog( FOG_LINEAR, fadeColour, .001, 500, 1000);
        mWindow->getViewport(0)->setBackgroundColour(fadeColour);*/
		
		// Create a skydome
		mSkyDome.setMaterialName("Examples/CloudySky");
		mSkyDome.setMeshName("PhthahSkyDome.mesh");
		mSkyDome.createSkyDome();
		//mSceneMgr->setTrueSkyDome(true,"Examples/CloudySky");
		
		// Load terrain:
		std::string terrain_cfg("terrain.cfg");
        mTerrain.Init( terrain_cfg );

		//mRaySceneQuery = mSceneMgr->createRayQuery(
          //  Ray(mCamera->getPosition(), Vector3::NEGATIVE_UNIT_Y));
		

		//// Set a nice viewpoint
  //      mCamera->setPosition(707,2500,528);
        mCamera->setOrientation(Quaternion(-0.3486, 0.0122, 0.9365, 0.0329));

		
		Entity *ent;
		ent = mSceneMgr->createEntity("head", "ogrehead.mesh");
		// Attach to child of root node, better for culling (otherwise bounds are the combination of the 2)
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

}

void CHouseOfPhthah::destroyScene(){}

void CHouseOfPhthah::createViewports()
{
	// Create one viewport, entire window
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
}

/// Method which will define the source of resources (other than current folder)
void CHouseOfPhthah::setupResources()
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORmAPPLE
			// OS X does not set the working directory relative to the app,
			// In order to make things portable on OS X we need to provide
			// the loading with it's own bundle path location
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				String(macBundlePath() + "/" + archName), typeName, secName);
#else
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
													archName, typeName, secName);
#endif
		}
	}
}

//// Optional override method where you can create resource listeners (e.g. for loading screens)
void CHouseOfPhthah::createResourceListener(void)
{
	
}

/// Optional override method where you can perform resource group loading
/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
void CHouseOfPhthah::loadResources()
{
	// Initialise, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}
