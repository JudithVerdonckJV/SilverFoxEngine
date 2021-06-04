#include <iostream>
#include <SilverFoxEngine.h>

#include "SceneSetup.h"
#include "ResourceManager.h"

int main()
{
	fox::SilverFoxEngine engine{};
	engine.Initialize();
	SceneSetup sceneSetup{};
	engine.Run();

	return 0;
}
