#include <cstdio>
#include "include/xml.h"

int main ()
{
    xml x;
    x.parse_file("xml/main.xml");
    node n = x.nodes()[0];
    string t = n.type();
    printf("第一个节点:%s\n",n.type().c_str());
    printf("宽:%s\n",n["android:layout_width"].c_str());

    return 0;
}
