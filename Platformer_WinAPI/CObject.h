#pragma once
class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

protected:
	void		Update_Rect();

public :
	const Vector2& Get_Position() const { return m_vPosition;  }
	const Vector2& Get_Direction() const { return m_vDirection; }
	const Vector2& Get_Size() const { return m_vSize; }

	const RECT* Get_Rect() { return &m_tRect;  }

	void Set_PosX(float _fX) { m_vPosition.x = _fX; }
	void Set_PosY(float _fY) { m_vPosition.y = _fY; }
	void Set_DirX(float _fX) { m_vDirection.x = _fX; }
	void Set_DirY(float _fY) { m_vDirection.y = _fY; }
	void Set_SizeX(float _fX) { m_vSize.x = _fX; }
	void Set_SizeY(float _fY) { m_vSize.y = _fY; }

	OBJID Get_ObjectID() { return m_objID; }
	virtual void		On_Collision(CObject* pObj) {};
	
protected:
	// Core components
	Vector2 m_vPosition;
	Vector2 m_vDirection;
	Vector2 m_vSize;

	// Renderer
	RECT		m_tRect;

	float		m_fSpeedX;
	float		m_fSpeedY;
	bool		m_bDead;

	OBJID m_objID;
};

