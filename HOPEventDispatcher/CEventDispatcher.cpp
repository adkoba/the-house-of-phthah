#include "CEventDispatcher.h"

namespace HOP
{

CEventDispatcher::~CEventDispatcher()
{
	//Remove ourself as a Window listener
	close(mWindow);
	mMouseEvent.erase(mMouseEvent.begin(),mMouseEvent.end());
	mKeyboardEvent.erase(mKeyboardEvent.begin(),mKeyboardEvent.end());
}

CEventDispatcher::CEventDispatcher()
	: mInputManager(NULL)
	, mMouse(NULL)
	, mKeyboard(NULL)
{}

void CEventDispatcher::initialize( Ogre::RenderWindow* pWindow )
{
	if( mInputManager == NULL )
	{
		mWindow = pWindow;

		OIS::ParamList lParamList;
		size_t lWindowHnd = 0;
		std::ostringstream lWindowHndStr;

		// Get the Window Handle
		pWindow->getCustomAttribute("WINDOW", &lWindowHnd);
		lWindowHndStr << lWindowHnd;

		// We add this parameter to the param list
		lParamList.insert(std::make_pair(std::string("WINDOW"), lWindowHndStr.str()));

		// then, we create the InputManager device
		mInputManager = OIS::InputManager::createInputSystem( lParamList );

		//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);

		// Register as a Window Listener
		Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
	}
}

void CEventDispatcher::close( Ogre::RenderWindow* pWindow )
{
	//Only close for window that created OIS (the main window in these demos)
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(pWindow);
}

void CEventDispatcher::registerMouseListerner( const std::string& pListenerName, OIS::MouseListener* pIntr )
{
	if( mMouseEvent.find(pListenerName) == mMouseEvent.end() )
	{
		mMouseEvent[pListenerName] = pIntr;
	}
}
void CEventDispatcher::unregisterMouseListerner( const std::string& pListenerName )
{
	mMouseEvent.erase(pListenerName);
}

void CEventDispatcher::registerKeyboardListerner( const std::string& pListenerName, OIS::KeyListener* pIntr )
{
	if( mKeyboardEvent.find(pListenerName) == mKeyboardEvent.end() )
	{
		mKeyboardEvent[pListenerName] = pIntr;
	}
}

void CEventDispatcher::unregisterKeyboardListerner( const std::string& pListenerName )
{
	mKeyboardEvent.erase(pListenerName);
}

//Adjust mouse clipping area
void CEventDispatcher::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void CEventDispatcher::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mWindow )
	{
		if( mInputManager )
		{
			mInputManager->destroyInputObject( mMouse );
			mInputManager->destroyInputObject( mKeyboard );

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}


} // End of namespace