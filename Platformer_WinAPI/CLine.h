#pragma once

// For testing in Stage04. Can be modified or deleted freely.
class CLine
{
public:
	CLine();
	CLine(LINEPOINT& _leftPoint, LINEPOINT& _rIghtPoint);
	~CLine();

public:
	void Render(HDC hDC);

public:
	const LINE& Get_Info() const { return m_tInfo; }

private:
	LINE m_tInfo;
};
