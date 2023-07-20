#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

private:
	CRect m_rcImage;
	CImage m_image;

	// 이미지 분석으로만 얻을 데이터
	BOOL m_bIsGotDatas;
	double m_dCenterOfGravityXFromImage;	// 무게중심
	double m_dCenterOfGravityYFromImage;	// 무게중심
	int m_nMinXFromImage;				// 분포범위
	int m_nMinYFromImage;				// 분포범위
	int m_nMaxXFromImage;				// 분포범위
	int m_nMaxYFromImage;				// 분포범위

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
	void ClearImage();
	void DrawCircleWithRandomPattern(int nRadius);
	void GetCircleInformation();

private:
	BOOL IsInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius);
	void DrawImage(CDC &dc);
	void DrawInformation(CDC& dc);
};
