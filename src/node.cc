#include "../include/node.h"

string & node::type(const string & _t)  
{
        if (_t.length() > 0)
        {
            return _type = _t;
        }else {
            return _type;
        }
}

string & node::text (const string & _t ) {
    if (_t.length() > 0) {
            return inner_text = _t;
    }else {
            return inner_text;
    }
}

string  & node::operator[](const string & name)  
{
    return (_attribute_set[name]);
}

const node & node::operator << (const node &newinner )
{
    _inner.push_back(newinner);
    return *this;
}


