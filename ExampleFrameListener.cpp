#include "ExampleFrameListener.h"
 #include "HouseOfPhthah.h"

// Override frameRenderingQueued event to process that (don't care about frameEnded)
bool ExampleFrameListener::frameRenderingQueued(const FrameEvent& evt)
{

	if(mWindow->isClosed())	return false;

	mSpeedLimit = mMoveScale * evt.timeSinceLastFrame;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();
	if( mJoy ) mJoy->capture();

	bool buffJ = (mJoy) ? mJoy->buffered() : true;

	Ogre::Vector3 lastMotion = mTranslateVector;

	//Check if one of the devices is not buffered
	if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
	{
		// one of the input modes is immediate, so setup what is needed for immediate movement
		if (mTimeUntilNextToggle >= 0)
			mTimeUntilNextToggle -= evt.timeSinceLastFrame;

		// Move about 100 units per second
		mMoveScale = mMoveSpeed * evt.timeSinceLastFrame;
		// Take about 10 seconds for full rotation
		mRotScale = mRotateSpeed * evt.timeSinceLastFrame;

		mRotX = 0;
		mRotY = 0;
		mTranslateVector = Ogre::Vector3::ZERO;

	}

	//Check to see which device is not buffered, and handle it
	if( !mKeyboard->buffered() )
		if( processUnbufferedKeyInput(evt) == false )
			return false;
	if( !mMouse->buffered() )
		if( processUnbufferedMouseInput(evt) == false )
			return false;

	// ramp up / ramp down speed
	if (mTranslateVector == Ogre::Vector3::ZERO)
	{
		// decay (one third speed)
		mCurrentSpeed -= evt.timeSinceLastFrame * 0.3;
		mTranslateVector = lastMotion;
	}
	else
	{
		// ramp up
		mCurrentSpeed += evt.timeSinceLastFrame;

	}
	// Limit motion speed
	if (mCurrentSpeed > 1.0)
		mCurrentSpeed = 1.0;
	if (mCurrentSpeed < 0.0)
		mCurrentSpeed = 0.0;

	mTranslateVector *= mCurrentSpeed;


	if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
	{
		moveCamera();
		// and then move the skydome (it must exist)
		SceneManager* sceneMgr = Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;
		sceneMgr->getSceneNode("PhthahSkyDomeNode")->setPosition(mCamera->getDerivedPosition() - Ogre::Vector3(0,50,0)); // trick to make the sky closer to the camera, thus camera can't easily see the void under the terrain
	}

	return true;
}