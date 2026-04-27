//***************************************************************************************

#include "pch.h"
#include "ChildWnd.h"

//***************************************************************************************

BEGIN_MESSAGE_MAP(ChildWnd, CWnd)
  ON_WM_PAINT()
END_MESSAGE_MAP()

//***************************************************************************************

void ChildWnd::RegisterWindowClass(const wchar_t* windowClassName)
{
  WNDCLASS wndcls = {};
  HINSTANCE instance = ::AfxGetInstanceHandle();
  if (!::GetClassInfoW(instance, windowClassName, &wndcls))
  {
    wndcls = {};
    wndcls.style = CS_DBLCLKS;
    wndcls.lpfnWndProc = ::DefWindowProcW;
    wndcls.hInstance = instance;
    wndcls.hCursor = ::LoadCursorW(NULL, IDC_ARROW);
    wndcls.lpszClassName = windowClassName;
    ::AfxRegisterClass(&wndcls);
  }
}

//***************************************************************************************

ChildWnd::ChildWnd()
{
  RegisterWindowClass(L"ChildWindow");
}

//***************************************************************************************

ChildWnd::~ChildWnd()
{
  if (m_bitmap != NULL)
  {
    ::SelectObject(m_memDC, m_oBitmap);
    ::DeleteObject(m_bitmap);
  }
}

//***************************************************************************************

void ChildWnd::CreateMemDC()
{
  m_memDC = ::CreateCompatibleDC(NULL);

  RECT rect;
  GetClientRect(&rect);

  m_w = rect.right;
  m_h = rect.bottom;

  BITMAPINFOHEADER header = {};
  header.biSize = sizeof(BITMAPINFOHEADER);
  header.biPlanes = 1;
  header.biBitCount = 32;
  header.biWidth = m_w;
  header.biHeight = m_h;

  unsigned char* bits = nullptr;
  m_bitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)&header, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
  if (m_bitmap != NULL) m_oBitmap = ::SelectObject(m_memDC, m_bitmap);
}

//***************************************************************************************

void ChildWnd::OnPaint()
{
  PAINTSTRUCT paintStruct;
  HDC paintDC = ::BeginPaint(m_hWnd, &paintStruct);
  ::BitBlt(paintDC, 0, 0, m_w, m_h, m_memDC, 0, 0, SRCCOPY);
  ::EndPaint(m_hWnd, &paintStruct);
}

//***************************************************************************************

void ChildWnd::RepaintMemDC()
{
  Clear();

  DrawArray({ 0, 0, m_w, m_h/3 - 5 });
  DrawHeapAsArray({ 0, m_h / 3 + 5, m_w, 2 * m_h / 3 - 5 });
  DrawHeapAsTree({ 0, 2*m_h/3 + 5, m_w, m_h });
}

//***************************************************************************************

void ChildWnd::Clear()
{
  RECT rect = { 0, 0, m_w, m_h };
  ::SetDCBrushColor(m_memDC, RGB(0,0,0));
  ::FillRect(m_memDC, (const RECT*)&rect, (HBRUSH)::GetStockObject(DC_BRUSH));
}

//***************************************************************************************

void ChildWnd::DrawArray(const RECT& rect)
{
  HGDIOBJ oBrush = ::SelectObject(m_memDC, ::GetStockObject(DC_BRUSH));
  HGDIOBJ oPen = ::SelectObject(m_memDC, ::GetStockObject(DC_PEN));

  int w = rect.right - rect.left - 4;
  int h = rect.bottom - rect.top - 4;
  int l0 = rect.left + 2;
  int b0 = rect.bottom - 2;
  int l = l0;

  for (size_t i = 0; i < m_stack->GetSize(); ++i)
  {
    COLORREF color = 0x0000af00;
    ::SetDCPenColor(m_memDC, color);
    ::SetDCBrushColor(m_memDC, color);
    int r = l0 + (w * ((int)i + 1) / (int)m_stack->GetMaxSize()) - 1;
    int t = b0 - h * (int)m_stack->GetNode(i).m_key / (int)m_fibonacci->GetMaxKey();
    ::Rectangle(m_memDC, l, t, r, b0);
    l = r + 2;
  }

  ::SelectObject(m_memDC, oPen);
  ::SelectObject(m_memDC, oBrush);
}

//***************************************************************************************

void ChildWnd::DrawHeapAsArray(const RECT& rect)
{
  HGDIOBJ oBrush = ::SelectObject(m_memDC, ::GetStockObject(DC_BRUSH));
  HGDIOBJ oPen = ::SelectObject(m_memDC, ::GetStockObject(DC_PEN));

  int w = rect.right - rect.left - 4;
  int h = rect.bottom - rect.top - 4;
  int l0 = rect.left + 2;
  int b0 = rect.bottom - 2;
  int l = l0;

  for (size_t i = 0; i < m_queue->GetSize(); ++i)
  {
    const Node& node = m_queue->GetNode(i);

    uint32_t color = m_queue->GetNodeColor(i);
    ::SetDCPenColor(m_memDC, color);
    ::SetDCBrushColor(m_memDC, color);

    int r = l0 + (w * ((int)i + 1) / (int)m_queue->GetMaxSize()) - 1;
    int t = b0 - h * (int)node.m_key / (int)m_fibonacci->GetMaxKey();
    ::Rectangle(m_memDC, l, t, r, b0);

    l = r + 2;
  }

  ::SelectObject(m_memDC, oPen);
  ::SelectObject(m_memDC, oBrush);
}

//***************************************************************************************

void ChildWnd::DrawHeapAsTree(const RECT& rect)
{
  size_t numNodes = m_queue->GetSize(); if (numNodes == 0) return;

  size_t numLevels = m_queue->GetNumLevels();

  const size_t numLevelsMax = 7;

  size_t numNodesOnLastLevelMax = (size_t)1 << (numLevelsMax - 1);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  int ry = h / (int)numLevelsMax / 2;
  int rx =  w / (int)numNodesOnLastLevelMax / 2;
  int r = rx;
  if (ry < r) r = ry;
  int fontSize = 3 * r / 2;

  std::vector<int> x(numNodes);
  std::vector<int> y(numNodes);

  HGDIOBJ oBrush = ::SelectObject(m_memDC, ::GetStockObject(DC_BRUSH));
  HPEN pen = ::CreatePen(PS_SOLID, 8 - (int)numLevelsMax, 0x00ffffff);
  HGDIOBJ oPen = ::SelectObject(m_memDC, pen);

  int t = 0;
  int b = rect.top;
  size_t prevLevel = (size_t)-1;
  size_t numNodesOnLevelMax = 1;
  for (size_t node = 0, levelNode = 0; node < numNodes; ++node, ++levelNode)
  {
    size_t level = m_queue->GetNodeLevel(node);
    if (level != prevLevel)
    {
      t = rect.top + (int)( level      * h / numLevelsMax);
      b = rect.top + (int)((level + 1) * h / numLevelsMax);
      numNodesOnLevelMax  = (size_t)1 << level;
      prevLevel = level;
      levelNode = 0;
    }
    int l = (int)(levelNode    ) * w / (int)numNodesOnLevelMax;
    int r = (int)(levelNode + 1) * w / (int)numNodesOnLevelMax;

    x[node] = (l + r) / 2;
    y[node] = (t + b) / 2;

    if (node > 0)
    {
      size_t parentNode = (node - 1) / 2;
      ::MoveToEx(m_memDC, x[parentNode], y[parentNode], nullptr);
      ::LineTo(m_memDC, x[node], y[node]);
    }
  }

  ::SelectObject(m_memDC, oPen);
  ::DeleteObject(pen);

  oPen = ::SelectObject(m_memDC, ::GetStockObject(DC_PEN));
  HFONT font = ::CreateFontW(fontSize, 0, 0, 0, 800, 0, 0, 0, 1, 0, 0, 0, 0, L"Segoe UI");
  HGDIOBJ oFont = ::SelectObject(m_memDC, font);
  ::SetTextAlign(m_memDC, TA_TOP | TA_CENTER | TA_NOUPDATECP);
  ::SetBkMode(m_memDC, TRANSPARENT);

  for (size_t node = 0; node < numNodes; ++node)
  {
    uint32_t color = m_queue->GetNodeColor(node);
    ::SetDCPenColor(m_memDC, color);
    ::SetDCBrushColor(m_memDC, color);
    ::SetTextColor(m_memDC, m_queue->GetNodeTextColor(node));

    ::Ellipse(m_memDC, x[node] - r, y[node] - r, x[node] + r, y[node] + r);
    std::wstring text = std::to_wstring(m_queue->GetNode(node).m_key);
    ::TextOutW(m_memDC, x[node], y[node] - fontSize / 2, text.c_str(), (int)text.size());
  }

  ::SelectObject(m_memDC, oFont);
  ::DeleteObject(font);
  ::SelectObject(m_memDC, oPen);

  ::SelectObject(m_memDC, oBrush);
}

//***************************************************************************************
