#include"Engine.h"

int main(int argc, char** argv) {
	Engine engine;
	bool success = engine.Initialize();
	if (success) {
		engine.RunLoop();
	}
	engine.ShutDown();
	return 0;
}
