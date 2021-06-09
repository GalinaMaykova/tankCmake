
#include <iostream>
#include <vector>
//#include "gmock\gmock.h"

#include "myVector.h"


int main(int argc, char** argv)
{

    std::vector<int> p(2);
    p[0] = 2;
    p[1] = 7; //{2, 7}
    myVector pos(p);
//    testing::InitGoogleMock(&argc, argv);
  //  RUN_ALL_TESTS();
    std::cout << p[1] + 1  << std::endl;
    int x;
    std::cin >> x;
}