#include "interface/Engine.h"

using namespace std;

int main()
{
    //instantiate object
    Engine engine;

    //engine loop
    while(engine.running()){
        //update frame by frame
        engine.update();
        //render frame
        engine.render();
    }

    return 0;
}