#include <iostream>
#include <vector>
using namespace std;

int getInversions(vector<int> num)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (num[i] == 0)
        {
            continue;
        }
        for (int j = i; j < 9; j++)
        {
            if (num[i] > num[j])
            {
                count++;
            }
        }
    }
    return count;
}

bool isEqual(vector<int> start, vector<int> end)
{
    for (int i = 0; i < 9; i++)
    {
        if (start[i] != end[i])
        {
            return false;
        }
    }
    return true;
}

bool hasSolution(vector<int> start, vector<int> end)
{
    int inverStart, inverEnd;
    inverStart = getInversions(start);
    inverEnd = getInversions(end);
    return inverStart % 2 == inverEnd % 2;
}

void printMatrix(vector<int> num)
{
    for (int i = 0; i < 7; i += 3)
    {
        for (int j = i; j < i + 3; j++)
        {
            cout << num[j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> start, end;
    start = {1, 3, 2, 4, 0, 5, 6, 7, 8};
    end = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    cout << "Input start:" << endl;
    printMatrix(start);
    /*
    for (int i = 0; i < 9; i++)
    {
        int num;
        cin >> num;
        start.push_back(num);
    }
    */
    cout << "Input end:" << endl;
    printMatrix(end);
    /*
    for (int i = 0; i < 9; i++)
    {
        int num;
        cin >> num;
        end.push_back(num);
    }
    */
    if (hasSolution(start, end))
    {
        cout << "Has solution";
    }
    else
    {
        cout << "No solution";
    }
    return 0;
}