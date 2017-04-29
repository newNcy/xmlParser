#ifndef _XML_H_
#define _XML_H_

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <iostream>
#define DEBUG
using std::vector;
using std::map;
using std::stringstream;
using std::string;
using std::ifstream;

/**
 * debug
 */
void debug(const string &msg)
{
#ifdef DEBUG
    std::cout<<msg; 
#endif
}


/**
 * 错误信息
 */
class xml_error
{
public:
    xml_error(){}
    xml_error(const string &_s):msg(_s) {}
    string msg;
};

/**
 * 标签
 */
class xml_tag 
{
protected:
    /* < />   < > </> */
    /* 类型名 */
    string type;
    /* 属性集合 */
    std::map<string,string> _attribute_set;
    /* 内部标签 */
    vector<xml_tag> inner; 
    /* 文本 */
    string inner_text;
public:
    /* 增删属性 */
     string  & operator[](const string & name)  
    {
           return (_attribute_set[name]);
    }

    /* 追加 内部标签 */
    const xml_tag & operator << (const xml_tag &newinner )
    {
        inner.push_back(newinner);
        return *this;
    }



};

/**
 * 头标签
 * */
class xml_header:public xml_tag
{

};

/**
 * 解析状态枚举
 */
enum _status{
    parse_key,
    parse_value
};

/**
 * xml
 */
class xml 
{
private:
    /* 内容缓冲 */
    stringstream ss; 
    /* 对象/类型 缓冲 */
    stringstream _type;
    /* 属性名缓冲 */
    stringstream _attr;
    /* 属性值缓冲 */
    stringstream _value;
    /* 错误信息 */
    xml_error _error;
    /* 头标签 */
    xml_tag _header;
    /* 标签存放 */
    vector<xml_tag> _tags;
    /* 是否正在解析value */
    _status status;
    /* 当前字符 */
    char ch;
    /* 获得下一个字符 */
    char getch();
    /* 放回字符 */
    /* 去除空白 */
    void skip();
    /* 解析属性名 */
    void parse_attr();
    /* 解析属性值 */
    void parse_value();
    /* 解析头标签 */;
    void parse_header();
    /*解析普通标签 */
    void parse_tag();

public:
    xml(const string & _raw ):ss(_raw) {}
    xml(){}
    xml(const char * _raw) :ss(_raw) {} 
   
    void parse();
    /* 解析字符串 */
    void parse(const string & _raw);
    void parse_file(const string &filename);

    /* 获取错误 */
    const xml_error & error() const { return _error;}

    /* 获取头标签 */
    const  xml_tag & header() const;
    ~xml(){}

};

#endif
