#include "src/mainclass.h"

int main(int argc, char* argv[])
{
    MainClass mc(argc, argv);
    return mc.connectAndExec();
}

