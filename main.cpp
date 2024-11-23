// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
using namespace std;

void computeLPSArray(const std::string& pattern, std::vector<int>& lps) {
    int m = pattern.length();
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i] = ++len;
            ++i;
        }
        else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

int kmpSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    computeLPSArray(pattern, lps);

    int i = 0; // 文本索引
    int j = 0; // 模式索引

    while (i < n) {
        if (pattern[j] == text[i]) {
            ++i;
            ++j;
        }

        if (j == m) {
            return i; // 找到匹配
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else {
                ++i;
            }
        }
    }
    return 0; // 未找到匹配
}

int main()
{
    string text,pattern;
    getline(cin,text);
    getline(cin,pattern);
    int xx=kmpSearch(text,pattern);
    if(xx)
        cout<<xx-pattern.size()+1;
    else
        cout<<"No!";
    return 0;
}