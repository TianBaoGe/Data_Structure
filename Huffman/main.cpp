#include <bitset>
#include <queue>
#include "BinTree.h"
#include "HuffChar.h"
#include <map>
#include <fstream>
#include <cassert>
#include <sstream>
using std::priority_queue;
using std::bitset;
using std::vector;
using std::map;
using std::string;
using std::ostringstream;
using std::ifstream;
using std::noskipws;
using std::ofstream;


#define HuffTree BinTree<HuffChar>
#define N_CHAR (0x80 - 0x20)
typedef map<char,string> HuffTable;
typedef bitset<96> HuffCode;
typedef priority_queue<HuffTree*> HuffForest;

vector<int>* statistics(string address){

    ifstream infile(address);//若失败,则输出错误消息,并终止程序运行
    assert(infile.is_open());
    vector<int>* array = new vector<int>(96);

    char c;
    infile >> noskipws;
    while (!infile.eof())
    {
        infile>>c;
        (*array)[c-32]++;
    }
    infile.close();
    return array;
}

HuffForest* initForest(vector<int>* freq) {

    HuffForest* forest = new HuffForest;
    for(int i = 0;i < N_CHAR; ++i ) {
        HuffTree* newTree = new HuffTree();
        newTree->insertAsRoot(HuffChar(32+i,(*freq)[i]));
        forest->push(newTree);
    }
    return forest;
}

HuffTree* generateTree(HuffForest* forest) {

    while(1 < forest->size()) {

        HuffTree* s1 = forest->top();forest->pop();
        HuffTree* s2 = forest->top();forest->pop();
        HuffTree* s = new HuffTree();
        s->insertAsRoot(HuffChar('^',s1->root()->data.weight+s2->root()->data.weight));
        s->attachAsLTree(s->root(),s1);
        s->attachAsRTree(s->root(),s2);
        forest->push(s);
    }
    //到这里，整个优先队列只剩下一棵树了，就是我们要求的最终树
    HuffTree* tree = forest->top();
    forest->pop();
    delete forest;//树已经完全了，所以队列没用了
    return tree;

}

string toString(bitset<96>& code,int length) {

    ostringstream os;
    for(int i = 0;i<length;i++) os << code[i];
    string temp =os.str();
    return temp;
}

void generateCT(bitset<96>& code,size_t length,HuffTable* table,BinNode<HuffChar>* v) {

    if(IsLeaf(*v)) {

        (*table)[v->data.ch] = toString(code,length);
        return;
    }
    if(HasLChild(*v)) {code.reset(length);generateCT(code,length+1,table,v->Lc);}
    if(HasRChild(*v)) {code.set(length);generateCT(code,length+1,table,v->Rc);}
}

HuffTable* generateTable(HuffTree* tree) {

    HuffTable* table = new HuffTable;
    bitset<96> code;
    generateCT(code,0,table,tree->root());
    return table;
}

string encode(HuffTable*table,string s) {

    ostringstream os;
    int n = 0;
    for(size_t m = s.length(),i = 0;i<m;++i) {

        string pCharCode = (*table)[s[i]];
        if(pCharCode == "") pCharCode = (*table)[' '];//不能识别的字符，统一当做空格处理
        os << pCharCode;
    }
    string result = os.str();
    return result;
}

void decode(HuffTree* tree,string& code) {

    BinNode<HuffChar>* x = tree->root();
    unsigned long n = code.length();
    for(int i = 0;i<n;++i) {

        x = (code[i] == '0')?x->Lc:x->Rc;
        if(IsLeaf(*x)) std::cout << x->data.ch,x = tree->root();
    }
    std::cout << std::endl << std::endl;
}


void show() {

    std::cout << "[0] Encoding" << std::endl;
    std::cout << "[1] Decoding" << std::endl;
    std::cout << "[2] Quit" << std::endl;
}



int main() {

    string address_1;
    string address_2;

    //获取字符的频率
    std::cout << "请输入字符集统计地址文件地址" << std::endl;
    getline(std::cin,address_1);
    vector<int>* freq = statistics(address_1);

    //生存Huffman树
    HuffForest* forest = initForest(freq);
    HuffTree* tree = generateTree(forest);
    HuffTable* table = generateTable(tree);

    int choose;
    string skt;
    bool ok = true;
    while(ok) {

        //system("cls");
        show();
        std::cin >> choose;
        switch (choose) {
            case 0:{
                string temp;
                std::cout << "请输入要编码的字符串" << std::endl;
                //getline(std::cin,temp);
                std::cin >> temp;
                skt = encode(table,temp);
                std::cout << "请输入要存储编码结果的文件地址" << std::endl;
                //getline(std::cin,address_2);
                std::cin >> address_2;
                ofstream outfile(address_2,std::ios::app);//若失败,则输出错误消息,并终止程序运行
                assert(outfile.is_open());
                outfile << skt;
            }break;
            case 1:{

                int c;
                std::cout << "[0]控制台输入" << std::endl;
                std::cout << "[1]文件输入" << std::endl;
                std::cin >> c;
                switch (c) {

                    case 0: {
                        string temp;
                        //getline(std::cin,temp);
                        std::cin >> temp;
                        decode(tree, temp);
                    }break;
                    case 1: {
                        std::cout << "请输入要解码文件的地址" << std::endl;
                        //getline(std::cin,address_2);
                        std::cin >> address_2;
                        ifstream infile(address_2);//若失败,则输出错误消息,并终止程序运行
                        assert(infile.is_open());
                        string temp;
                        //getline(infile,temp);
                        infile >> temp;
                        decode(tree,temp);
                        std::cout << std::endl << std::endl;
                    }break;
                }
            }break;
            case 2:ok = false;break;
        }
    }
    return 0;
}
