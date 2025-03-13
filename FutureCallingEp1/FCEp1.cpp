#include "FCEp1.h"
#include "StateTest1.h"

FCEp1::FCEp1()
{
	SetApp(1024, 768, "FCEp1");
	PushState(new StateTest1);
	Run();
}