#include "pch.h"
#include "CCollisionManager.h"

void CCollisionManager::Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT	rcCol{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcCol, Dst->Get_Rect(), Src->Get_Rect()))
			{
				// TODO : Implement collision logic
				Dst->On_Collision(Src);
				Src->On_Collision(Dst);
			}
		}
	}
}

void CCollisionManager::Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				// TODO : Implement collision logic
				if (Dst)
					Dst->On_Collision(Src);
				if(Src)
					Src->On_Collision(Dst);
			}
		}
	}
}

bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
{
	float	fWidth = fabsf(_Dst->Get_Position().x - _Src->Get_Position().x);
	float	fHeight = fabsf(_Dst->Get_Position().y - _Src->Get_Position().y);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Size().x + _Src->Get_Size().x) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionManager::Collision_RectEx(list<CObject*> _Dst, list<CObject*> _Src)
{
	float fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY)	// 상하 충돌
				{
					if (Dst->Get_Position().y < Src->Get_Position().y) // 상 충돌
					{
						Dst->Set_PosY(-fY);
					}
					else  // 하충돌
					{
						Dst->Set_PosY(fY);
					}
				}
				else			// 좌우 충돌
				{
					if (Dst->Get_Position().x < Src->Get_Position().x) // 좌 충돌
					{
						Dst->Set_PosX(-fX);
					}
					else  // 우 충돌
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionManager::Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	float	fDistanceX = fabsf(_Dst->Get_Position().x - _Src->Get_Position().x);
	float	fDistanceY = fabsf(_Dst->Get_Position().y - _Src->Get_Position().y);

	float	fRadiusX = (_Dst->Get_Size().x + _Src->Get_Size().x) * 0.5f;
	float	fRadiusY = (_Dst->Get_Size().y + _Src->Get_Size().y) * 0.5f;

	if ((fRadiusX >= fDistanceX) && (fRadiusY >= fDistanceY))
	{
		*pX = fRadiusX - fDistanceX;
		*pY = fRadiusY - fDistanceY;

		return true;
	}
	return false;
}