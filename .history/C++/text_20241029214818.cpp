#include <iostream>
using namespace std;
int main(){
    int x = -9999999;
    unsigned int y = x;
    int t = y;
    unsigned short z = x;
    short w =  x;
    cout << x << endl << t << endl << y << endl << z << endl << w << endl;
    cout << "int: " << sizeof(x) << endl << "short: " << sizeof(z) << endl; << "unsigned int: " << sizeof(y) << endl << "unsigned short: " << sizeof(w) << endl; 
    return 0;
}