#ifndef __HOP_C_EVENT_DISPATCHER__
#define __HOP_C_EVENT_DISPATCHER__

#include <string>
#include <map>

#include <OgreSingleton.h>
#include "OgreFrameListener.h"
#include "OgreWindowEventUtilities.h"
#include "OIS/OIS.h"
#include "OgreRenderWindow.h"
#include "IEventDispatcher.h"

namespace HOP
{
	/**
	 * \class   CEventDispatcher
	 * \brief   Classe de gestion de l'ordre d'appel des listener
	 * \author  FransTreb
	 * \date    22 nov. 2009
	 *
	 */
	class CEventDispatcher  : public OIS::KeyListener       // To received keyboard notifications
							, public OIS::MouseListener     // To received mouse notifications
							, public Ogre::FrameListener    // To received frame notifications
							, public IEventDispatcher       // To register/unregister modules
							, public Ogre::WindowEventListener	// To received windows events
	{
		private:
			Ogre::RenderWindow* mWindow;
			OIS::InputManager*	mInputManager;
			OIS::Mouse*			mMouse;
			OIS::Keyboard*		mKeyboard;

			typedef std::map<std::string,OIS::MouseListener*> TMapMouseListener;
			typedef std::map<std::string,OIS::KeyListener*> TMapKeyboardListener;
			typedef std::map<std::string,Ogre::FrameListener*> TMapFrameListener;

			TMapMouseListener		mMouseEvent;
			TMapKeyboardListener	mKeyboardEvent;
			TMapFrameListener		mFrameEvent;

		public:
			/**
			 * \brief Destructeur
			 */
			~CEventDispatcher();

			/**
			 * \brief Constructeur
			 */
			CEventDispatcher();

		//
		// Implementation de l'interface IEventDispatcher
		//
			void	initialize(Ogre::RenderWindow* pWindow);
			void	close(Ogre::RenderWindow* pWindow);
			Ogre::FrameListener*	getFrameListener() {return this;}
		//
		// Implementation de l'interface IInputEventDispatcher
		//
			/** 
			 * \brief Register a listener of Mouse Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 *		\param[in] pIntr		 Interface to call
			 */
			void registerMouseListerner( const std::string& pListenerName, OIS::MouseListener* pIntr );
			/** 
			 * \brief Unregister a listener of Mouse Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 */
			void unregisterMouseListerner( const std::string& pListenerName );

			/** 
			 * \brief Register a listener of Keyboard Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 *		\param[in] pIntr		 Interface to call
			 */
			void registerKeyboardListerner( const std::string& pListenerName, OIS::KeyListener* pIntr );
			/** 
			 * \brief Unregister a listener of Keyboard Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 */
			void unregisterKeyboardListerner( const std::string& pListenerName );

		//
		// Implementation de l'interface Ogre::WindowEventListener
		//
			void windowResized(Ogre::RenderWindow* rw);
			/** 
			 * \brief Unattach OIS before window shutdown (very important under Linux)
			 *		\param[in] rm Window
			 */
			void windowClosed(Ogre::RenderWindow* rw);
		//
		// Implementation de l'interface Ogre::FrameListener
		//
			bool frameStarted(const Ogre::FrameEvent& evt) 
			{ 
				bool lReturn = true;
                
				if(mMouse)
					mMouse->capture();
				if(mKeyboard) 
					mKeyboard->capture();

				return lReturn; 
			}

		//
		// Implementation de l'interface OIS::KeyListener
		//
			bool keyPressed( const OIS::KeyEvent & arg )
			{ 
				bool lReturn = true;

				for( TMapKeyboardListener::iterator lIt = mKeyboardEvent.begin(); lIt != mKeyboardEvent.end() && lReturn; lIt++ )
				{
					lReturn = lIt->second->keyPressed(arg);

					if( lReturn == false )
						break;
				}

				return lReturn; 
			}

			bool keyReleased( const OIS::KeyEvent &arg )
			{ 
				bool lReturn = true;

				for( TMapKeyboardListener::iterator lIt = mKeyboardEvent.begin(); lIt != mKeyboardEvent.end() && lReturn; lIt++ )
				{
					lReturn = lIt->second->keyReleased(arg);

					if( lReturn == false )
						break;
				}

				return lReturn; 
			}

		//
		// Implementation de l'interface OIS::MouseListener
		//
			bool mouseMoved( const OIS::MouseEvent &arg )
			{ 
				bool lReturn = true;

				for( TMapMouseListener::iterator lIt = mMouseEvent.begin(); lIt != mMouseEvent.end() && lReturn; lIt++ )
				{
					lReturn = lIt->second->mouseMoved(arg);

					if( lReturn == false )
						break;
				}

				return lReturn; 
			}
			bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
			{ 
				bool lReturn = true;

				for( TMapMouseListener::iterator lIt = mMouseEvent.begin(); lIt != mMouseEvent.end() && lReturn; lIt++ )
				{
					lIt->second->mousePressed(arg,id);

					if( lReturn == false )
						break;
				}

				return lReturn; 
			}
			bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
			{ 
				bool lReturn = true;

				for( TMapMouseListener::iterator lIt = mMouseEvent.begin(); lIt != mMouseEvent.end() && lReturn; lIt++ )
				{
					lIt->second->mouseReleased(arg,id);

					if( lReturn == false )
						break;
				}

				return lReturn; 
			}

	}; /* End of CEventDispatcher */

} /* End of namespace */

#endif //__HOP_C_EVENT_DISPATCHER__