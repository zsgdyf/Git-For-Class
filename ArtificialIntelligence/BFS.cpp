#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

bool isEqual(vector<int> start, vector<int> end);

class state
{
  public:
    vector<int> num;
    int nowId, parentId;
    state(vector<int> num, int nowId, int parentId)
    {
        this->num = num;
        this->nowId = nowId;
        this->parentId = parentId;
    }
    bool operator==(const state &now) const
    {
        return isEqual(num, now.num);
    }
};

queue<state> open;
vector<state> path;
map<vector<int>, bool> close;

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
            if (num[j] != 0 && num[i] > num[j])
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
    return (inverStart % 2 == inverEnd % 2);
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

int BFS(vector<int> start, vector<int> end)
{
    int id = 0, step = 0;
    vector<int> move = {-1, -3, 1, 3};
    open.push(state(start, id, id++));
    while (!open.empty())
    {
        state now = open.front();
        open.pop();
        path.push_back(now);
        close[now.num] = true;
        if (isEqual(now.num, end))
        {
            return path.size();
        }
        int zeroL = zeroLocation(now.num);
        int newLocation = 0;
        for (int i = 0; i < 4; i++)
        {
            newLocation = zeroL + move[i];
            if (newLocation > -1 && newLocation < 9 
            && !(newLocation == 2 && zeroL == 3) 
            && !(newLocation == 3 && zeroL == 2) 
            && !(newLocation == 5 && zeroL == 6) 
            && !(newLocation == 6 && zeroL == 5))
            {
                swap(now.num[newLocation], now.num[zeroL]);
                state newState = state(now.num, id++, now.nowId);
                swap(now.num[newLocation], now.num[zeroL]);
                if (!close.count(newState.num))
                {
                    open.push(newState);
                    step++;
                }
            }
        }
    }
}

int main()
{
    vector<int> start(9), end(9);
    clock_t startTime, endTime;
    //start = {2, 8, 3, 1, 0, 4, 7, 6, 5};
    //end = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    cout << "Input start:" << endl;
    for (int i = 0; i < 9; i++)
    {
        cin >> start[i];
    }
    cout << "------------------" << endl;
    printMatrix(start);
    cout << "------------------" << endl;
    cout << "Input end:" << endl;
    for (int i = 0; i < 9; i++)
    {
        cin >> end[i];
    }
    cout << "------------------" << endl;
    printMatrix(end);
    cout << "------------------" << endl;
    startTime = clock();
    if (hasSolution(start, end))
    {
        int steps = BFS(start, end);
        for (int i = 1; i < path.size(); i++)
        {
            cout << "step[" << i << "]-->" << endl;
            printMatrix(path[i].num);
        }
        cout << "steps:" << steps - 1 << endl;
        cout << "Has solution" << endl;
    }
    else
    {
        cout << "No solution" << endl;
    }
    endTime = clock();
    cout << "Total Time:" << endTime - startTime << "ms" << endl;
    return 0;
}