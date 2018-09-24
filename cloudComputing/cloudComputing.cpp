#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>
#include <cctype>
using namespace std;
string toLower(string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
    }
    return word;
}
string delePunct(string word)
{
    string outword;
    for (int i = 0; i < word.size(); i++)
    {
        if (!ispunct(word[i]))
        {
            outword = outword + word[i];
        }
    }
    return outword;
}
bool compare(const pair<string, size_t> &x, const pair<string, size_t> &y)
{
    return x.second > y.second;
}
void sortByValue(map<string, size_t> &wordMap, vector<pair<string, size_t>> &wordVector)
{
    for (auto &iter : wordMap)
    {
        wordVector.push_back(make_pair(iter.first, iter.second));
    }
    sort(wordVector.begin(), wordVector.end(), compare);
    for (auto iter = wordVector.begin(); iter < (wordVector.begin() + 3); iter++)
    {
        cout << left << setw(20) << iter->first << "\t" << iter->second
             << ((iter->second > 1) ? " times" : " time") << endl;
    }
}
void wordCount(string word)
{
    map<string, size_t> wordCount;
    vector<pair<string, size_t>> wordVector;
    ifstream inFile;
    inFile.open("data.dat");
    while (!inFile.eof())
    {
        inFile >> word;
        word = delePunct(word);
        word = toLower(word);
        wordCount[word]++;
    }
    
    for (auto &w : wordCount)
    {
        cout << left << setw(20) << w.first << "\t" << w.second 
        << ((w.second > 1)? " times" : " time") << endl;
    }
    
    cout << "-----------------------------------"
         << "Sort by value:" << endl;
    sortByValue(wordCount, wordVector);
}
int main()
{
    clock_t startTime, endTime;
    startTime = clock();
    string word;
    wordCount(word);
    endTime = clock();
    cout << "Program Running Time:" << endTime - startTime << " ms" << endl;
    return 0;
}