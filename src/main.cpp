#include "main.hpp"

Engine* e;

int main() {
	srand((unsigned int)time(0));

	e = new Engine(160, 100);
    
	e->Init();
	e->Load();

	while(!TCODConsole::isWindowClosed() && !e->leaveGame) {
		TCODSystem::sleepMilli(10);

        e->Update();
        e->Render();

        TCODConsole::flush();
    }

    e->Save();

	//NOTE: This calls the close function in the Engine class.
	delete e;
	e = nullptr;

    return(0);
}