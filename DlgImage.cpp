// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gLimMfcProject.h"
#include "afxdialogex.h"
#include "DlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_IMAGE, pParent)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

void CDlgImage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_image.IsNull())
		m_image.Destroy();
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	DrawImage(dc);
	DrawInformation(dc);
}

void CDlgImage::CreateImage()
{
	GetClientRect(&m_rcImage);

	if (!m_image.IsNull())
		m_image.Destroy();

	const int nBPP = 8;

	m_image.Create(m_rcImage.Width(), -m_rcImage.Height(), nBPP);

	if (nBPP == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

		m_image.SetColorTable(0, sizeof(rgb) / sizeof(rgb[0]), rgb);
	}

	unsigned char *fm = (unsigned char *)m_image.GetBits();
	memset(fm, 0, m_rcImage.Height() * m_image.GetPitch());

	Invalidate(FALSE);
}

void CDlgImage::DrawImage(CDC& dc)
{
	m_image.Draw(dc, m_rcImage);
}

void CDlgImage::DrawInformation(CDC& dc)
{

}
