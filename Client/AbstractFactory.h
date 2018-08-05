#pragma once

class CObj;
template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;

		if (FAILED(pObj->Initialize()))
		{
			SafeDelete(pObj);
		}

		return pObj;
	}

	static CObj* CreateObj(D3DXVECTOR3& vPos)
	{
		CObj* pObj = new T;

		if (FAILED(pObj->Initialize()))
		{
			SafeDelete(pObj);
		}

		pObj->SetPos(vPos);

		return pObj;
	}
};