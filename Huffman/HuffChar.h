//
// Created by tianbao on 17-11-26.
//

#ifndef _HUFFCHAR_H
#define _HUFFCHAR_H

class HuffChar {

public:

    char ch;
    int weight;//字符的频率
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}

    bool operator<(const HuffChar &temp) const { return weight > temp.weight; }//此处大小是颠倒的
    bool operator== (const HuffChar &temp) const {return weight == temp.weight;}

};

#endif