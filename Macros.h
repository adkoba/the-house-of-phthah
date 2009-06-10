#ifndef _MACROS_
#define _MACROS_

#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } }

#define ASSERT(p,string) { if(!p) MessageBox(NULL, string, "Assert Failure", MB_ICONERROR);  \
	assert(p); \
	}

#endif