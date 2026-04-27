//***************************************************************************************

#pragma once
#include "FibonacciNumber.h"

//***************************************************************************************

using Node = FibonacciNumber;

class Stack
{
public:

  Stack(size_t maxSize);

  bool Push(const Node& node);
  bool Pop(Node& node);

  size_t GetMaxSize() const { return m_maxSize; }
  size_t GetSize() const { return m_data.size(); }
  const Node& GetNode(size_t i) const { return m_data[i]; }

private:

  size_t m_maxSize;

  std::vector<Node> m_data;
};

//***************************************************************************************
