#include "sortmethod.h"

#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    SortMethod<int> s(v);
    s.Sort();
    return 0;
}