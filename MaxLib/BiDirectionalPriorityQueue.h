//***************************************************************************************

#pragma once
#include <vector>
#include "FiboGenerator.h"

//***************************************************************************************

class BiDirectionalPriorityQueue
{
public:

  void Enqueue(const Fibo& item);

  Fibo DequeueMin();
  Fibo DequeueMax();

private:

  Fibo PeekMin();
  Fibo PeekMax();

  std::vector<Fibo> m_heap; // min-max heap
};

//***************************************************************************************
