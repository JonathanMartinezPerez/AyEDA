#include <iostream>
#include "nif.h"
#include "sequence.h"
#include "function.h"
#include "exploration.h"
#include "hash.h"
#include "usagetools.h"

int main(int argc, char* argv[]) {
    
    Options params(argc, argv);
    params.RunSimulation();

    return 0;
}
