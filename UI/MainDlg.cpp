//***************************************************************************************

#include "pch.h"
#include "Resource.h"
#include "MainDlg.h"

//***************************************************************************************

BEGIN_MESSAGE_MAP(MainDlg, CDialog)
  ON_BN_CLICKED(ID_PUSH_BUTTON, OnPushButtonClicked)
  ON_BN_CLICKED(ID_POP_BUTTON, OnPopButtonClicked)
  ON_BN_CLICKED(ID_ENQUEUE_BUTTON, OnEnqueueButtonClicked)
  ON_BN_CLICKED(ID_DEQUEUE_MIN_BUTTON, OnDequeueMinButtonClicked)
  ON_BN_CLICKED(ID_DEQUEUE_MAX_BUTTON, OnDequeueMaxButtonClicked)
END_MESSAGE_MAP()

//***************************************************************************************
// 93rd Fibonacci number is the largest that fits in uint64_t

MainDlg::MainDlg(CWnd* parent) : CDialog(ID_UI_DIALOG, parent), m_fibonacci(10), m_stack(127), m_queue(127)
{
  m_hIcon = AfxGetApp()->LoadIconW(ID_MAINFRAME);

  m_wnd.SetFibonacci(&m_fibonacci);
  m_wnd.SetStack(&m_stack);
  m_wnd.SetQueue(&m_queue);
}

//***************************************************************************************

BOOL MainDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  SetIcon(m_hIcon, TRUE);
  SetIcon(m_hIcon, FALSE);

  m_wnd.CreateMemDC();
  m_wnd.RepaintMemDC();

  UpdateData(FALSE);

  return TRUE;
}

//***************************************************************************************

void MainDlg::DoDataExchange(CDataExchange* dx)
{
  CDialog::DoDataExchange(dx);

  DDX_Control(dx, ID_CACHE1_EDIT, m_cache1Edit);
  DDX_Control(dx, ID_CACHE2_EDIT, m_cache2Edit);
  DDX_Control(dx, ID_ARRAY_EDIT, m_arrayEdit);
  DDX_Control(dx, ID_HEAP_EDIT, m_heapEdit);
  DDX_Control(dx, ID_CHILD_WINDOW, m_wnd);
}

//***************************************************************************************

void MainDlg::UpdateEditBoxes()
{
  std::wstring text1;
  std::wstring text2;
  for (size_t i = 0; i < m_fibonacci.GetCacheSize(); ++i)
  {
    const auto& item = m_fibonacci.GetCacheItem(i);
    text1 += std::format(L"{:2d}     {:d}\r\n", item.m_key, item.m_value);
    text2 += std::format(L"{:d}   {:%F %T}\r\n", item.m_counter, item.m_time);
  }
  m_cache1Edit.SetWindowTextW(text1.c_str());
  m_cache2Edit.SetWindowTextW(text2.c_str());

  std::wstring text;
  for (size_t i = 0; i < m_stack.GetSize(); ++i)
  {
    const auto& node = m_stack.GetNode(i);
    text += std::format(L"{:2d}     {:d}\r\n", node.m_key, node.m_value);
  }
  m_arrayEdit.SetWindowTextW(text.c_str());

  text.clear();
  for (size_t i = 0; i < m_queue.GetSize(); ++i)
  {
    const auto& node = m_queue.GetNode(i);
    text += std::format(L"{:2d}     {:d}\r\n", node.m_key, node.m_value);
  }
  m_heapEdit.SetWindowTextW(text.c_str());
}

//***************************************************************************************

void MainDlg::OnPushButtonClicked()
{
  FibonacciNumber number = m_fibonacci.New();

  m_stack.Push(number);

  m_wnd.RepaintMemDC();
  m_wnd.Invalidate(FALSE);
  m_wnd.UpdateWindow();

  UpdateEditBoxes();
}

//***************************************************************************************

void MainDlg::OnPopButtonClicked()
{
  FibonacciNumber number;

  m_stack.Pop(number);

  m_wnd.RepaintMemDC();
  m_wnd.Invalidate(FALSE);
  m_wnd.UpdateWindow();

  UpdateEditBoxes();
}

//***************************************************************************************

void MainDlg::OnEnqueueButtonClicked()
{
  FibonacciNumber number;

  if (m_stack.Pop(number))
  {
    m_queue.Enqueue(number);
  }

  m_wnd.RepaintMemDC();
  m_wnd.Invalidate(FALSE);
  m_wnd.UpdateWindow();

  UpdateEditBoxes();
}

//***************************************************************************************

void MainDlg::OnDequeueMinButtonClicked()
{
  FibonacciNumber number;

  if (m_queue.DequeueMin(number))
  {
    m_stack.Push(number);
  }

  m_wnd.RepaintMemDC();
  m_wnd.Invalidate(FALSE);
  m_wnd.UpdateWindow();

  UpdateEditBoxes();
}

//***************************************************************************************

void MainDlg::OnDequeueMaxButtonClicked()
{
  FibonacciNumber number;

  if (m_queue.DequeueMax(number))
  {
    m_stack.Push(number);
  }

  m_wnd.RepaintMemDC();
  m_wnd.Invalidate(FALSE);
  m_wnd.UpdateWindow();

  UpdateEditBoxes();
}

//***************************************************************************************
