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

	static CObj* CreateObj(INFO& tInfo)
	{
		CObj* pObj = new T;

		if (FAILED(pObj->Initialize()))
		{
			SafeDelete(pObj);
		}

		pObj->SetInfo(tInfo);
		return pObj;
	}

	static CObj* CreateObj(D3DXVECTOR3& vPos, float _fAngle)
	{
		CObj* pObj = new T;

		if (FAILED(pObj->Initialize()))
		{
			SafeDelete(pObj);
		}


		pObj->SetPos(vPos);
		pObj->SetAngle(_fAngle);
		return pObj;
	}
};

template <typename T1, typename T2>
class CEffectFactory 
{
public:
	static CObj* CreateEffect(D3DXVECTOR3& vPos, const TCHAR* szStateKey, const FRAME& tFrame)
	{
		T2* pAnim = new T2;
		pAnim->SetStateKey(szStateKey);
		pAnim->SetFrame(tFrame);

		CObj* pEffect = CAbstractFactory<T1>::CreateObj(vPos);
		dynamic_cast<T1*>(pEffect)->SetBridge(pAnim);

		return pEffect;
 	}
};

//template <typename T>
//class IMPFactory
//{
//public:
//	static CBossIMP* CreateIMP()
//	{
//		T = new T
//	}
//};