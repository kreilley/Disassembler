// demo split string class
// source: https://www.cplusplus.com/articles/1UqpX9L8/

#ifndef __SPLIT_STRING_H__
#define __SPLIT_STRING_H__
#include <string>
#include <vector>
#include <iostream>


class splitstring : public std::string {
    std::vector<std::string> flds;
public:
    splitstring(char *s) : std::string(s) { };
    std::vector<std::string>& split(char delim, int rep=0);
};
#endif // __SPLIT_STRING_H__
