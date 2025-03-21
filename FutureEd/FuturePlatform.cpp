#include "FuturePlatform.h"
#include "FSLogin.h"

FuturePlatform::FuturePlatform() {

	SetApp(1024, 768, "Future Platform (open-source) - Star Signal Games");
	PushState(new FSLogin);
	Run();

}