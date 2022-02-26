#include "cache_set_fan.h"
#include "log.h"

#include <time.h>

// RANDOM: Selects the victim line randomly (from among valid lines)

CacheSetFan::CacheSetFan(
    CacheBase::cache_t cache_type,
    UInt32 associativity, UInt32 blocksize) : CacheSet(cache_type, associativity, blocksize)
{
    m_rand.seed(time(NULL));
}

CacheSetFan::~CacheSetFan()
{
}

UInt32
CacheSetFan::getReplacementIndex(CacheCntlr *cntlr)
{
    // Invalidations may mess up the LRU bits

    for (UInt32 i = 0; i < m_associativity; i++)
    {
        if (!m_cache_block_info_array[i]->isValid())
            return i; // if there is an invalid line, use that line
    }

    UInt32 index = (m_rand.next() % m_associativity);
    if (isValidReplacement(index))
    {
        return index;
    }
    else
    {
        // Could not find valid victim, try again, due to randomness, it might work
        return getReplacementIndex(cntlr);
    }
}

void CacheSetFan::updateReplacementIndex(UInt32 accessed_index)
{
}
