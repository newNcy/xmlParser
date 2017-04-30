#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>
#include <map>

using std::map;
using std::vector;
using std::string;
/**
 * 标签
 */
class node
{
protected:
    /* 类型名 */
    string _type;
    /* 属性集合 */
    std::map<string,string> _attribute_set;
    /* 内部标签 */
    vector<node> _inner; 
    /* 文本 */
    string inner_text;
public:
    /* 类型 */
    string & type(const string & _t = ""); 
    /* 文本 */
    string & text(const string & _t = "");
    /* 增删属性 */
    string  & operator[](const string & name);
    /* 追加 内部标签 */
    const node & operator << (const node &newinner );

};

#endif
