#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::vector;

struct Record
{
    Record(const string & word,int frequency)
    : _word(word)
    , _frequency(frequency)
    {}

	string _word;
	int _frequency;
};

bool operator<(const Record & lhs,const Record & rhs){
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
    Dictionary(int capacity)
    {
        _dict.reserve(capacity);
    }

    void read(const string &filename){
        ifstream ifs(filename);
        
        if(!ifs){
            cerr << "ifs open file failed!" << endl;
            return;
        }

        //因为磁盘文件读写速度慢，应该尽量减少文件IO的次数
        /* string word; */
        /* while(ifs >> word){ */
        /* } */

        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                //处理单词
                string newWord = dealWord(word);

                //将单词插入到vector
                insert(newWord);
            }
        }

        //对vector中的元素进行排序
        sort(_dict.begin(),_dict.end());

        ifs.close();
    }

    string dealWord(const string & word){
        for(size_t idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();//如果有非法字符就返回空字符串
            }
        }
        return word;
    }

    void insert(const string & word){
        if(word == string())
        {
            return;
        }

        //判断这个单词是否已经在vector中了
        size_t idx = 0;
        for(; idx != _dict.size(); ++idx){
            if(word == _dict[idx]._word){
                ++_dict[idx]._frequency;
                break;
            }
        }

        if(idx == _dict.size()){
            _dict.push_back(Record(word,1));
        }
    }

    void store(const string &filename){
        ofstream ofs(filename);
        
        if(!ofs){
            cerr << "ofs open file failed!" << endl;
            return;
        }

        for(size_t idx = 0; idx != _dict.size(); ++idx){
            ofs << _dict[idx]._word << " "
                << _dict[idx]._frequency <<endl;
        }
        ofs.close();
    }
private:
    vector<Record> _dict;
};

void test0(){
    Dictionary dict(10000);
    dict.read("The_Holy_Bible.txt");
    dict.store("dictionary.dat");
}

int main()
{
    test0();
    return 0;
}


