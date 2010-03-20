/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleFrameListener.h
Description: Defines an example frame listener which responds to frame events.
This frame listener just moves a specified camera around based on
keyboard and mouse movements.
Mouse:    Freelook
W or Up:  Forward
S or Down:Backward
A:        Step left
D:        Step right
             PgUp:     Move upwards
             PgDown:   Move downwards
             F:        Toggle frame rate stats on/off
			 R:        Render mode
             T:        Cycle texture filtering
                       Bilinear, Trilinear, Anisotropic(8)
             P:        Toggle on/off display of camera position / orientation
-----------------------------------------------------------------------------
*/

#ifndef __ExampleFrameListener_H__
#define __ExampleFrameListener_H__

#include <Ogre.h>
#include <OgreStringConverter.h>
#include <OgreException.h>

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

namespace HOP
{
	/**
	 * \class   CHOPFrameListener
	 * \brief   Classe de gestion des évènements généraux (capture d'écran, ....). 
	 *			Les évènements gérés ici ne doivent avoir aucune influence sur le
	 *			comportement ou le contenu du jeu.
	 * \author  FransTreb
	 * \date    19 mars 2010
	 */
	class CHOPFrameListener : public Ogre::FrameListener	// Implemente frame listener
							//, public OIS::MouseListener     // Implemente mouse listener
							, public OIS::KeyListener       // Implemente keyboard listener

	{
		public:
			// Constructor takes a RenderWindow because it uses that to determine input context
			CHOPFrameListener( RenderWindow* win );
			virtual ~CHOPFrameListener();

			void showDebugOverlay(bool show)
			{
				if (mDebugOverlay)
				{
					if (show)
						mDebugOverlay->show();
					else
						mDebugOverlay->hide();
				}
			}

			//
			// Implémentation de l'interface MouseListener
			//
			
				//bool mouseMoved( const OIS::MouseEvent &arg );
				//bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
				//bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

			//
			// Implémentation de l'interface KeyListener
			//

				bool keyPressed( const OIS::KeyEvent &arg );
				bool keyReleased( const OIS::KeyEvent &arg ) {return true;}

			//
			// Implémentation de l'interface KeyListener
			//
				bool frameRenderingQueued(const FrameEvent& evt);
				bool frameEnded(const FrameEvent& evt) { updateStats(); return !mQuit; }

	protected:
		virtual void updateStats();

	protected:
		RenderWindow*	mWindow;
		bool			mStatsOn;
		bool			mQuit;
		std::string		mDebugText;

		unsigned int	mNumScreenShots;
		// just to stop toggles flipping too fast
		TextureFilterOptions mFiltering;
		int				mAniso;

		int				mSceneDetailIndex ;
		Overlay*		mDebugOverlay;
	};
}	// End of namespace HOP
#endif
