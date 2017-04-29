#include "xml.h"


/**
 * 从文件解析
 */
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

/**
 * 真正的解析
 */
void xml::parse()
{
    try {
        parse_header();
        while (ss.good()) {
            parse_tag();
        }
    }catch (std::runtime_error e) {
        _error = xml_error(e.what());
    }
}

/**
 * 下一个字符
 */
char xml::getch()
{
    ss>>ch;
    string chh = &ch;
    debug(chh);
    return ch;
}

void xml::skip()
{
    while (getch()) {
        if (ch == ' ') continue;
        if (ch == '\n') continue;
        else break;
    }
}

/**
 * 解析属性名
 */
void xml::parse_attr() 
{
    _attr.str("");
    _attr.clear();
    while(true) {
            if (ch == ' ') {
                skip();
                break;
            }else if (ch == '=') {
                break;
            }
            _attr<<ch;
            getch();
    }

    debug("attr:"+_attr.str());
}
/**
 * 解析属性值
 */
void xml::parse_value()
{
    _value.str("");
     _value.clear();
    
     if(ch != '\'' && ch != '\"') {
            throw std::runtime_error("应该是 ''' 或者 '\"' :");
        }
        char be = ch;
        while (getch()) {
            if (ch == be) break;
            _value<<ch;
        }
        debug("value:"+_value.str());
}

/**
 * 解析头标签
 */
void xml::parse_header()
{
    

    skip();
    char s[2];
    ss>>s;
    if(string("<?") != string(s)) throw std::runtime_error("缺少开始符号");
    skip();
    char _xml[4];
    ss>>_xml;
    if (string("xml") != string(_xml)) {
        throw std::runtime_error("缺少'xml'");
    }

    while (ss.good() ) {
        skip();
            if (ch == '?' ) {
               getch();
                if (ch == '>') {
                   throw std::runtime_error("头标签解析结束");
                    break;
                }else {
                    throw std::runtime_error("应该是以 '>' 结尾");
                } 
            }
        parse_attr(); 
        if(ch != '=') throw std::runtime_error("需要 =");
        skip();
        parse_value();
        _header[_attr.str()]= _value.str();
    }
    
    
}

/**
 * 解析标签
 */
void xml::parse_tag()
{

}



/**
 * 获取头标签
 */
const xml_tag & xml::header() const 
{
    return _header;
}
int main ()
{
    xml _xml;
    _xml.parse_file("a.xml");
    std::cout<<"result:"<<_xml.error().msg<<std::endl;
    xml_tag h = _xml.header();

   debug("版本:"+h["version"]);
   debug("编码:"+h["encoding"]);
}
