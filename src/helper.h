/*
	Helper types and constants for helpdeco
*/

#ifndef int16_t
typedef signed short int16_t;
#endif

#ifndef int32_t
typedef signed int int32_t;
#endif

#ifndef int64_t
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef signed __int64 int64_t;
#else
typedef signed long long int64_t;
#endif
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

#ifndef uint16_t
typedef unsigned short uint16_t;
#endif

#ifndef uint32_t
typedef unsigned long uint32_t;
#endif

#ifndef uint64_t
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 uint64_t;
#else
typedef unsigned long long uint64_t;
#endif
#endif

#ifndef NAME_MAX
#define NAME_MAX 255
#endif

#ifndef PATH_MAX
#define PATH_MAX 512
#endif