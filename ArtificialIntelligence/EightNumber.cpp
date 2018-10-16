#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

int zeroLocation(vector<int> num)
{
    for (int i = 0; i < 9; i++)
    {
        if (num[i] == 0)
        {
            return i;
        }
    }
}

vector<int> moveUp(vector<int> num)
{
    int i = zeroLocation(num);
    num[i] = num[i - 3];
    num[i - 3] = 0;
    return num;    
}

vector<int> moveDown(vector<int> num)
{
    int i = zeroLocation(num);
    num[i] = num[i + 3];
    num[i + 3] = 0;
    return num;    
}

vector<int> moveLeft(vector<int> num)
{
    int i = zeroLocation(num);
    num[i] = num[i - 1];
    num[i - 1] = 0;
    return num;    
}

vector<int> moveRight(vector<int> num)
{
    int i = zeroLocation(num);
    num[i] = num[i + 1];
    num[i + 1] = 0;
    return num;    
}

void BFS(vector<int> start, vector<int> end)
{
    int steps = 0;
    queue<vector<int>> open;
    vector<vector<int>> close,state;
    vector<int> now, nowMoveUp, nowMoveDown, nowMoveRight, nowMoveLeft;
    open.push(start);
    while (!open.empty())
    { 
        now = open.front();
        open.pop();
        state.push_back(now);
        int zeroPosition = zeroLocation(now);
        auto iter = find(close.begin(), close.end(), now);
        if (!isEqual(now, end))// && iter == close.end())
        {
            if (iter == close.end())
            {
                if (zeroPosition % 3 != 0)
            {
                nowMoveLeft = moveLeft(now);
                steps++;
                open.push(nowMoveLeft);
            }
                if (zeroPosition > 3)
            {
                nowMoveUp = moveUp(now);
                steps++;
                open.push(nowMoveUp);
            }
            if (zeroPosition % 3 != 2)
            {
                nowMoveRight = moveRight(now);
                steps++;
                open.push(nowMoveRight);
            }
            if (zeroPosition < 5)
            {
                nowMoveDown = moveDown(now);
                steps++;
                open.push(nowMoveDown);
            }
            close.push_back(now);
            }
            else
            {
                continue;
            }
        }
        else
        {
            cout << "steps:" << steps << endl;
            for (vector<int> s:state)
            {
                cout << "---------" << endl;
                printMatrix(s);
                cout << "---------" << endl;
            }
            break;
        }
    }

}

int main()
{
    vector<int> start, end;
    start = {2, 8, 3, 1, 0, 4, 7, 6, 5};
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
        BFS(start, end);
        cout << "Has solution";
    }
    else
    {
        cout << "No solution";
    }
    return 0;
}