#include "SkyDome.h"

CSkyDome::CSkyDome(	const Ogre::String& MaterialName,
					const Ogre::Real& Curv,
					const Ogre::Real& Tiling,
					const Ogre::Real& Distance):
    mPath(MaterialName)
{
	mParam.skyDomeCurvature = Curv;
	mParam.skyDomeTiling = Tiling;
	mParam.skyDomeDistance = Distance;
}

	CSkyDome::CSkyDome(const CSkyDome& Copy):
	mPath(Copy.mPath),
	mParam(Copy.mParam)
{
}

CSkyDome::~CSkyDome()
{
}

void CSkyDome::push(Ogre::SceneManager* SceneMgr, const bool& Enable, const bool& DrawFirst)
{
	SceneMgr->setSkyDome(Enable, mPath, mParam.skyDomeCurvature, mParam.skyDomeTiling, mParam.skyDomeDistance, DrawFirst);
}