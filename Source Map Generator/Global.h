#ifndef _GLOBAL_INCLUDED_
#define _GLOBAL_INCLUDED_


#define TSMG_VERSION	"0.1"
#define TSMG_STATUS		"alpha"

#define TSMG_NIMP		// Not IMPlemented function/parameter
#define TSMG_RECURSIVE	// Function is recursive.


#define TSMG_NAME		TyphoonSMG
#define TSMG_BEGIN		namespace TSMG_NAME {
#define TSMG_END		}
#define TSMG			TSMG_NAME::

// Typhoon Source Map Generator
TSMG_BEGIN
TSMG_END

#pragma comment(lib, "utils/utils30.lib")


#endif