#include "Main.h"
#include "AppMain.h"
#include <conio.h>

USING_IRIS;

int main(int* argc, char** argv)
{   
    AppMain appMain;
    CustomObjectPool customPool;
    return IRIS_APPLICATION.run();
}
