//***************************************************************************************

#pragma once
#include "ChildWnd.h"
#include "RandomFibonacciNumbersGenerator.h"
#include "Stack.h"
#include "BiDirectionalPriorityQueue.h"

//***************************************************************************************

class MainDlg : public CDialog
{
public:

  MainDlg(CWnd* parent = nullptr);

private:

  HICON m_hIcon;

  CEdit m_cache1Edit;
  CEdit m_cache2Edit;
  CEdit m_arrayEdit;
  CEdit m_heapEdit;
  ChildWnd m_wnd;

  RandomFibonacciNumbersGenerator m_fibonacci;
  Stack m_stack;
  BiDirectionalPriorityQueue m_queue;

  void UpdateEditBoxes();

  //CButton m_pushButton;
  //CButton m_popButton;
  //CButton m_enqueueButton;
  //CButton m_dequeueMinButton;
  //CButton m_dequeueMaxButton;

  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* dx);

  afx_msg void OnPushButtonClicked();
  afx_msg void OnPopButtonClicked();
  afx_msg void OnEnqueueButtonClicked();
  afx_msg void OnDequeueMinButtonClicked();
  afx_msg void OnDequeueMaxButtonClicked();

  DECLARE_MESSAGE_MAP()
};

//***************************************************************************************
