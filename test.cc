#include <cstdio>
#include "include/xml.h"

int main ()
{

    xml x;
    x.parse_file("xml/main.xml");
    vector<node> nodes = x.nodes()[0].inner();
    node n = nodes[0].inner()[1].inner()[0];
    string t = n.type();
    printf("类型:%s\n",t.c_str());
    printf("文本:%s\n",n["android:text"].c_str());
    printf("id:%s\n",n["android:id"].c_str());

    x.parse("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
    node h = x.header();
    printf("版本:%s\n",h["version"].c_str());
    return 0;
}
