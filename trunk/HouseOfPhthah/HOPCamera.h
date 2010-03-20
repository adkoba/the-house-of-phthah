#ifndef __HOP_CAMERA_H__
#define __HOP_CAMERA_H__

// Forward declaration
#include "OgreVector3.h"
#include "OgreFrameListener.h"
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

namespace Ogre
{
	class SceneNode;
	class Camera;
	class SceneManager;
}

namespace HOP
{
	/**
	 * \class   CCamera
	 * \brief   Definition d'une classe de gestion de camera pour HOP
	 * \author  FransTreb
	 * \date    19 nov. 2009
	 *
	 * Dans la version de Ogre que l'on utilise, on ne peut définir qu'une seule
	 * caméra. Pour pouvoir regler different point de vue, on utilise des noeuds
	 * de scenes entre lesquels on switche au moment voulue. 
	 * 
	 * Cette classe permet de définir les actions à réaliser sur les caméras en 
	 * fonction du mode d'affichage dans lequel on est. Dès qu'un noeud de scene
	 * de caméra est ajouté, il faut ajouter dans cette classe les éléments de 
	 * manipulation de la caméra dans ce nouveau mode.
	 *
	 * Normalement cette classe devrait-être un singleton vu que l'on ne doit pas
	 * avoir plusieurs instance de celle-ci dans l'application. Cependant il n'y
	 * a aucune raison pour l'instant qu'elle soit accessible depuis d'autres
	 * modules ou d'autres classes. De ce fait on assume que seule la classe CHouseOfPhthah
	 * en créra une instance.
	 */
	class CCamera : public Ogre::FrameListener    // Implemente frame events
                  , public OIS::MouseListener     // Implemente mouse events
                  , public OIS::KeyListener       // Implemente keyboard events
	{
		private:
			enum CameraModeEnum
			{
				FlyingCamera,   /*!< Camera libre de se déplacer dans toute la scène */
				PlayerCamera    /*!< Camera attachée au joueur de la partie */
			};

			/**! Mode d'affichage de la camera */
			CameraModeEnum		mCameraMode;
			/**! Pointeur sur le noeud de scene de la camera en cours de manipulation */
			Ogre::SceneNode*	mCamNode;
			/**! Current camera */
			Ogre::Camera*		mCamera;
            /**! Deplacement a appliquer a la camera en mode Flying */
            Ogre::Vector3       mDirection;

			float				mTimeUntilNextToggle;
            /**! Mode d'affichage de la scene */
            int                 mSceneDetailIndex;
			Ogre::Real			mMove;			// The move constant
			Ogre::Real			mRotate;        // The rotate constant
			bool				mDisplayCameraDetails;			// Used to knwon is we do display camera position or not
			std::string			mDebugText;		// String used to display camera position
			bool				mDisplayCameraMode;	// True if need to display camera mode
			Ogre::SceneManager* mSceneMgr;

		public:

			/**
             * \brief Constructeur
			 *		\param[in] pSceneMgr	Scene manager
			 *
			 * Créé une camera en mode Flying.
             */
            CCamera( Ogre::SceneManager* pSceneMgr );

			/**
             * \brief Destructeur
             */
            ~CCamera();
            
			/**
			 * \brief Get the camera
			 *		\return Camera utilisé par l'application
			 */
			Ogre::Camera* getOgreCamera() {return mCamera;}

			/**
			 * \brief Get camera mode
			 *		\return Camera mode in string format
			 */
			std::string getCameraMode() const;

		//
		// Implémentation de l'interface MouseListener
		//
		
			bool mouseMoved( const OIS::MouseEvent &arg );
			bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		//
		// Implémentation de l'interface KeyListener
		//

			bool keyPressed( const OIS::KeyEvent &arg );
			bool keyReleased( const OIS::KeyEvent &arg );

		//
		// Implémentation de l'interface FrameListener
		//
			bool frameStarted(const Ogre::FrameEvent& evt);
			bool frameEnded(const Ogre::FrameEvent& evt);
	};	// End of classe CCamera

}	// End of namespace HOP

#endif /* __HOP_CAMERA_H__ */
