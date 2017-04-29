#include <iostream>
#include <sstream>

using namespace std;

int main ()
{
    stringstream ss("abcd");
    char ch;
    ss>>ch;
    cout<<ch;
    ss.clear();
    const string s = ss.str();
    string a = &ch;
    ss.str(a+s);
    ss>>ch;
    ss>>ch;
    cout<<ch;
}
