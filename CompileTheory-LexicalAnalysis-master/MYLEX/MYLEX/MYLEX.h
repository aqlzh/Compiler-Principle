
// MYLEX.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMYLEXApp: 
// �йش����ʵ�֣������ MYLEX.cpp
//

class CMYLEXApp : public CWinApp
{
public:
	CMYLEXApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMYLEXApp theApp;