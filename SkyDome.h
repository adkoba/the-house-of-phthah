#ifndef _SkyDome_
#define _SkyDome_

#include <Ogre.h>

class CSkyDome
{
public:
	CSkyDome(const Ogre::String& MaterialName = "");
	CSkyDome(const CSkyDome& Copy);
	~CSkyDome();
	const Ogre::String& getPath() const { return mPath; };
	void push(bool enable = true);
	void setPath(const Ogre::String& Path) { mPath = Path; };
	void setSkyDome(const Ogre::String &materialName);

private:
	Ogre::Entity* mSkyDomeEntity;
	Ogre::String		mPath;
};

#endif // _SkyDome_