#include "HOPCamera.h"
#include "HOPEventDispatcher.h"
#include "Globals.h"

#include <Ogre.h>
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "OgreCommon.h"

namespace HOP
{
	
CCamera::CCamera( Ogre::SceneManager* pSceneMgr )
    : mSceneDetailIndex(0)
	, mSceneMgr(pSceneMgr)
	, mMove(150)
	, mRotate(0.13)
	, mDisplayCameraDetails(false)
	, mDisplayCameraMode(false)
	, mDebugText("")
	, mTimeUntilNextToggle(0)
{
	mCamera = pSceneMgr->createCamera(CGlobals::TerrainCameraName);

	// Position it at 500 in Z direction
	mCamera->setNearClipDistance(5);

	mCamNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(CGlobals::TerrainCameraName,mCamera->getPosition());
	mCamNode->attachObject(mCamera);
	mCamNode->setPosition(Ogre::Vector3(128,25,128));

	mCameraMode = CCamera::FlyingCamera;
    
    HOP::CHOPEventDispatcher::getEventDispatcher()->registerMouseListerner("HOPCamera",this);
    HOP::CHOPEventDispatcher::getEventDispatcher()->registerKeyboardListerner("HOPCamera",this);

	mDirection = Ogre::Vector3::ZERO;
}

CCamera::~CCamera()
{
    HOP::CHOPEventDispatcher::getEventDispatcher()->unregisterKeyboardListerner("Camera");
    HOP::CHOPEventDispatcher::getEventDispatcher()->unregisterMouseListerner("Camera");
}


bool CCamera::mouseMoved( const OIS::MouseEvent &arg )                           
{ 
	mCamNode->yaw(Ogre::Degree(-mRotate * arg.state.X.rel), Ogre::Node::TS_WORLD);
    mCamNode->pitch(Ogre::Degree(-mRotate * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
	
	return true;
}

bool CCamera::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )  
{ return true; }

bool CCamera::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{ return true; }

bool CCamera::keyPressed( const OIS::KeyEvent &arg )
{ 
	if( arg.key == OIS::KC_M )
	{
		mDisplayCameraMode = !mDisplayCameraMode;
		if (!mDisplayCameraMode)
			mDebugText = "";
	}

    // Changement du mode d'affichage de la scene
    if( arg.key == OIS::KC_R )
	{
		mSceneDetailIndex = (mSceneDetailIndex+1)%3 ;
		switch(mSceneDetailIndex) 
        {
			case 0 : mCamera->setPolygonMode(Ogre::PM_SOLID); break;
			case 1 : mCamera->setPolygonMode(Ogre::PM_WIREFRAME); break;
			case 2 : mCamera->setPolygonMode(Ogre::PM_POINTS); break;
		}
	}
    
    // Change camera state
    if( arg.key == OIS::KC_1 && mCameraMode != FlyingCamera )
    {
        mCamera->getParentSceneNode()->detachObject(mCamera);
        mCamNode = mSceneMgr->getSceneNode(CGlobals::TerrainCameraName);
        mCamNode->attachObject(mCamera);
        
        mCameraMode = FlyingCamera;
    }
    
    // Change camera state
    if( arg.key == OIS::KC_2 && mCameraMode != PlayerCamera )
    {
        mCamera->getParentSceneNode()->detachObject(mCamera);
        mCamNode = mSceneMgr->getSceneNode(CGlobals::PlayerCameraName);
        mCamNode->attachObject(mCamera);
        
        mCameraMode = PlayerCamera;
    }
    
    // Déplacement de la caméra
    if( mCameraMode == FlyingCamera )
    {
        switch( arg.key )
        {
            case OIS::KC_UP:
                mDirection.z = -mMove;
                break;
     
            case OIS::KC_DOWN:
                mDirection.z = mMove;
                break;

            case OIS::KC_LEFT:
                mDirection.x = -mMove;
                break;

            case OIS::KC_RIGHT:
                mDirection.x = mMove;
                break;

            case OIS::KC_PGDOWN:
                mDirection.y = -mMove;
                break;
     
            case OIS::KC_PGUP:
                mDirection.y = mMove;
                break; 
        }
    }

	if(arg.key == OIS::KC_P)
	{
		mDisplayCameraDetails = !mDisplayCameraDetails;
		if (!mDisplayCameraDetails)
			mDebugText = "";
	}
    return true; 
}

bool CCamera::keyReleased( const OIS::KeyEvent &arg )
{
    if( mCameraMode == FlyingCamera )
    {
        switch( arg.key )
        {
            case OIS::KC_UP:
            case OIS::KC_DOWN:
                mDirection.z = 0;
                break;
     
            case OIS::KC_LEFT:
            case OIS::KC_RIGHT:
                mDirection.x = 0;
                break;

            case OIS::KC_PGDOWN:
            case OIS::KC_PGUP:
                mDirection.y = 0;
                break; 
        }
    }

    return true;
}

bool CCamera::frameStarted(const Ogre::FrameEvent& evt)
{
	mCamNode->translate(mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	Ogre::Ray lCameraRay(Ogre::Vector3(mCamNode->getPosition().x, 5000.0f, mCamNode->getPosition().z), Ogre::Vector3::NEGATIVE_UNIT_Y);
	Ogre::RaySceneQuery* lRaySceneQuery = mSceneMgr->createRayQuery(lCameraRay);

	Ogre::RaySceneQueryResult & lResult = lRaySceneQuery->execute();
	
	Ogre::RaySceneQueryResult::iterator lIt = lResult.begin();
	if( lIt != lResult.end() && lIt->worldFragment && lIt->worldFragment->singleIntersection.y > mCamNode->getPosition().y )
	{
		mCamNode->setPosition( mCamNode->getPosition().x, lIt->worldFragment->singleIntersection.y, mCamNode->getPosition().z);
	}

	return true;
}

std::string CCamera::getCameraMode() const
{
	switch( mCameraMode )
	{
		case FlyingCamera: return "FlyingCamera";
			break;
		case PlayerCamera: return "PlayerCamera";
			break;
		default: return "UnknownMode !!!!";
			break;
	}
}

bool CCamera::frameEnded(const Ogre::FrameEvent& evt)
{
	if(mDisplayCameraDetails)
	{
		mDebugText = "CAM - P : " + Ogre::StringConverter::toString(mCamera->getDerivedPosition()) +
					 " " + "O : " + Ogre::StringConverter::toString(mCamera->getDerivedOrientation());
	}

	if( mDisplayCameraMode )
	{
		mDebugText += "\n CAM - Mode: " + getCameraMode();
	}
	
	if( mDebugText != "")
	{
		Ogre::OverlayElement* guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(mDebugText);
	}

	return true;
}

}