// InputInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Packer.h"
#include "InputInfo.h"
#include "afxdialogex.h"
#include "string"
#include "info.h"
// InputInfo �Ի���

IMPLEMENT_DYNAMIC(InputInfo, CDialogEx)

InputInfo::InputInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

InputInfo::~InputInfo()
{
}

void InputInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// InputInfo ��Ϣ�������


void InputInfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char buf[512];
	GetDlgItemTextA(IDC_PASSWORD,buf,512);
	gApplet.info.strPassword.clear();
	if (strlen(buf) > 15)
	{
		MessageBox("���볤�Ȳ��ܳ���14λ","��ʾ",MB_ICONWARNING);
		return;
	}
	gApplet.info.strPassword = buf;
	OnOK();

}
