#include "MiniginPCH.h"

#ifdef _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//#include <vld.h>
#endif

#include "SDL.h"
#include "SilverFoxEngine.h"

int main(int, char*[])
{
	fox::SilverFoxEngine engine{};
	engine.Run();

    return 0;
}