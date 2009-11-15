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

class ExampleFrameListener: public FrameListener, public WindowEventListener
{
	enum CameraMode
	{
		FlyingCamera, 
		PlayerCamera
	};

public:
	// Constructor takes a RenderWindow because it uses that to determine input context
	ExampleFrameListener(	RenderWindow* win,
							Camera* cam,
							bool bufferedKeys = false,
							bool bufferedMouse = false,
							bool bufferedJoy = false );
	virtual ~ExampleFrameListener();

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt);

	virtual bool processUnbufferedMouseInput(const FrameEvent& evt)
	{

		// Rotation factors, may not be used if the second mouse button is pressed
		// 2nd mouse button - slide, otherwise rotate
		const OIS::MouseState &ms = mMouse->getMouseState();
		if( ms.buttonDown( OIS::MB_Right ) )
		{
			mTranslateVector.x += ms.X.rel * 0.13;
			mTranslateVector.y -= ms.Y.rel * 0.13;
		}
		else if( ms.buttonDown( OIS::MB_Left ) ) /* PAN */
		{

		}
		else /* Rotation */
		{
			mRotX = Degree(-ms.X.rel * 0.13);
			mRotY = Degree(-ms.Y.rel * 0.13);
		}

		return true;
	}

	virtual void moveCamera()
	{
		// Make all the changes to the camera
		// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
		//(e.g. airplane)
		if( mCameraMode == FlyingCamera )
		{
			mCamera->yaw(mRotX);
			mCamera->pitch(mRotY);
			mCamera->moveRelative(mTranslateVector);
		}
	}

	virtual void showDebugOverlay(bool show)
	{
		if (mDebugOverlay)
		{
			if (show)
				mDebugOverlay->show();
			else
				mDebugOverlay->hide();
		}
	}

	// Override frameRenderingQueued event to process that (don't care about frameEnded)
	bool frameRenderingQueued(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt) { updateStats(); return true; }
	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw);
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw);

protected:
	virtual void updateStats();

protected:
	Camera*			mCamera;
	CameraMode		mCameraMode;
	Vector3			mTranslateVector;
	Real			mCurrentSpeed;
	RenderWindow*	mWindow;
	bool			mStatsOn;

	std::string		mDebugText;

	unsigned int	mNumScreenShots;
	float			mMoveScale;
	float			mSpeedLimit;
	Degree			mRotScale;
	// just to stop toggles flipping too fast
	Real			mTimeUntilNextToggle ;
	Radian			mRotX,
					mRotY;
	TextureFilterOptions mFiltering;
	int				mAniso;

	int				mSceneDetailIndex ;
	Real			mMoveSpeed;
	Degree			mRotateSpeed;
	Overlay*		mDebugOverlay;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*		mMouse;
	OIS::Keyboard*	mKeyboard;
	OIS::JoyStick*	mJoy;
};

#endif
