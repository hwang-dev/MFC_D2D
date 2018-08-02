#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual HRESULT Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	
};

