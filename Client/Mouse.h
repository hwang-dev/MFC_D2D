#pragma once
class CMouse
{
	DECLARE_SINGLETON(CMouse)

private:
	CMouse();
	~CMouse();

public:
	void Update();
	void Render();
	D3DXVECTOR3& GetMousePos();

private:
	D3DXVECTOR3 m_vMouse;

};

