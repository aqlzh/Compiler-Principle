
// MYLEXDlg.h : ͷ�ļ�


#pragma once
#include<string>
#include"MAlex.h"
#include "afxwin.h"
using namespace std;
// CMYLEXDlg �Ի���
class CMYLEXDlg : public CDialogEx
{
// ����
public:
	CMYLEXDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYLEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChangeInputedit();
//	afx_msg void OnChangeListedit();

//	afx_msg void OnChangeReservedit();
//	afx_msg void OnChangeResultedit();

	MAlex Lex_analyzer;
	// //Դ����
	CString source;
	// Ԥ������
	CString cpreop;
	// ������
	CString relist;
	// ���
	CString result;
	afx_msg void OnBnClickedYuan();
	afx_msg void OnBnClickedAlybutton();
//	afx_msg void OnEnChangeInputedit();
	// //Դ�ļ����
	CEdit sour_edit;
	// ����Ԥ����
	CEdit edit_list;
	// �������
	CEdit result_edit;
	// ����������
	CEdit res_edit;
};

