#pragma once


// CEditFloat

class CEditFloat : public CEdit
{
	DECLARE_DYNAMIC(CEditFloat)

public:
	CEditFloat();
	virtual ~CEditFloat();
	double operator = (double x);

protected:
	DECLARE_MESSAGE_MAP()
};


