
// ArbitraryEnergyView.h : interface of the CArbitraryEnergyView class
//

#pragma once

#include "3DWindow.h"

class CArbitraryEnergyView : public CView, public C3DWindow
{
protected: // create from serialization only
	CArbitraryEnergyView();
	DECLARE_DYNCREATE(CArbitraryEnergyView)

// Attributes
public:
	CArbitraryEnergyDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CArbitraryEnergyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DoPaint(CDC &dc=*(CDC*)NULL);
	virtual void Paint();
	void PaintSphere(double radius,unsigned char red,unsigned char green,unsigned char blue,bool half);
	void PaintCircle(double radius1,unsigned char red1,unsigned char green1,unsigned char blue1,double radius2,unsigned char red2,unsigned char green2,unsigned char blue2);
	class CGetXValue
	{
	public:
		double Go(int index,void * user_data);
	};
	double m_round_face_min,m_round_face_max;
	TCHAR m_round_face_string[1024];
	void PaintRoundFace(double radius,void * thiz,double (CGetXValue::*Go)(int index,void * user_data),int count,void * user_data=NULL);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in ArbitraryEnergyView.cpp
inline CArbitraryEnergyDoc* CArbitraryEnergyView::GetDocument() const
   { return reinterpret_cast<CArbitraryEnergyDoc*>(m_pDocument); }
#endif

