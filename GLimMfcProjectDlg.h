
// GLimMfcProjectDlg.h: 헤더 파일
//

#pragma once

#include "DlgImage.h"


// CGLimMfcProjectDlg 대화 상자
class CGLimMfcProjectDlg : public CDialogEx
{
private:
	CDlgImage* m_pDlgImage;

// 생성입니다.
public:
	CGLimMfcProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMMFCPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnPattern();
	afx_msg void OnBnClickedBtnAnalyze();

	DECLARE_MESSAGE_MAP()
public:
	int m_nRadius;
};
