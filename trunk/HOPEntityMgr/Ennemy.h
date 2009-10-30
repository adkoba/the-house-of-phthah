#ifndef _C_ENNEMY_
#define _C_ENNEMY_

#include "Character.h"

class CEnnemy : public CCharacter
{
private:
	//! FrameListener which schedule its actions
	//CEnnemiesFrameListener*	mFrameListener;

public:
	CEnnemy( Ogre::SceneNode* pHisNode, Ogre::Entity* pItsEntity, const std::string& pItsName )
		: CCharacter(pHisNode, pItsEntity, pItsName)
	{}

	~CEnnemy() 
	{
		//mFrameListener = NULL;
	}
};

#endif // _C_ENNEMY_