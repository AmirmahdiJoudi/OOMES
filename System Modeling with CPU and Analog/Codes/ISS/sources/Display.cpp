#include "Display.h"

void Display::Displaying()
{
	while(true)
	{
		if(en == SC_LOGIC_1)
		{
			cout << "************************************"<< endl;
			cout << "************************************"<< endl;
			if(data == SC_LOGIC_1)
				cout << "Display = Passed" << endl;
			else
				cout << "Display = Failed" << endl;
			cout << "************************************"<< endl;
			cout << "************************************"<< endl;
		}
		wait();
	}
}
