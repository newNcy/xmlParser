#include <iostream>
#include "xml.h"


void xml::parse_file(const string &filename)
{
    ifstream inf(filename);

    if(!inf.is_open()) {
       throw std::runtime_error("无法打开文件");
    }

    ss.str("");
    ss.clear();

    char bit;
    while (! inf.eof()) {
        inf.read(&bit,1);
        ss<<bit;
    }

    inf.close();
    parse();
}

void xml::parse()
{
    parse_header();
    while (ss.good()) {
        parse_tag();
    }
}


void xml::parse_header()
{
    char ch;
    
    ss>>ch;

    while (ch == ' ') ss>>ch;
    if (ch != '<') throw std::runtime_error("不是有效的xml开始符号,需要 '<' 而得到");
    ss>>ch;
    if (ch != '?') throw std::runtime_error("不是有效的头标签符号");
    char _xml[4];
    ss>>_xml;
    if (string("xml") != string(_xml)) {
        throw std::runtime_error("缺少'xml'");
    }

    stringstream key;
    stringstream value;
    while (ss.good() ) {
        /* 解析属性名 */
        while(ss>>ch) {
            if (ch == ' ') continue;
            if (ch == '=') {
                break;
            }
            key<<ch;
        }

        /* 除去空白 */
        /* 解析属性值 */
        while (ss>>ch) {
            if (ch != ' ') break;
        }
        if(ch != '\'' && ch != '\"') {
            throw std::runtime_error("应该是 ''' 或者 '\"' :"  );
        }
        char be = ch;
        while (ss>>ch) {
            if (ch == be) break;
            value<<ch;
        }
        
        while(ss>>ch) {
            if(ch!=' ') break;
        }
    
        
    }
    
    
}
void xml::parse_tag()
{

}
int main ()
{
    xml _xml;
    _xml.parse_file("a.xml");
}
