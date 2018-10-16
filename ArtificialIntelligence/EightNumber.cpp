#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
int getInversions(vector<int> num);
bool isEqual(vector<int> start, vector<int> end);
bool hasSolution(vector<int> start, vector<int> end);
void printMatrix(vector<int> num);
int zeroLocation(vector<int> num);
vector<int> moveUp(vector<int> num);
vector<int> moveDown(vector<int> num);
vector<int> moveRight(vector<int> num);
vector<int> moveLeft(vector<int> num);
bool isInClose(vector<int> num);
void BFS(vector<int> start, vector<int> end);
*/

queue<vector<int>> open;
vector<vector<int>> close,state;

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

bool isInClose(vector<int> num)
{
    auto iter = find(close.begin(), close.end(), num);
    if (iter != close.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BFS(vector<int> start, vector<int> end)
{
    int steps = 0;
    vector<int> now, nowMoveUp, nowMoveDown, nowMoveRight, nowMoveLeft;
    open.push(start);
    while (!open.empty())
    { 
        now = open.front();
        open.pop();
        state.push_back(now);
        int zeroPosition = zeroLocation(now);
        if (!isEqual(now, end))// && iter == close.end())
        {
            if (!isInClose(now))
            {
                if (zeroPosition % 3 != 0)
                {
                    nowMoveLeft = moveLeft(now);
                    if (!isInClose(nowMoveLeft))
                    {
                        open.push(nowMoveLeft);
                        steps++;
                    }
                    
                }
                if (zeroPosition > 2)
                {
                    nowMoveUp = moveUp(now);
                    if (!isInClose(nowMoveUp))
                    {
                        open.push(nowMoveUp);
                        steps++;
                    }
                }
                if (zeroPosition % 3 != 2)
                {
                    nowMoveRight = moveRight(now);
                    if (!isInClose(nowMoveRight))
                    {
                        open.push(nowMoveRight);
                        steps++;
                    }
                }
                if (zeroPosition < 6)
                {
                    nowMoveDown = moveDown(now);
                    if (!isInClose(nowMoveDown))
                    {
                        open.push(nowMoveDown);
                        steps++;
                    }
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

