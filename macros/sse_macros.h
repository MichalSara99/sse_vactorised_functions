#pragma once
#if !defined(_SSE_MACROS)
#define _SSE_MACROS




#define SSE_ASSERT(condition, message){\
do {\
if(!(condition)){\
std::cerr << "Assertion `" #condition "` failed in " << __FILE__\
<< " line " << __LINE__ << ": " << message << std::endl;\
std::terminate();\
}\
} while (false);\
}\



#endif ///_SSE_MACROS