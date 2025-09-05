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
	virtual void		On_Collision(CObject* pObj) {}; 	// 충돌 시 CollisionManager에서 호출된다
																				// 충돌 로직 구현은 각 객체에게 위임한다
	
protected:
	// Core components
	Vector2 m_vPosition;		// 객체의 위치, 중점
	Vector2 m_vDirection;		// 객체의 방향
	Vector2 m_vSize;				// 객체의 크기

	// Renderer
	RECT		m_tRect;			// 객체의 렌더 범위

	float		m_fSpeedX;			// 수평 방향 속도
	float		m_fSpeedY;			// 수직 방향 속도
	bool		m_bDead;			

	OBJID m_objID;				// 객체를 구분하는 enum
};

