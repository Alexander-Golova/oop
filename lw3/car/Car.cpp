#include "stdafx.h"

#include "Car.h"


CCar::CCar()
{
}


CCar::~CCar()
{
}


bool CCar::TurnOnEngine()
{
	return false;
}


bool CCar::TurnOffEngine()
{
	return false;
}


bool CCar::IsEngineTurnOn() const
{
	return false;
}


bool CCar::SetGear(Gear gear)
{
	return false;
}


Gear CCar::GetGear() const
{
	return Gear();
}


bool CCar::SetSpeed(unsigned speed)
{
	return false;
}


unsigned CCar::GetSpeed() const
{
	return 0;
}


Direction CCar::GetDirection() const
{
	return Direction();
}
