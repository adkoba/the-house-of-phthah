#ifndef _Globals_
#define _Globals_

#ifdef	HOPUTILS_EXPORTS
#define	CGlobalsExport	__declspec( dllexport )
#else
#define	CGlobalsExport	__declspec( dllimport )
#endif

class CGlobalsExport CGlobals
{
public:
	static	float		waterHeight;	
	static	const char*	TerrainCameraName;
	static	const char*	PlayerCameraName;
	
	static	const char*	MainSceneName;
	static	const char*	IdleAnimName;
	static	const char*	WalkAnimName;
};

#endif // _Globals_