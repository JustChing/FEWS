
#include "hash.h"

vector< vector<unsigned> > hash_table;
uint32_t Randome_hash_func(uint32_t a)
{
    a = (a+0x479ab41d) + (a<<8);
    a = (a^0xe4aa10ce) ^ (a>>5);
    a = (a+0x9942f0a6) - (a<<14);
    a = (a^0x5aedd67d) ^ (a>>3);
    a = (a+0x17bea992) + (a<<7);
    return a;
}

// BKDR Hash Function
unsigned int BKDRHash(const char* str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(const char* str)
{
    unsigned int hash = 0;
    int i;

    for (i = 0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(const char* str)
{
    unsigned int hash = 5381;

    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(const char* str)
{
    unsigned int hash = 1315423911;

    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash(const char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

void BloomSet1(const char* str)
{
    size_t i1 = BKDRHash(str) % QQQQ;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) % QQQQ;
    size_t i3 = DJBHash(str) % QQQQ;
    size_t i4 = JSHash(str)% QQQQ;
    size_t i5 =  RSHash(str) % QQQQ;

    //在这个位设置为1
    _bitset1.set(i1);
    _bitset1.set(i2);
    _bitset1.set(i3);
    _bitset1.set(i4);
    _bitset1.set(i5);
}

void BloomSet2(const char* str)
{
    size_t i1 = BKDRHash(str) % QQQQ;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) % QQQQ;
    size_t i3 = DJBHash(str) % QQQQ;
    size_t i4 = JSHash(str)% QQQQ;
    size_t i5 =  RSHash(str) % QQQQ;

    //在这个位设置为1
    _bitset2.set(i1);
    _bitset2.set(i2);
    _bitset2.set(i3);
    _bitset2.set(i4);
    _bitset2.set(i5);
}

void BloomSet3(const char* str)
{
    size_t i1 = BKDRHash(str) % QQQQ;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) % QQQQ;
    size_t i3 = DJBHash(str) % QQQQ;
    size_t i4 = JSHash(str)% QQQQ;
    size_t i5 =  RSHash(str) % QQQQ;

    //在这个位设置为1
    _bitset3.set(i1);
    _bitset3.set(i2);
    _bitset3.set(i3);
    _bitset3.set(i4);
    _bitset3.set(i5);
}






bool Bloom_reservoir(const char* str,int a)
{
    size_t i1 = BKDRHash(str) % QQQQ;

    if(a==1)
    {
        if (_bitset1.test(i1) == false)
        {
            return false;
        }

        size_t i2 = APHash(str) % QQQQ;
        if (_bitset1.test(i2) == false)
        {
            return false;
        }

        size_t i3 = DJBHash(str) % QQQQ;
        if (_bitset1.test(i3) == false)
        {
            return false;
        }
        size_t i4 = JSHash(str) % QQQQ;
        if (_bitset1.test(i4) == false)
        {
            return false;
        }
        size_t i5 = RSHash(str) % QQQQ;
        if (_bitset1.test(i5) == false)
        {
            return false;
        }
        return true;

    }else if(a==2)
        {
            if (_bitset2.test(i1) == false)
            {
                return false;
            }

            size_t i2 = APHash(str) % QQQQ;
            if (_bitset2.test(i2) == false)
            {
                return false;
            }

            size_t i3 = DJBHash(str) % QQQQ;
            if (_bitset2.test(i3) == false)
            {
                return false;
            }
            size_t i4 = JSHash(str) % QQQQ;
            if (_bitset2.test(i4) == false)
            {
                return false;
            }
            size_t i5 = RSHash(str) % QQQQ;
            if (_bitset2.test(i5) == false)
            {
                return false;
            }
            return true;
        }else if(a==3)
                {
                    if (_bitset3.test(i1) == false)
                    {
                        return false;
                    }

                    size_t i2 = APHash(str) % QQQQ;
                    if (_bitset3.test(i2) == false)
                    {
                        return false;
                    }

                    size_t i3 = DJBHash(str) % QQQQ;
                    if (_bitset3.test(i3) == false)
                    {
                        return false;
                    }
                    size_t i4 = JSHash(str) % QQQQ;
                    if (_bitset3.test(i4) == false)
                    {
                        return false;
                    }
                    size_t i5 = RSHash(str) % QQQQ;
                    if (_bitset3.test(i5) == false)
                    {
                        return false;
                    }
                    return true;

                }

}















