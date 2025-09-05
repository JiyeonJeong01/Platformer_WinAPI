#pragma once
class InputKeyInfo
{
public:
	InputKeyInfo() : bPrevPressed(false), bCurrentPressed(false) {}
	~InputKeyInfo() {}

public:
	bool GetKeyDown() { return (!bPrevPressed && bCurrentPressed); }
	bool GetKey() { return (bPrevPressed && bCurrentPressed); }
	bool GetKeyUp() { return (bPrevPressed && !bCurrentPressed); }

public:
	bool Get_PrevPressed() const { return bPrevPressed; }
	bool Get_CurrentPressed() const { return bCurrentPressed; }
	void Set_PrevPressed(bool value) { bPrevPressed = value; }
	void Set_CurrentPressed(bool value) { bCurrentPressed = value; }

private:
	bool bPrevPressed;
	bool bCurrentPressed;
};