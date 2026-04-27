//***************************************************************************************

#pragma once
#include "FibonacciNumber.h"
#include "RandomNumbersGenerator.h"

//***************************************************************************************

class RandomFibonacciNumbersGenerator
{
public:

  RandomFibonacciNumbersGenerator(size_t maxCacheSize);

  FibonacciNumber New();

  class CacheItem : public FibonacciNumber
  {
  public:
    size_t m_counter = 1;
    std::chrono::system_clock::time_point m_time{};
  };

  size_t GetCacheSize() const { return m_cache.size(); }

  const CacheItem& GetCacheItem(size_t i) const { return m_cache[i]; }  

  uint32_t GetMinKey() const { return m_keyGenerator.GetMin(); }
  uint32_t GetMaxKey() const { return m_keyGenerator.GetMax(); }

private:

  RandomNumbersGenerator m_keyGenerator;

  size_t m_maxCacheSize;

  std::vector<CacheItem> m_cache; // LRU (Least Recently Used) cache

  uint64_t ComputeValue(uint32_t key);

  uint64_t LookUpCache(uint32_t key);

  void AddToCache(uint32_t key, uint64_t value);
};

//***************************************************************************************
