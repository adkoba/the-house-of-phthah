#include "LocalPlayer.h"
#include "Globals.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>

bool CLocalPlayer::frameStarted(const Ogre::FrameEvent &evt) 
{
	mAnimationState->addTime(evt.timeSinceLastFrame);	
	return true; 
}

CLocalPlayer::CLocalPlayer( Ogre::SceneNode* pHisNode, Ogre::Entity* pHisEntity, const std::string& pHisName )
	: CCharacter(pHisNode, pHisEntity, pHisName)
{
	// Set idle animation
	mAnimationState = mEntity->getAnimationState(CGlobals::IdleAnimName);
	mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

	// Create camera node
	mCameraNode = mNode->createChildSceneNode( CGlobals::PlayerCameraName);
}

CLocalPlayer::~CLocalPlayer() {}

bool CLocalPlayer::mouseMoved(const OIS::MouseEvent &arg) 
{ return true; }

bool CLocalPlayer::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) 
{ return true; }

bool CLocalPlayer::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) 
{ return true; }

bool CLocalPlayer::keyPressed( const OIS::KeyEvent &arg ) 
{ return true; }

bool CLocalPlayer::keyReleased( const OIS::KeyEvent &arg ) 
{ return true; }
