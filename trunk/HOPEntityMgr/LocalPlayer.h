#ifndef _C_LOCAL_PLAYER_
#define _C_LOCAL_PLAYER_

#include "Character.h"

class CLocalPlayer : public CCharacter
				   , public OIS::KeyListener
				   , public OIS::MouseListener
{
private:
	Ogre::SceneNode*		mCameraNode;

public:
	CLocalPlayer( Ogre::SceneNode* pHisNode, Ogre::Entity* pHisEntity, const std::string& pHisName );
		
	~CLocalPlayer();

	bool frameStarted(const Ogre::FrameEvent &evt);
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	bool keyPressed( const OIS::KeyEvent &arg );
	bool keyReleased( const OIS::KeyEvent &arg );
};

#endif // _C_LOCAL_PLAYER_