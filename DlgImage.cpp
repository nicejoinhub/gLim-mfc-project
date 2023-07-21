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
	srand((unsigned int)time(nullptr));
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

	ClearImage();
}

void CDlgImage::ClearImage()
{
	m_bIsGotDatas = FALSE;

	unsigned char *fm = (unsigned char *)m_image.GetBits();
	memset(fm, 0, m_rcImage.Height() * m_image.GetPitch());

	Invalidate(FALSE);
}

void CDlgImage::DrawCircleWithRandomPattern(int nRadius)
{
	ClearImage();

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();

	nRadius = max(1, min(m_image.GetHeight(), min(m_image.GetWidth(), nRadius)));

	int nRndX = rand() % (m_image.GetWidth() - nRadius * 2) + nRadius;
	int nRndY = rand() % (m_image.GetHeight() - nRadius * 2) + nRadius;

	for (int y = nRndY - nRadius; y < nRndY + nRadius; y++)
	{
		if (y < 0 || y >= m_image.GetHeight())
			continue;

		for (int x = nRndX - nRadius; x < nRndX + nRadius; x++)
		{
			if (x < 0 || x >= m_image.GetWidth())
				continue;

			if (IsInCircle(x, y, nRndX, nRndY, nRadius))
			{
				fm[y * nPitch + x] = rand() % 0xFF;
			}
		}
	}

	Invalidate(FALSE);
}

void CDlgImage::GetCircleInformation()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	int nMinX = 0x7FFFFFFF; // signed int 최대값
	int nMinY = 0x7FFFFFFF; // signed int 최대값
	int nMaxX = 0x80000000; // signed int 최소값
	int nMaxY = 0x80000000; // signed int 최소값

	for (int y = 0; y < m_image.GetHeight(); y++)
	{
		for (int x = 0; x < m_image.GetWidth(); x++)
		{
			// 0x00 ~ 0x7F: Off
			// 0x80 ~ 0xFF: On
			if (fm[y * nPitch + x] >= 0x80)
			{
				nSumX += x;
				nSumY += y;
				nCount++;

				if (nMinX > x)	nMinX = x;
				if (nMinY > y)	nMinY = y;
				if (nMaxX < x)	nMaxX = x;
				if (nMaxY < y)	nMaxY = y;
			}
		}
	}

	m_dCenterOfGravityXFromImage = (double)nSumX / nCount;
	m_dCenterOfGravityYFromImage = (double)nSumY / nCount;
	m_nMinXFromImage = nMinX;
	m_nMinYFromImage = nMinY;
	m_nMaxXFromImage = nMaxX;
	m_nMaxYFromImage = nMaxY;

	m_bIsGotDatas = TRUE;

	Invalidate(FALSE);
}

BOOL CDlgImage::IsInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius)
{
	int dx = x - nCenterX;
	int dy = y - nCenterY;
	int distSqare = dx * dx + dy * dy;
	int compareValue = nRadius * nRadius;

	return distSqare <= compareValue;
}

void CDlgImage::DrawImage(CDC& dc)
{
	m_image.Draw(dc, m_rcImage);
}

void CDlgImage::DrawInformation(CDC& dc)
{
	if (!m_bIsGotDatas)
		return;

	const double dCrossLength = 5.5;

	HPEN hPenYellow = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hOldPen = (HPEN)dc.SelectObject(hPenYellow);
	HBRUSH hOldBrush = (HBRUSH)dc.SelectObject(hBrush);

	dc.Ellipse(m_nMinXFromImage, m_nMinYFromImage, m_nMaxXFromImage, m_nMaxYFromImage);

	dc.SelectObject(hPenRed);

	dc.MoveTo((int)round(m_dCenterOfGravityXFromImage - dCrossLength), (int)round(m_dCenterOfGravityYFromImage));
	dc.LineTo((int)round(m_dCenterOfGravityXFromImage + dCrossLength), (int)round(m_dCenterOfGravityYFromImage));
	dc.MoveTo((int)round(m_dCenterOfGravityXFromImage), (int)round(m_dCenterOfGravityYFromImage - dCrossLength));
	dc.LineTo((int)round(m_dCenterOfGravityXFromImage), (int)round(m_dCenterOfGravityYFromImage + dCrossLength));

	dc.SelectObject(hOldBrush);
	dc.SelectObject(hOldPen);

	DeleteObject(hPenYellow);
	DeleteObject(hPenRed);
}
