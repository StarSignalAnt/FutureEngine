#include "FCEp1.h"
#include "StateTest1.h"
#include "StateLogoScreen.h"

FCEp1::FCEp1()
{
	SetApp(1024, 768, "Future Calling - Episode 1 \"The Future Calling\"");
	PushState(new StateTest1);
	Run();
}