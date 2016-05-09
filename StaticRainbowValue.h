#pragma once


// CStaticRainbowValue

class CStaticRainbowValue : public CStatic
{
	DECLARE_DYNAMIC(CStaticRainbowValue)

public:
	CStaticRainbowValue();
	virtual ~CStaticRainbowValue();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


