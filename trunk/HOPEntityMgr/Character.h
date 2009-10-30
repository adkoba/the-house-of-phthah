#ifndef _Character_
#define _Character_

#include <string>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <OgreRoot.h>
#include <OgreFrameListener.h>

#include "Globals.h"

class CCharacter
{
public:
	CCharacter()
		: mNode(NULL)
		, mEntity(NULL)
		, mName(NULL)
	{}

	CCharacter(Ogre::SceneNode* pHisNode, Ogre::Entity* pHisEntity, const std::string& pHisName)
		: mNode(pHisNode)
		, mEntity(pHisEntity)
		, mName(pHisName)
	{}

	~CCharacter() {}

protected:
	Ogre::SceneNode*	mNode;
	Ogre::Entity*		mEntity;
	std::string			mName;
	Ogre::AnimationState*		mAnimationState; // The current animation state of the object
};


#endif // _Character_