#include <iostream>
#include <vector>


int main(){
    std::vector<double> test;

    test.push_back(1.0);
    test.push_back(2.0);

    for(double val : test){
        std::cout << val << std::endl;
    }
    return 0;
}