#include <iostream>
#include <thread>
#include <string>

using namespace std;

void hello(int n, const string & str) {
    for(int k = 0; k < n; k++) {
        cout << str << "\n";
    }
}
int main()
{
    int a;
    a = 5;
    int b = 5;
    if(a <= 5) cout << "ala";
    thread w1;
    w1 = thread(hello, 5, "hi!");
    w1.join();
    cout << "Hello World!" << endl;
    return 0;
}
