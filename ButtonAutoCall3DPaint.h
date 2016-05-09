#pragma once


// CButtonAutoCall3DPaint

class CButtonAutoCall3DPaint : public CButton
{
	DECLARE_DYNAMIC(CButtonAutoCall3DPaint)

public:
	CButtonAutoCall3DPaint();
	virtual ~CButtonAutoCall3DPaint();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
};


