#ifndef _HASH_H_
#define _HASH_H_

#include <string>
unsigned int BKDRHash(const std::string& str);
unsigned int BKDRHash2(const char* pStr);
unsigned int BKDRHash3( const char* pData,unsigned int DataLen );
unsigned long long MurmurHash64B ( const void * key, int len, unsigned int seed );
unsigned long long MurmurHash64A ( const void * key, int len, unsigned int seed );

#endif

