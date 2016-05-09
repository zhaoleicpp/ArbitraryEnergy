#pragma once


// CStaticLog

class CStaticLog : public CStatic
{
	DECLARE_DYNAMIC(CStaticLog)

public:
	CStaticLog();
	virtual ~CStaticLog();
	void Paint(CDC &dc=*(CDC*)NULL);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


