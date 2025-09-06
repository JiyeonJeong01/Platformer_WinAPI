#pragma once

// For testing in Stage04. Can be modified or deleted freely.
class CLine
{
public:
	CLine();
	CLine(Vector2& _leftPoint, Vector2& _rIghtPoint);
	~CLine();

public:
	void Render(HDC hDC);

public:
	const LINE& Get_Info() const { return m_tLine; }

private:
	LINE m_tLine;
};
