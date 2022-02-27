#ifndef CACHE_SET_FAN_H
#define CACHE_SET_FAN_H

#include "cache_set.h"

class CacheSetFan : public CacheSet
{
public:
    CacheSetFan(CacheBase::cache_t cache_type,
                UInt32 associativity, UInt32 blocksize);
    ~CacheSetFan();

    UInt32 getReplacementIndex(CacheCntlr *cntlr);
    void updateReplacementIndex(UInt32 accessed_index);

private:
    Random m_rand;
    UInt8* m_fan_bits;
    UInt32 findIndexInRest();
};

#endif /* CACHE_SET_RANDOM_H */
