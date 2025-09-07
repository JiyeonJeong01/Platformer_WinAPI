#pragma once

class CScrollManager
{
private:
	CScrollManager();
	virtual ~CScrollManager();

public:
	void		Set_ScrollX(float _X) { m_fScrollX += _X; }
	void		Set_ScrollY(float _Y) { m_fScrollY += _Y; }

	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

public:
	static CScrollManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CScrollManager();

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollManager* m_pInstance;

	float m_fScrollX;
	float m_fScrollY;

};

