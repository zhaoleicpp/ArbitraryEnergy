#pragma once

class C3DWindow
{
protected:
	unsigned char m_data[1024*2];
	void UpdateLook(void);
public:
	void SetSize(double size);
	void SetSize(int width,int height);
	void OnLeftButtonDown(int x,int y);
	void OnMouseDrag(int x,int y);
	void OnMouseWheel(short delta);
	void SetLook(double from[3],double at[3]);
	int GetWidth();
	int GetHeight();
	void GetLookDirection(double direction[3]);
	void *GetImageData();
public:
	C3DWindow();
	~C3DWindow();
	void Initialize();
	void Uninitialize();
	void Render();
	void Add(double x0,double y0,double z0,unsigned char red0,unsigned char green0,unsigned char blue0,double x1,double y1,double z1,unsigned char red1,unsigned char green1,unsigned char blue1,double x2,double y2,double z2,unsigned char red2,unsigned char green2,unsigned char blue2);
	void Add(double x0,double y0,double z0,unsigned char red0,unsigned char green0,unsigned char blue0,double x1,double y1,double z1,unsigned char red1,unsigned char green1,unsigned char blue1);
	void Add(double x,double y,double z,unsigned char red,unsigned char green,unsigned char blue);
	void Add(double x,double y,double z,void const * image,int width,int height,int start_x=0x7fffffff,int start_y=0x7fffffff);
	void TurnOnLight(double light_direction[3]);
	void TurnOffLight();
	virtual void Paint();
};
