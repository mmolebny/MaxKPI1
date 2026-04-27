//***************************************************************************************

#pragma once
#include "FibonacciNumber.h"

//***************************************************************************************

using Node = FibonacciNumber;

class BiDirectionalPriorityQueue
{
public:

  BiDirectionalPriorityQueue(size_t maxSize);

  bool Enqueue(const Node& node);

  bool DequeueMin(Node& node);
  bool DequeueMax(Node& node);

  size_t GetMaxSize() const { return m_maxSize; }
  size_t GetSize() const { return m_data.size(); }
  const Node& GetNode(size_t i) const { return m_data[i]; }
  uint32_t GetNodeColor(size_t i) const;
  uint32_t GetNodeTextColor(size_t i) const;
  static size_t GetNodeLevel(size_t i);
  size_t GetNumLevels() const { return GetNodeLevel(m_data.size() - 1) + 1; }

private:

  size_t m_maxSize;

  std::vector<Node> m_data;

  bool PeekMin(Node& node);
  bool PeekMax(Node& node, size_t& index);

  bool RemoveNode(size_t i);

  void SiftUpMin(size_t i);
  void SiftUpMax(size_t i);
  void SiftUp(size_t i, bool(*compare)(const Node&, const Node&));
  void SiftDownMin(size_t i);
  void SiftDownMax(size_t i);
  void SiftDown(size_t i, bool(*compare)(const Node&, const Node&));

  size_t GetParentIndex(size_t i) const { return (i - 1) >> 1; }
  size_t GetLeftChildIndex(size_t i) const { return (i << 1) + 1; }
};

//***************************************************************************************
