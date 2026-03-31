//***************************************************************************************

#pragma once
#include <vector>

//***************************************************************************************

std::vector<int> GenerateArray(int64_t n, int min, int max);

//***************************************************************************************

class FibonacciGenerator
{
public:

  FibonacciGenerator(size_t cacheSize = 0) : m_maxCacheSize(cacheSize)
  {
    if (cacheSize > 0) m_memo.reserve(cacheSize);
  }

  int64_t GetNext()
  {
    CalculateUntil(m_curIndex);
    return m_memo[m_curIndex++];
  }

  int64_t GetAt(size_t index)
  {
    CalculateUntil(index);
    return m_memo[index];
  }

  void Reset()
  {
    m_curIndex = 0;
  }

private:

  std::vector<int64_t> m_memo = { 0, 1 };
  size_t m_curIndex = 0;
  size_t m_maxCacheSize = 0;

  void CalculateUntil(size_t n)
  {
    while (m_memo.size() <= n)
    {
      if (m_maxCacheSize && m_memo.size() >= m_maxCacheSize)
      {
        m_memo.erase(m_memo.begin());
      }
      size_t i = m_memo.size();
      int64_t next_value = m_memo[i - 1] + m_memo[i - 2];
      m_memo.push_back(next_value);
    }
  }
};

//***************************************************************************************
