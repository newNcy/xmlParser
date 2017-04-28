#ifndef _XML_H_
#define _XML_H_

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>

using std::vector;
using std::map;
using std::stringstream;
using std::string;
using std::ifstream;

class xml_error
{

};
class xml_tag 
{
private:
    /* < />   < > </> */
    string begin,end;
    string type;
    std::map<string,string> attribute_set;
    vector<xml_tag> inner; 
    string value;

};

class xml_header:public xml_tag
{

};

enum _status{
    parse_key,
    parse_value
};
class xml 
{
private:
    /* 内容缓冲 */
    stringstream ss; 
    /* 错误信息 */
    xml_error _error;
    /* 头标签 */
    xml_header header;
    /* 标签存放 */
    vector<xml_tag> tags;
    /* 是否正在解析value */
    _status status;
    /* 解析头标签 */
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
    xml_error & error() const;

    ~xml(){}

};

#endif
