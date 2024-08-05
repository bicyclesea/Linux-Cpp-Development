#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {2, 3, 4, 5};
    vector<vector<int>> vec;
    vec.push_back(vec1);
    vec.push_back(vec2);
    for(size_t i = 0; i < vec.size(); ++i){
        for(size_t j = 0; j < vec[i].size(); ++j){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

