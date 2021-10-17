
// MYLEXDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MYLEX.h"
#include "MYLEXDlg.h"
#include "afxdialogex.h"
#include"MAlex.h"
#include<string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnYuan();
//	afx_msg void OnAlybutton();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMYLEXDlg �Ի���



CMYLEXDlg::CMYLEXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMYLEXDlg::IDD, pParent)
	, source(_T(""))
	, cpreop(_T(""))
	, relist(_T(""))
	, result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMYLEXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUTEDIT, source);
	DDX_Text(pDX, IDC_LISTEDIT, cpreop);
	DDX_Text(pDX, IDC_RESERVEDIT, relist);
	DDX_Text(pDX, IDC_RESULTEDIT, result);
	DDX_Control(pDX, IDC_INPUTEDIT, sour_edit);
	DDX_Control(pDX, IDC_LISTEDIT, edit_list);
	DDX_Control(pDX, IDC_RESULTEDIT, result_edit);
	DDX_Control(pDX, IDC_RESERVEDIT, res_edit);
}

BEGIN_MESSAGE_MAP(CMYLEXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_YUAN, &CMYLEXDlg::OnBnClickedYuan)
ON_BN_CLICKED(IDC_ALYBUTTON, &CMYLEXDlg::OnBnClickedAlybutton)
END_MESSAGE_MAP()


// CMYLEXDlg ��Ϣ�������

BOOL CMYLEXDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMYLEXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMYLEXDlg::OnPaint()
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
HCURSOR CMYLEXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMYLEXDlg::OnBnClickedYuan()
{
	CString filepathname;    //�����Ի��򲢶�ȡ�ļ�
	CString filename;
	filepathname = "";
	filename = "";
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CString("ALL File (*.*)|*.*||"), AfxGetMainWnd());
	if (FileDlg.DoModal() == IDOK){
		filepathname = FileDlg.GetPathName();
		filename = FileDlg.GetFileName();
	}
	ifstream infile;
	infile.open(filepathname, ios::in);
	if (!infile){
		MessageBox(filepathname);
		return;
	} 
	Lex_analyzer.COPE(infile);    
	char buffer[256];
	infile.seekg(0);   //�ص��ļ���ͷ
	while (infile.getline(buffer, 256,'\n')){   //��ȡԴ�ļ���source��
		strcat_s(buffer, 256, "\r\n");
		source += buffer;
	}
	sour_edit.SetWindowTextW(source);
	ifstream prefile;
	prefile.open("preout.txt");
    while (prefile.getline(buffer, 256, '\n')){   //��ȡԤ�������ļ���Ԥ�������
		strcat_s(buffer, 256, "\r\n");
		cpreop += buffer;
	}
	edit_list.SetWindowTextW(cpreop);
	infile.close();
	prefile.close();
}


void CMYLEXDlg::OnBnClickedAlybutton()
{
	ifstream resfile;
	resfile.open("resout.txt");
	char buffer[256];
	while (resfile.getline(buffer, 256, '\n')){   //��ȡ�������ļ���result��
		strcat_s(buffer, 256, "\r\n\r\n");
	    result += buffer;
	}
	result_edit.SetWindowTextW(result);
	Lex_analyzer.print_list(relist);
	res_edit.SetWindowTextW(relist);
	resfile.close();
}

