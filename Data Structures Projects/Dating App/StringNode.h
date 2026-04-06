// StringNode.h
#ifndef STRINGNODE_H
#define STRINGNODE_H
#include <string>
using namespace std;

struct StringNode {
    string phone;
    StringNode* next;
    StringNode(string p) : phone(p), next(nullptr) {}
};
#endif