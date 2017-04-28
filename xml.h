#ifndef _XML_H_
#define _XML_H_

#include <vector>
#include <map>

class xml_tag;
class xml 
{
private:
    xml_tag header;
    vector<xml_tag> tags;

};
class xml_tag 
{
private:
   string type;
   std::map<string,string> attribute_set;
   vector<xml_tag> inner; 
};
#endif
