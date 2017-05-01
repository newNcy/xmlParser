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
string  & node::attr(const string & name)  
{
    return (_attribute_set[name]);
}

const node & node::operator << (const node &newinner )
{
    return add_node(newinner);
}
const node & node::add_node (const node &newinner )
{
    _inner.push_back(newinner);
    return *this;
}
const vector<node> & node::inner()const 
{
    return _inner;
}


