
/**
	\author Natesh Narain
	\date Nov 12 2016
*/

#ifndef GAMEBOYCORE_API_H
#define GAMEBOYCORE_API_H

/* DLL Export/Import */

#ifdef _MSC_VER
#	ifdef GAMEBOYCORE_EXPORT
#		define GAMEBOYCORE_API __declspec(dllexport)
#	else
#		define GAMEBOYCORE_API __declspec(dllimport)
#	endif
#else
#	define GAMEBOYCORE_API
#endif

#endif
