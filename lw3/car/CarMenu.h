#pragma 

#include "Car.h"

class CCarMenu
{
public:
	CCarMenu(CCar & car);
	~CCarMenu()  = default;
	
	void CCarMenu::GetInfo() const;

	void RunCommand(std::string & command);

private:
	CCar & m_car;
};
