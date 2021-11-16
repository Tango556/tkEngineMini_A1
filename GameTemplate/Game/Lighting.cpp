#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting()
{
	
}

Lighting::~Lighting()
{

}

bool Lighting::Start()
{
	return true;
}

void Lighting::Update()
{
	
}

void Lighting::AddLig(DirectionLight DL)
{
	if (MaxDLig <= DLigNum)
	{
		return;
	}
	DLig[DLigNum] = &DL;
	DLigNum++;
}
void Lighting::AddLig(PointLight PL)
{
	if (MaxPLig <= PLigNum)
	{
		return;
	}
	PLig[PLigNum] = &PL;
	PLigNum++;
}
void Lighting::AddLig(SpotLight SL)
{
	if (MaxSLig <= SLigNum)
	{
		return;
	}
	SLig[SLigNum] = &SL;
	SLigNum++;
}
void Lighting::RemLig(REM_LIG rL , int lignum)
{
	switch (rL)
	{
	case Lighting::enD:
		if (DLigNum <= lignum)return;

		DLig[lignum] = nullptr;
		for (int alpha = lignum; DLig[alpha] == nullptr; alpha++)
		{
			if (DLig[alpha + 1] == nullptr)
			{
				break;
			}
			DLig[alpha] = DLig[alpha + 1];
		}
		break;
	case Lighting::enP:
		if (PLigNum <= lignum)return;

		PLig[lignum] = nullptr;
		for (int alpha = lignum; PLig[alpha] == nullptr; alpha++)
		{
			if (PLig[alpha + 1] == nullptr)
			{
				break;
			}
			PLig[alpha] = PLig[alpha + 1];
		}
		break;
	case Lighting::enS:
		if (SLigNum <= lignum)return;

		SLig[lignum] = nullptr;
		for (int alpha = lignum; SLig[alpha] == nullptr; alpha++)
		{
			if (SLig[alpha + 1] == nullptr)
			{
				break;
			}
			SLig[alpha] = SLig[alpha + 1];
		}
		break;
	default:
		return;
		break;
	}	
	return;
}

void Lighting::LigClear(bool DL, bool PL, bool SL)
{
	if (DL)
	{
		for (int alpha = 0; alpha < DLigNum; alpha++)
		{
			DLig[alpha] = nullptr;
		}
	}
	if (PL)
	{
		for (int alpha = 0; alpha < PLigNum; alpha++)
		{
			PLig[alpha] = nullptr;
		}
	}
	if (SL)
	{
		for (int alpha = 0; alpha < SLigNum; alpha++)
		{
			SLig[alpha] = nullptr;
		}
	}
}

void Lighting::SetAlig(AmbientLight AL)
{
	ALig = &AL;
}