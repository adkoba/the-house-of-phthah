#ifndef _MACROS_
#define _MACROS_

#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } }

#endif