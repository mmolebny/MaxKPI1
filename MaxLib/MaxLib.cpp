//***************************************************************************************

#include "pch.h"
#include "MaxLib.h"

//***************************************************************************************

std::vector<int> GenerateArray(int64_t n, int min, int max)
{
  if (n < 1) n = 1; else if (n > 127) n = 127;

  std::srand((unsigned int)std::time(nullptr));

  std::vector<int> values;
  values.reserve(n);

  for (int64_t i = 0; i < n; ++i)
  {
    values.push_back(min + std::rand() % (max - min + 1));
  }

  return values;
}

//***************************************************************************************

