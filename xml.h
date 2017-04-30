#ifndef _XML_H_
#define _XML_H_

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <stack>
#include <stdexcept>
#include <iostream>
#include "node.h"

//#define DEBUG
//#define STREAM
using std::vector;
using std::map;
using std::stringstream;
using std::string;
using std::ifstream;
using std::stack;

/**
 * debug
 */
#ifdef DEBUG
int tabs = 0;
#endif
template <typename T>
void debug(const T &msg)
{
#ifdef DEBUG
    for (int i = 0;i<tabs;i++) {
        std::cout<<"\t";
    }
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
 * 头标签
 * */
class xml_header:public node
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
    vector<char> doc; 
    /* 对象/类型 缓冲 */
    stringstream _type;
    /* 属性名缓冲 */
    stringstream _attr; 
    /* 属性值缓冲 */
    stringstream _value;
    /* 文本缓冲 */
    stringstream _text;
  
    /* 正在解析 */
    string parsing;
    /* 错误信息 */
    xml_error _error;
    /* 头标签 */
    node _header;
    /* 标签存放 */
    vector<node> _nodes;
    /* 是否正在解析value */
    _status status;
    /* 当前字符 */
    char ch;
    /* 取出来的字符 */
    stack<char> _past;
    /* 放回去的字符 */
    stack<char> _unget;
    /* 前看一个字符 */
    bool look_ahead;
    /* 获得下一个字符 */
    char getch();
    /* 放回字符 */
    void unget();
    /* 去除空白 */
    bool skip();
    /* 解析类型 */
    void parse_type();
    /* 解析属性名 */
    void parse_attr();
    /* 解析属性值 */
    void parse_value();
    /* 解析内容 */
    void parse_text();
    /* 解析头标签 */;
    void parse_header();
    /*解析普通标签 */
    node  & parse_node();

public:
    xml(const string & _raw ) {}
    xml(){}
    xml(const char * _raw){} 
   
    void parse();
    /* 解析字符串 */
    void parse(const string & _raw);
    void parse_file(const string &filename);

    /* 获取错误 */
    const xml_error & error() const { return _error;}

    /* 获取头标签 */
    const  node & header() const;
    const vector <node> & nodes() const ;
    ~xml(){}

};

#endif
