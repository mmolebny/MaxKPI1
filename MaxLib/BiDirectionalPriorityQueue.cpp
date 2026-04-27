//***************************************************************************************

#include "pch.h"
#include "BiDirectionalPriorityQueue.h"

//***************************************************************************************

BiDirectionalPriorityQueue::BiDirectionalPriorityQueue(size_t maxSize) : m_maxSize(maxSize)
{
  m_data.reserve(maxSize);
}

//***************************************************************************************

size_t BiDirectionalPriorityQueue::GetNodeLevel(size_t i)
{
  ++i;

  size_t l = 63;
  for (;;)
  {
    if (i & ((size_t)1 << l)) break;
    --l;
  }

  return l;
}

//***************************************************************************************

uint32_t BiDirectionalPriorityQueue::GetNodeColor(size_t i) const
{
  return GetNodeLevel(i) & 1 ? 0x002f4fcf : 0x00cf4f2f;
}

//***************************************************************************************

uint32_t BiDirectionalPriorityQueue::GetNodeTextColor(size_t i) const
{
  return GetNodeLevel(i) & 1 ? 0x00cfcfff : 0x00ffcfcf;
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::Enqueue(const Node& node)
{
  if (m_data.size() == m_maxSize) return false;

  m_data.push_back(node);

  size_t i = m_data.size() - 1; // new node's index

  if (i == 0) return true; // new node is a root

  size_t p = (i - 1) >> 1; // new node parent's index

  if (GetNodeLevel(i) & 1) // new node is on odd / max level
  {
    if (m_data[i].m_key < m_data[p].m_key)
    {
      std::swap(m_data[i], m_data[p]);

      SiftUpMin(p);
    }
    else
    {
      SiftUpMax(i);
    }
  }
  else // new node is on even / min level
  {
    if (m_data[i].m_key > m_data[p].m_key)
    {
      std::swap(m_data[i], m_data[p]);

      SiftUpMax(p);
    }
    else
    {
      SiftUpMin(i);
    }
  }

  return true;
}

//***************************************************************************************

void BiDirectionalPriorityQueue::SiftUpMin(size_t i)
{
  SiftUp(i, [](const Node& a, const Node& b) { return a.m_key >= b.m_key; });
}

void BiDirectionalPriorityQueue::SiftUpMax(size_t i)
{
  SiftUp(i, [](const Node& a, const Node& b) { return a.m_key <= b.m_key; });
}

void BiDirectionalPriorityQueue::SiftUp(size_t i, bool(*compare)(const Node&, const Node&))
{
  while (true)
  {
    if (i < 3) return; // no grandparent exists

    size_t k = GetParentIndex(GetParentIndex(i)); // index of a grandparent

    if (compare(m_data[i], m_data[k])) return;

    std::swap(m_data[i], m_data[k]);

    i = k;
  }
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::PeekMin(Node& node)
{
  if (m_data.empty()) return false;

  node = m_data[0];

  return true;
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::PeekMax(Node& node, size_t& index)
{
  if (m_data.empty()) return false;

  if (m_data.size() == 1)
  {
    node = m_data[0];
    index = 0;
  }
  else
  {
    node = m_data[1];
    index = 1;

    if (m_data.size() > 2)
    {
      if (node.m_key < m_data[2].m_key)
      {
        node = m_data[2];
        index = 2;
      }
    }
  }

  return true;
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::DequeueMin(Node& node)
{
  if (!PeekMin(node)) return false;

  RemoveNode(0);

  return true;
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::DequeueMax(Node& node)
{
  size_t index;
  if (!PeekMax(node, index)) return false;

  RemoveNode(index);

  return true;
}

//***************************************************************************************

bool BiDirectionalPriorityQueue::RemoveNode(size_t i)
{
  if (i >= m_data.size()) return false;

  m_data[i] = m_data[m_data.size() - 1];

  m_data.pop_back();

  if (i < m_data.size())
  {
    if (GetNodeLevel(i) & 1) // node is on odd / max level
    {
      SiftDownMax(i);
    }
    else // node is on even / min level
    {
      SiftDownMin(i);
    }
  }

  return true;
}

//***************************************************************************************

void BiDirectionalPriorityQueue::SiftDownMin(size_t i)
{
  SiftDown(i, [](const Node& a, const Node& b) { return a.m_key > b.m_key; });
}

void BiDirectionalPriorityQueue::SiftDownMax(size_t i)
{
  SiftDown(i, [](const Node& a, const Node& b) { return a.m_key < b.m_key; });
}

void BiDirectionalPriorityQueue::SiftDown(size_t i, bool(*compare)(const Node&, const Node&))
{
  size_t n = m_data.size();

  while (true)
  {
    // go through children
    size_t k1 = GetLeftChildIndex(i);
    if (k1 >= n) return; // no left child exists => this is a leaf => exit

    size_t k2 = k1 + 1;
    if (k2 >= n) k2 = n - 1;
    size_t m = i;
    for (size_t k = k1; k <= k2; ++k)
    {
      if (compare(m_data[m], m_data[k])) m = k;
    }
    if (m != i) std::swap(m_data[i], m_data[m]);

    // go through grandchildren
    k1 = GetLeftChildIndex(k1);
    k2 = k1 + 4;
    if (k2 >= n) k2 = n - 1;
    m = i;
    for (size_t k = k1; k <= k2; ++k)
    {
      if (compare(m_data[m], m_data[k])) m = k;
    }
    if (m == i) return; // no need to swap => exit

    std::swap(m_data[i], m_data[m]);

    i = m;
  }
}

//***************************************************************************************
