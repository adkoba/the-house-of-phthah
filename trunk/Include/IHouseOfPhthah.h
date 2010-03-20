#ifndef __I_HOUSE_OF_PHTHAH_H__
#define __I_HOUSE_OF_PHTHAH_H__

namespace HOP
{
	class CCamera;
}

class IHouseOfPhthah
{
public:
	virtual HOP::CCamera*		getCamera()		= 0;
	virtual Ogre::SceneManager*	getSceneMgr()	= 0;
	virtual Ogre::Root*			getRoot()		= 0;
};

#endif // __I_HOUSE_OF_PHTHAH_H__