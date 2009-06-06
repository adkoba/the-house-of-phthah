#include <Ogre.h>
#include <OIS\OIS.h>

#include "HouseOfPhthah.h"

//#ifdef _UNICODE
//#define _T(x)      L ## x
//#else /* _UNICODE */
//#define _T(x)      x
//#endif /* _UNICODE */

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
	{
	try {
		CHouseOfPhthah houseOfPhthah;
		houseOfPhthah.Start ();
		houseOfPhthah.Run() ;
		houseOfPhthah.Exit();
		} catch( Ogre::Exception &e ) { 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
			MessageBox( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			fprintf(stderr, "An exception has occurred: %s\n",
				e.what());
#endif
		}

	return 0;
	}
