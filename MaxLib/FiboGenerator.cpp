//***************************************************************************************

#include "pch.h"
#include "FiboGenerator.h"

//***************************************************************************************

FiboGenerator::FiboGenerator()
{
  std::srand((unsigned int)std::time(nullptr));
}

//***************************************************************************************

Fibo FiboGenerator::New()
{
  Fibo item;

  item.m_key = (uint32_t)std::rand() % 94;

  item.m_value = GetFibonacci(item.m_key);

  return item;
}

//***************************************************************************************

uint64_t FiboGenerator::GetFibonacci(uint32_t n)
{
  if (n == 0) return 0;
  if (n == 1) return 1;
  uint64_t a = 0, b = 1, c = 0;
  for (uint32_t i = 2; i <= n; ++i)
  {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

//***************************************************************************************
