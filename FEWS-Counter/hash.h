
#ifndef HASH_H_
#define HASH_H_


#include "Basic.h"
#include <random>


uint32_t Randome_hash_func(uint32_t a);


// BKDR Hash Function
unsigned int BKDRHash(const char* str);


// AP Hash Function
unsigned int APHash(const char* str);


// DJB Hash Function
unsigned int DJBHash(const char* str);


// JS Hash Function
unsigned int JSHash(const char* str);


// RS Hash Function
unsigned int RSHash(const char *str);


void BloomSet1(const char* str);
void BloomSet2(const char* str);
void BloomSet3(const char* str);

bool Bloom_reservoir(const char* str,int a);



#endif /* HASH_H_ */
