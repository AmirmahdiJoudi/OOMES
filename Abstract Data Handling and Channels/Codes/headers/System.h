#ifndef __SYSTEM_H
#define __SYSTEM_H "system.h"

#include "channel_interface.h"
#include "GrayScaler.h"
#include "EdgeDetector.h"

SC_MODULE(System)
{
	fifo* FIFO;
	GrayScaler* GS;
	EdgeDetector* ED;

	SC_CTOR(System)
	{
		FIFO = new fifo();
		GS = new GrayScaler("GrayScaler");
			GS->out(*FIFO);
		ED = new EdgeDetector("EdgeDetector");
			ED->in(*FIFO);
	}
};

#endif