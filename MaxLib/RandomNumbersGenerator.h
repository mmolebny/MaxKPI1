//***************************************************************************************

#pragma once

//***************************************************************************************

class RandomNumbersGenerator
{
public:

  RandomNumbersGenerator(uint32_t min, uint32_t max) : m_min(min), m_max(max)
  {
    std::srand((uint32_t)std::time(nullptr));
  }

  uint32_t New() { return m_min + (uint32_t)std::rand() % (m_max - m_min + 1); }

  uint32_t GetMin() const { return m_min; }
  uint32_t GetMax() const { return m_max; }

private:

  uint32_t m_min;
  uint32_t m_max;
};

//***************************************************************************************
