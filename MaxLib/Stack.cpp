//***************************************************************************************

#include "pch.h"
#include "Stack.h"

//***************************************************************************************

Stack::Stack(size_t maxSize) : m_maxSize(maxSize)
{
  m_data.reserve(maxSize);
}

//***************************************************************************************

bool Stack::Push(const Node& node)
{
  if (m_data.size() == m_maxSize) return false;

  m_data.push_back(node);

  return true;
}

//***************************************************************************************

bool Stack::Pop(Node& node)
{
  if (m_data.empty()) return false;

  node = m_data[m_data.size() - 1];

  m_data.pop_back();

  return true;
}

//***************************************************************************************
