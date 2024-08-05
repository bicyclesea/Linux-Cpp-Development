#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;

/* 读取一个文件的全部内容 */
/* 还可以在创建输入流对象时指定ate模式，省去第一步将游标置流末尾处的操作 */
void test0(){
    string filename = "6.cc";
    ifstream ifs(filename);

    if(!ifs){
        cerr << "ifs open file fail!";
        return;
    }
    
    //读取一个文件的所有内容先要获取文件的大小
    //将游标放到了文件的最后（尾后）
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取尾后下标，实际就是总的字符数
    cout << length << endl;

    char * pdata = new char[length]();
    //需要将游标再放置到文件开头
    ifs.seekg(0,std::ios::beg);
    ifs.read(pdata,length);

    //content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    cout << "content:" << content << endl;
    /* cout << pdata << endl; */
    ifs.close();
}

/* 最终版本 */
void test1()
{
    //文件游标置于末尾
    ifstream ifs("6.cc", std::ios::ate);

    if(!ifs.good()){
        cerr << "ifstream open file failed!" << endl;
        return;
    }

    //为了获取字符数
    long length = ifs.tellg();
    cout << "length:" << length << endl;

    char *pdata = new char[length + 1]();

    //文件游标再移到开始位置
    //从文件游标的位置往后读
    ifs.seekg(0);
    ifs.read(pdata, length);

    cout << pdata << endl;
}

int main()
{
    test1();
    return 0;
}

