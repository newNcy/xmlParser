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


    char bit;
    while (! inf.eof()) {
        inf.read(&bit,1);
        doc.push_back(bit);
    }

    inf.close();
    parse();
}

/**
 * 真正的解析
 */
void xml::parse()
{
    look_ahead = false;
    _error = xml_error("no error");
    try {
        parse_header();
        while (true) {
         _tags.push_back( parse_tag());
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
    if (!_unget.empty()) {
        ch = _unget.top();
        _unget.pop();
    } else {
        if (doc.empty()) {
            throw std::runtime_error("finish");
        }
        ch = doc.front(); 
        doc.erase(doc.begin());
    }
    _past.push(ch);
#ifdef STREAM 
    debug(ch);
#endif

    return ch;
}
/* 放回 */
void xml::unget()
{
    char t = _past.top();
    _unget.push(t);
    _past.pop();
}

bool xml::skip()
{
    while (getch()) {
        if (ch == ' ') continue;
        if (ch == '\n') continue;
        else {
            unget();
            break;
        }
    }
    return true;
}


void xml::parse_type()
{
    skip();
    _type.str("");
    _type.clear();
    
    while(getch()) {
            if (ch == ' ' || ch == '\n')  break;
            if (ch == '>') {
                unget();
                break;
            }
            _type<<ch;
    }
    debug("type:"+_type.str() + "\n");

}
/**
 * 解析属性名
 */
void xml::parse_attr() 
{
    skip();
    _attr.str("");
    _attr.clear();
    while(getch()) {
            if (ch == ' ') {
                break;
            }else if (ch == '=' || ch == '>') {
                unget();
                break;
            }
            _attr<<ch;
    }

   debug("attr:"+_attr.str() + " ");
}
/**
 * 解析属性值
 */
void xml::parse_value()
{
    skip();
    _value.str("");
     _value.clear();
   
     getch();
     if(ch != '\'' && ch != '\"') {
            throw std::runtime_error("应该是 ''' 或者 '\"' :");
        }
        char be = ch;
        while (getch()) {
            if (ch == be) break;
            _value<<ch;
        }
        debug("value:"+_value.str() + "\n");
}

/**
 * 解析文本 
 */
void xml::parse_text()
{
    skip();
    _text.str("");
    _text.clear();
    while (getch()) {
        if (ch == '<') {
            unget();
            break;
        }else {
            _text<<ch;
        }
    }

    debug("text:"+_text.str() + "\n");
}

/**
 * 解析头标签
 */
void xml::parse_header()
{
    

    skip();
    getch();
    if (ch != '<') throw std::runtime_error("需要 <");
    getch();
    if (ch != '?') throw std::runtime_error("需要 ?");

    parse_type();
    if (string("xml") != _type.str()) {
        throw std::runtime_error("缺少'xml'");
    }

    while (!doc.empty()) {
        skip();
            if (getch() == '?' ) {
                if (getch() == '>') {
                    break;
                }else {
                    throw std::runtime_error("应该是以 '>' 结尾");
                } 
            }else {
                unget();
            }
        parse_attr(); 
        if(getch() != '=') throw std::runtime_error("需要 =");
        skip();
        parse_value();
        _header[_attr.str()]= _value.str();
    }
    
    
}

/**
 * 解析标签
 */
xml_tag & xml::parse_tag()
{
    skip();
     xml_tag *tag = new xml_tag;
     if(getch() != '<') {
         throw std::runtime_error("需要 <");
     } 

    /* 解析类型 */
    parse_type();
    parsing = tag->type( _type.str());
    debug("开始解析:"+tag->type()+"\n");
    /* 解析属性 */
    while (skip()) {
        /* 碰到 '/>' 解析结束 */
        if (getch() == '/') {
            if (getch() == '>') {
                debug("返回:"+tag->type()+"\n");
                return *tag;
            }else {
                throw std::runtime_error("需要 '>'");
            }
        }else {
            unget();
        }
        /* 碰到 '>' 向下解析 */
        if (getch() == '>') {
            break;
        }else {
            unget();
        }
        

        parse_attr();
        skip();
        if (getch() != '=') {
            throw std::runtime_error("缺少 '='");
        }else {
        }
        skip();
        parse_value();

        (*tag)[_attr.str()] = _value.str();
 
    }

    /* 解析节点内容 */
    skip();
    /* 是否文本 */
    if(getch() != '<') {
        unget();
        debug("文本\n");
        parse_text();
    }else {
        debug("碰到'<'\n");
        unget();
    }
    /* 是否结束 */
    while (skip() ) {
        getch();
        if (ch != '<') {
            throw std::runtime_error("此处必须为 '<'");
        }
        if (getch() == '/') {
            parse_type();
            debug("关闭标签:"+_type.str()+"\n");
            skip();
            getch();
            return *tag;
        }
#define STREAM
        unget();
        unget();
#undef STREAM
        (*tag)<<parse_tag();
    }

    return *tag;
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
    std::cout<<"解析结果:"<<_xml.error().msg<<std::endl;
    xml_tag h = _xml.header();
    std::cout<<h["version"];


}
