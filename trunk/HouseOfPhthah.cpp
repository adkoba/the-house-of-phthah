#include "HouseOfPhthah.h"

#include <OIS\OIS.h>
#include "OgreConfigFile.h"

// Custom parameter bindings
#define CUSTOM_SHININESS 1
#define CUSTOM_DIFFUSE 2
#define CUSTOM_SPECULAR 3

SceneNode* rotNode;

//class CelShadingListener : public ExampleFrameListener
//{
//protected:
//public:
//    CelShadingListener(RenderWindow* win, Camera* cam)
//        : ExampleFrameListener(win, cam)
//    {
//    }
//
//    bool frameRenderingQueued(const FrameEvent& evt)
//    {
//	if( ExampleFrameListener::frameRenderingQueued(evt) == false )
//		return false;
//
//        rotNode->yaw(Degree(evt.timeSinceLastFrame * 30));
//        return true;
//    }
//};


CHouseOfPhthah::CHouseOfPhthah() :
	m_Root(NULL),
	m_SceneMgr(NULL),
	m_Window(NULL),
	m_Viewport(NULL),
	m_Camera(NULL),
	m_ResourcePath("")
{
}

CHouseOfPhthah::~CHouseOfPhthah()
{
	Exit();
}

void CHouseOfPhthah::Run()
{
	m_Root->startRendering();
}

void CHouseOfPhthah::Start()
{
	Ogre::String pluginsPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
	pluginsPath = m_ResourcePath + "plugins.cfg";
#endif

	m_Root = OGRE_NEW Ogre::Root(pluginsPath, 
		m_ResourcePath + "ogre.cfg", m_ResourcePath + "Ogre.log");

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
	/*if (m_SceneMgr) delete m_SceneMgr;
	if (m_Viewport) delete m_Viewport;
	if (m_Camera) delete m_Camera;
	if (m_Window) delete m_Window;
	if (m_FrameListener) delete m_FrameListener;*/
	if (m_Root!=0) delete m_Root;
}	


/** Configures the application - returns false if the user chooses to abandon configuration. */
void CHouseOfPhthah::configure()
{
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(m_Root->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		m_Window = m_Root->initialise(true);
	}
}

void CHouseOfPhthah::chooseSceneManager()
{
	// Create the SceneManager, in this case a generic one
	m_SceneMgr = m_Root->createSceneManager(Ogre::ST_GENERIC, "ExampleSMInstance");
}
void CHouseOfPhthah::createCamera()
{
	// Create the camera
	m_Camera = m_SceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	m_Camera->setPosition(Ogre::Vector3(0,0,500));
	// Look back along -Z
	m_Camera->lookAt(Ogre::Vector3(0,0,-300));
	m_Camera->setNearClipDistance(5);
}

void CHouseOfPhthah::createFrameListener()
{
	m_FrameListener = new ExampleFrameListener(m_Window, m_Camera);
	m_FrameListener->showDebugOverlay(true);
	m_Root->addFrameListener(m_FrameListener);
}

void CHouseOfPhthah::createScene()
{
//// Check capabilities
//		const RenderSystemCapabilities* caps = Root::getSingleton().getRenderSystem()->getCapabilities();
//        if (!caps->hasCapability(RSC_VERTEX_PROGRAM) || !(caps->hasCapability(RSC_FRAGMENT_PROGRAM)))
//        {
//			OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED, "Your card does not support vertex and fragment programs, so cannot "
//                "run this demo. Sorry!", 
//                "CelShading::createScene");
//        }
//
//        // Create a point light
//        Light* l = m_SceneMgr->createLight("MainLight");
//        // Accept default settings: point light, white diffuse, just set position
//        // Add light to the scene node
//        rotNode = m_SceneMgr->getRootSceneNode()->createChildSceneNode();
//        rotNode->createChildSceneNode(Vector3(20,40,50))->attachObject(l);
//
//        Entity *ent = m_SceneMgr->createEntity("head", "ogrehead.mesh");
//
//        m_Camera->setPosition(20, 0, 100);
//        m_Camera->lookAt(0,0,0);
//
//
//        // Set common material, but define custom parameters to change colours
//        // See Example-Advanced.material for how these are finally bound to GPU parameters
//        SubEntity* sub;
//        // eyes
//        sub = ent->getSubEntity(0);
//        sub->setMaterialName("Examples/CelShading");
//		sub->setCustomParameter(CUSTOM_SHININESS, Vector4(35.0f, 0.0f, 0.0f, 0.0f));
//        sub->setCustomParameter(CUSTOM_DIFFUSE, Vector4(1.0f, 0.3f, 0.3f, 1.0f));
//        sub->setCustomParameter(CUSTOM_SPECULAR, Vector4(1.0f, 0.6f, 0.6f, 1.0f));
//        // skin
//        sub = ent->getSubEntity(1);
//        sub->setMaterialName("Examples/CelShading");
//        sub->setCustomParameter(CUSTOM_SHININESS, Vector4(10.0f, 0.0f, 0.0f, 0.0f));
//        sub->setCustomParameter(CUSTOM_DIFFUSE, Vector4(0.0f, 0.5f, 0.0f, 1.0f));
//        sub->setCustomParameter(CUSTOM_SPECULAR, Vector4(0.3f, 0.5f, 0.3f, 1.0f));
//        // earring
//        sub = ent->getSubEntity(2);
//        sub->setMaterialName("Examples/CelShading");
//        sub->setCustomParameter(CUSTOM_SHININESS, Vector4(25.0f, 0.0f, 0.0f, 0.0f));
//        sub->setCustomParameter(CUSTOM_DIFFUSE, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
//        sub->setCustomParameter(CUSTOM_SPECULAR, Vector4(1.0f, 1.0f, 0.7f, 1.0f));
//        // teeth
//        sub = ent->getSubEntity(3);
//        sub->setMaterialName("Examples/CelShading");
//        sub->setCustomParameter(CUSTOM_SHININESS, Vector4(20.0f, 0.0f, 0.0f, 0.0f));
//        sub->setCustomParameter(CUSTOM_DIFFUSE, Vector4(1.0f, 1.0f, 0.7f, 1.0f));
//        sub->setCustomParameter(CUSTOM_SPECULAR, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
//
//        // Add entity to the root scene node
//        m_SceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
//
//        m_Window->getViewport(0)->setBackgroundColour(ColourValue::White);
}

void CHouseOfPhthah::destroyScene(){}    // Optional to override this

void CHouseOfPhthah::createViewports()
{
	// Create one viewport, entire window
	m_Viewport = m_Window->addViewport(m_Camera);
	m_Viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	m_Camera->setAspectRatio(
		Ogre::Real(m_Viewport->getActualWidth()) / Ogre::Real(m_Viewport->getActualHeight()));
}

/// Method which will define the source of resources (other than current folder)
void CHouseOfPhthah::setupResources()
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(m_ResourcePath + "resources.cfg");

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
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
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
