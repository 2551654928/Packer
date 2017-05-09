
// PackerDlg.h : ͷ�ļ�
//

#pragma once
#include "vector"
#include "info.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPackerDlg �Ի���
class CPackerDlg : public CDialogEx
{
// ����
public:
	CPackerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PACKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnUpdateProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateWriteMemoryProgress(WPARAM wParam, LPARAM lParam);
	void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progress;
	afx_msg void OnBnClickedOk();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_FileName;

	afx_msg void OnBnClickedButton1();
};
