//***************************************************************************************

#pragma once

//***************************************************************************************

class MainDlg : public CDialog
{
public:

	MainDlg(CWnd* parent = nullptr);

private:

	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* dx);

	DECLARE_MESSAGE_MAP()
};

//***************************************************************************************
