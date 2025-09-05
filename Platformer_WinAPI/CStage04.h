#include "CStage.h"

class CStage04 : public CStage
{
public:
	CStage04();
	virtual ~CStage04();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:

};