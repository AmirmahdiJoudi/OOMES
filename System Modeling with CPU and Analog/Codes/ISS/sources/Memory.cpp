#include "Memory.h"

template <int adrBit, int dataBit>
void memory <adrBit, dataBit> :: init()
{
	int i = 0;
	sc_lv <dataBit> data;
	ifstream initFile;
	initFile.open("CA6ISS.txt");
	while(!(initFile.eof()))
	{
		if( i < memRange)
		{
			initFile >> data;
			mem[i] = data;
			cout << "data is  " << mem[i] << endl; 
			i++;
			
		}
	}
	initFile.close();
}
template <int adrBit, int dataBit>
void memory <adrBit, dataBit> :: readMem()
{
	sc_lv<adrBit> tempAdr;
	tempAdr = address;
	if (CS -> read() == '1')
	{
		if(memRead -> read() == '1')
		{
			if(tempAdr.to_uint() < memRange)
			{
				dataOut = mem[tempAdr.to_uint()];
			}
		}
	}
}

template <int adrBit, int dataBit>
void memory <adrBit, dataBit> :: writeMem()
{
	sc_lv <adrBit> tempAd;
	
	if (CS -> read() == '1')
	{
		tempAd = address;
		if (tempAd.to_uint() < memRange)
		{
			if(memWrite -> read() == '1')
			{
				mem[tempAd.to_uint()] = dataIn -> read();
			}
		}
	}
}

template <int adrBit, int dataBit>
void memory <adrBit, dataBit> :: dump()
{
	ofstream out;
	wait (30, SC_NS);
	out.open("dump.txt");
	for (int i = 0; i < memRange; i++)
	{
		out << i << "\t" << mem[i] << endl;
	}
	out.close();
}

template <int adrBit, int dataBit>
void memory <adrBit, dataBit> :: setMemReady()
{
	sc_lv <adrBit> tempAd;
	memReady = SC_LOGIC_0;
	cout << "memReady Ready is " << memReady << endl;
	if (CS -> read() == '1')
	{
		tempAd = address;
		if (tempAd.to_uint() < memRange)
		{
			if(memWrite -> read() == '1' || memRead -> read() == '1')
			{
				memReady = SC_LOGIC_1;
			}
		}
	}
}