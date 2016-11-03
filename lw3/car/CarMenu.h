#pragma 

#include "Car.h"

class CCarMenu
{
public:
	CCarMenu(CCar & car);
	~CCarMenu()  = default;
	
	void CCarMenu::GetInfo() const;	
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	void RunCommand(std::string & command);

private:
	CCar & m_car;
};
