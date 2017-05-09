
// PackerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Packer.h"
#include "PackerDlg.h"
#include "afxdialogex.h"
#include "util.h"
#include "vector"
#include "aplib.h"
#include "Task.h"
#include "info.h"
#include "Loading.h"
#pragma comment(lib, "aplib.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable: 4996)

extern HWND g_hwnd;
std::string path;
bool isPacking = false;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPackerDlg �Ի���



CPackerDlg::CPackerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PACKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
}

BEGIN_MESSAGE_MAP(CPackerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_UPDATE, &CPackerDlg::OnUpdateProgress)
	ON_MESSAGE(WM_UPDATEWRITEMEMORY, &CPackerDlg::OnUpdateWriteMemoryProgress)
	ON_BN_CLICKED(IDOK, &CPackerDlg::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CPackerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPackerDlg ��Ϣ�������
BOOL CPackerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	g_hwnd = GetSafeHwnd();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

LRESULT CPackerDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	if (lParam != 0)
		m_progress.SetPos(((DWORD)wParam / (DWORD)lParam) * 100);
	return LRESULT();
}

LRESULT CPackerDlg::OnUpdateWriteMemoryProgress(WPARAM wParam, LPARAM lParam)
{
	if (lParam != 0)
		m_progress.SetPos(((DWORD)wParam / (DWORD)lParam) * 50);
	return LRESULT();
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPackerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPackerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPackerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (path.empty())
	{
		MessageBoxA("·������Ϊ��","Packer",MB_ICONWARNING);
		return;
	}

	if (isPacking)
	{
		MessageBoxA("���ڼӿ�����Ⱥ�", "Packer", MB_ICONWARNING);
		return;
	}
	LoadIng load;
	load.DoModal();
}


void CPackerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ  
	if (DropCount > 1)
	{
		MessageBox("Ŀǰֻ֧��һ���ļ���ק","��ʾ",0);
		DragFinish(hDropInfo);
		return;
	}
	CHAR wsStr[MAX_PATH];
	DragQueryFileA(hDropInfo, 0, wsStr, MAX_PATH);
	std::string wsFileKind=wsStr;
	wsFileKind=wsFileKind.substr(wsFileKind.length()-3,3);
	if (stricmp(wsFileKind.c_str(),"exe")!=0)
	{
		MessageBox("ֻ֧����קEXE�ļ�","��ʾ" , 0);
		DragFinish(hDropInfo);
		return;
	}
	DragFinish(hDropInfo);
	SetDlgItemTextA(IDC_FILENAME,wsStr);
	path = wsStr;
	CDialogEx::OnDropFiles(hDropInfo);
}


void CPackerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("��ִ���ļ�(*.exe)|*.exe|�����ļ�(*.*)|*.*||");
	CFileDialog fileDialog(TRUE,_T("exe"),NULL,0,szFilter,this);
	CString csFileName;
	if (IDOK == fileDialog.DoModal())
	{
		csFileName = fileDialog.GetPathName();
		std::string wsFileKind=csFileName.GetBuffer();
		wsFileKind=wsFileKind.substr(wsFileKind.length() - 3, 3);
		if (stricmp(wsFileKind.c_str(), "exe") != 0)
		{
			MessageBox("ֻ֧��EXE�ļ�", "��ʾ", 0);
			return;
		}
		SetDlgItemTextA(IDC_FILENAME, csFileName.GetBuffer());
		path = csFileName.GetBuffer();
	}
}
