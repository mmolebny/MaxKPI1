//***************************************************************************************

#include "pch.h"
#include "RandomFibonacciNumbersGenerator.h"

//***************************************************************************************

RandomFibonacciNumbersGenerator::RandomFibonacciNumbersGenerator(size_t maxCacheSize) :
  m_maxCacheSize(maxCacheSize), m_keyGenerator(1, 93)
{
  m_cache.reserve(maxCacheSize);
}

//***************************************************************************************

FibonacciNumber RandomFibonacciNumbersGenerator::New()
{
  uint32_t key = m_keyGenerator.New();

  if (key == 0) return { 0, 0 };
  if (key == 1) return { 1, 1 };

  uint64_t value = LookUpCache(key);

  if (value == 0) // not found in cache
  {
    value = ComputeValue(key);

    AddToCache(key, value);
  }

  return { key, value };
}

//***************************************************************************************

uint64_t RandomFibonacciNumbersGenerator::LookUpCache(uint32_t key)
{
  for (CacheItem& item : m_cache)
  {
    if (item.m_key == key)
    {
      item.m_counter++;
      item.m_time = std::chrono::system_clock::now();

      return item.m_value;
    }
  }
  return 0; // not found
}

//***************************************************************************************

void RandomFibonacciNumbersGenerator::AddToCache(uint32_t key, uint64_t value)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate some delay in cache access

  CacheItem item = { key, value, 1, std::chrono::system_clock::now() };

  if (m_cache.size() < m_maxCacheSize)
  {
    m_cache.push_back(item);
  }
  else
  {
    size_t imin = 0;
    auto min = m_cache[0].m_time;

    for (size_t i = 1; i < m_cache.size(); ++i)
    {
      if (m_cache[i].m_time < min)
      {
        imin = i;
        min = m_cache[i].m_time;
      }
    }

    m_cache[imin] = item;
  }
}

//***************************************************************************************

uint64_t RandomFibonacciNumbersGenerator::ComputeValue(uint32_t key)
{
  uint64_t a = 0, b = 1, c = 0;

  for (uint32_t i = 2; i <= key; ++i)
  {
    c = a + b;
    a = b;
    b = c;
  }

  return c;
}

//***************************************************************************************
