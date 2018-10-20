#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

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

static int id = 0;

void expandState(state now, int zeroL, int newLocation)
{
    swap(now.num[newLocation], now.num[zeroL]);
    state newState = state(now.num, id++, now.nowId);
    //vector<int>::iterator iter = find(close.begin(), close.end(), now.num);
    if(!close.count(now.num))
    {
        open.push(newState);
        //step++;
    }
}

int BFS(vector<int> start, vector<int> end)
{
    int step = 0;
    //static int id = 0, step = 0;
    vector<int> move = {-1, -3, 1, 3};
    open.push(state(start, id, id++));
    while(!open.empty())
    {
        state now = open.front();
        open.pop();
        path.push_back(now);
        close[now.num] = true;
        if (isEqual(now.num, end))
        {
            return now.nowId;
        }
        int zeroL = zeroLocation(now.num);
        int newLocation = 0;
        if (zeroL % 3 != 0)
        {
            newLocation = zeroL + move[0];
            expandState(now, zeroL, newLocation);
            step++;
        }
        if (zeroL > 2)
        {
            newLocation = zeroL + move[1];
            expandState(now, zeroL, newLocation);
        }
        if (zeroL % 3 != 2)
        {
            newLocation = zeroL + move[2];
            expandState(now, zeroL, newLocation);
        }
        if (zeroL < 6)
        {
            newLocation = zeroL + move[3];
            expandState(now, zeroL, newLocation);
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
    cout << "Input end:" << endl;
    printMatrix(end);
    if (hasSolution(start, end))
    {
        int steps = BFS(start, end);
        for (auto i : path)
        {
            cout << "-------->" << endl;
            printMatrix(i.num);
        }
        cout << "steps:" << steps << endl;
        cout << "Has solution";
    }
    else
    {
        cout << "No solution";
    }
    return 0;
}