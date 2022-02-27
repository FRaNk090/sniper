#include "cache_set_fan.h"
#include "log.h"

#include <time.h>

// RANDOM: Selects the victim line randomly (from among valid lines)

int num_cache = 0;
int num_cache_destory = 0;

CacheSetFan::CacheSetFan(
    CacheBase::cache_t cache_type,
    UInt32 associativity, UInt32 blocksize) : CacheSet(cache_type, associativity, blocksize)
{
    // num_cache++;
    // printf("in cacheset Fan: %i\n", num_cache);
    m_rand.seed(time(NULL));
    m_fan_bits = new UInt8[2];
    for (UInt32 i = 0; i < 2; i++)
        m_fan_bits[i] = i;
}

CacheSetFan::~CacheSetFan()
{
    // num_cache_destory++;
    // printf("in ~CacheSetFan: %i\n", num_cache_destory);
    delete[] m_fan_bits;
}

UInt32
CacheSetFan::getReplacementIndex(CacheCntlr *cntlr)
{
    // Invalidations may mess up the Fan bits
    printf("In get replcement indec");
    UInt32 candidate;
    for (UInt32 i = 0; i < m_associativity; i++)
    {
        if (!m_cache_block_info_array[i]->isValid())
        {
            if (i == m_fan_bits[0] || i == m_fan_bits[1])
            {
                candidate = findIndexInRest();
            }
            else
            {
                return i;
            }
            UInt32 second_lru = m_fan_bits[1];
            m_fan_bits[1] = candidate;

            if (i == m_fan_bits[0])
            {
                m_fan_bits[0] = second_lru;
            }

            return i;
            // if there is an invalid line, use that line
        }
    }

    candidate = m_fan_bits[0];

    UInt32 next_candidate = findIndexInRest();

    m_fan_bits[0] = m_fan_bits[1];
    m_fan_bits[1] = next_candidate;

    return candidate;

    // UInt32 index = (m_rand.next() % m_associativity);
    // if (isValidReplacement(index))
    // {
    //     return index;
    // }
    // else
    // {
    //     // Could not find valid victim, try again, due to randomness, it might work
    //     return getReplacementIndex(cntlr);
    // }
}

void CacheSetFan::updateReplacementIndex(UInt32 accessed_index)
{
}

UInt32 CacheSetFan::findIndexInRest()
{
    printf("Finding index\n");
    UInt32 index = (m_rand.next() % m_associativity);
    printf("%i and %i but selected %i\n", m_fan_bits[0], m_fan_bits[1], index);
    printf("associativity is %i\n", m_associativity);
    if (isValidReplacement(index) && index != m_fan_bits[0] && index != m_fan_bits[1])
    {
        return index;
    }
    else
    {
        // Could not find valid victim, try again, due to randomness, it might work
        return findIndexInRest();
    }
}
