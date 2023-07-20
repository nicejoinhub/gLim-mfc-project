#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

private:
	CRect m_rcImage;
	CImage m_image;

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnDestroy();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	void CreateImage();
	void DrawImage(CDC &dc);
	void DrawInformation(CDC& dc);
};
