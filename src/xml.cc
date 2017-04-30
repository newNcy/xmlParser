#include "../include/xml.h"


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
         _nodes.push_back( parse_node());
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
        if (doc.empty()) {
            throw std::runtime_error("finish");
        }
        ch = doc[0]; 
        doc.erase(doc.begin());
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
    doc.insert(doc.begin(),t);
    //debug("放回:"+t);
    _past.pop();
}

bool xml::skip()
{
    while (getch()) { 
        //过滤不可见字符
        if ((0 <= ch && ch <= 32 ) || ch == 127) {
            continue;
        }else  {
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
    debug("类型:"+_type.str() + "\n");

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

   debug("属性:"+_attr.str() + " ");
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
        debug("属性值:"+_value.str() + "\n");
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

    debug("文本:"+_text.str() + "\n");
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
node & xml::parse_node()
{
    skip();
     node *_node = new node;
     if(getch() != '<') {
         throw std::runtime_error("需要 <");
     } 

    /* 解析类型 */
    parse_type();
    parsing = _node->type( _type.str());
    debug("开始解析:"+_node->type()+"\n");
    /* 解析属性 */
    while (skip()) {
        /* 碰到 '/>' 解析结束 */
        if (getch() == '/') {
            if (getch() == '>') {
                debug("返回:"+_node->type()+"\n");
                skip();
                return *_node;
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

        (*_node)[_attr.str()] = _value.str();
 
    }

    /* 解析节点内容 */
    while (skip() ) {
        /* 是否文本 */
    if(getch() != '<') {
        unget();
        debug("文本\n");
        parse_text();
        _node->text(_text.str());
    }else {
    
    /* 是否结束 */
    
        if (getch() == '/') {
            parse_type();
            debug("关闭标签:"+_type.str()+"\n");
            skip();
            if (getch() != '>') 
            {
                throw std::runtime_error("需要 '>'");
            }
            return *_node;
        }
        unget();
        unget();
        (*_node)<<parse_node();
    }

    }

    
    return *_node;
}




/**
 * 获取头标签
 */
const node & xml::header() const 
{
    return _header;
}

/**
 * 获取标签
 */
const vector <node> & xml::nodes()const 
{
    return _nodes;
}

