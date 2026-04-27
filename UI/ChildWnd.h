//***************************************************************************************

#pragma once
#include "RandomFibonacciNumbersGenerator.h"
#include "Stack.h"
#include "BiDirectionalPriorityQueue.h"

//***************************************************************************************

class ChildWnd : public CWnd
{
public:

  ChildWnd();
  ~ChildWnd();

  void SetFibonacci(RandomFibonacciNumbersGenerator* fibonacci) { m_fibonacci = fibonacci; }
  void SetStack(Stack* stack) { m_stack = stack; }
  void SetQueue(BiDirectionalPriorityQueue* queue) { m_queue = queue; }

  void CreateMemDC();
  void RepaintMemDC();

private:

  RandomFibonacciNumbersGenerator* m_fibonacci = nullptr;
  Stack* m_stack = nullptr;
  BiDirectionalPriorityQueue* m_queue = nullptr;

  int m_w = 0;
  int m_h = 0;

  HDC m_memDC = NULL;
  HBITMAP m_bitmap = NULL;
  HGDIOBJ m_oBitmap = NULL;

  void Clear();
  void DrawArray(const RECT& rect);
  void DrawHeapAsArray(const RECT& rect);
  void DrawHeapAsTree(const RECT& rect);

  void OnPaint();

  static void RegisterWindowClass(const wchar_t* windowClassName);

  DECLARE_MESSAGE_MAP()
};

//***************************************************************************************
