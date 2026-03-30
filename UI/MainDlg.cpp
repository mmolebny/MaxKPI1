//***************************************************************************************

#include "pch.h"
#include "Resource.h"
#include "MainDlg.h"

//***************************************************************************************

BEGIN_MESSAGE_MAP(MainDlg, CDialog)
END_MESSAGE_MAP()

//***************************************************************************************

MainDlg::MainDlg(CWnd* parent): CDialog(ID_UI_DIALOG, parent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//***************************************************************************************

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//***************************************************************************************

BOOL MainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: Add extra initialization here

	return TRUE;
}

//***************************************************************************************

