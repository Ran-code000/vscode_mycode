#include <iostream>
#include <cmath>
using namespace std;
int main(){
    cout << "0.0 / 0.0 : " << 0.0 / 0.0 << endl;
    cout << "0.0 / inf : " << 0.0
    cout << std::isnan(0.0 / 0.0) << endl;
    cout << 1 << endl;
    return 0;
}