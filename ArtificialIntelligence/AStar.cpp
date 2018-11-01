#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

bool isEqual(vector<int> start, vector<int> end);

class state
{
    public:
    vector<int> num;
    int fX, gX, hX;
    int nowId, parentId;
    state(vector<int> num, int fX, int gX, int hX, int nowId, int parentId)
    {
        this->num = num;
        this->fX = fX;
        this->gX = gX;
        this->hX = hX;
        this->nowId = nowId;
        this->parentId = parentId;
    }
    /*
    bool operator<(const state &now) const
    {
        return fX < now.fX;
    }
    */
    bool operator==(const state &now) const
    {
        return isEqual(num, now.num);
    }
};

vector<state> open;
vector<state> path;
map<vector<int>, bool> close;


int HX(vector<int> start, vector<int> end)
{
    int hX = 0;
    for (int i = 0; i < 9; i++)
    {
        if (start[i] != end[i])
        {
            hX++;
        }
    }
    return hX;
}

int FX(state &now)
{
    return now.hX + now.gX;
}

bool isEqual(vector<int> start, vector<int> end)
{
    /*
    for (int i = 0; i < 9; i++)
    {
        if (start[i] != end[i])
        {
            return false;
        }
    }
    return true;
    */
    return HX(start, end) == 0;
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


int AStar(vector<int> start, vector<int> end)
{
    int id = 0;
    vector<int> move = {-3, -1, 3, 1};
    open.push_back(state(start, HX(start, end), 0, HX(start, end), id, id++));
    while (!open.empty())
    {
        auto min = min_element(open.begin(), open.end(), [](const state &x, const state &y)-> bool 
        {
            return x.fX < y.fX;
        });
        state now = *min;
        open.erase(min);
        //sort(open.begin(), open.end());
        //state now = *open.begin();
        //open.erase(open.begin());
        path.push_back(now);
        close[now.num] = true;
        if (isEqual(now.num, end))
        {
            return now.gX;
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
                state newState = state(now.num, 0, now.gX + 1, HX(now.num, end), id++, now.nowId);
                swap(now.num[newLocation], now.num[zeroL]);
                newState.fX = FX(newState);
                if (isEqual(newState.num, end))
                {
                    path.push_back(newState);
                    return newState.gX;
                }
                if (!close.count(newState.num))
                {
                    vector<state>::iterator iter = find(open.begin(), open.end(), newState);
                    if (iter != open.end())
                    {
                        if (iter->fX > newState.fX)
                        {
                            open.erase(iter);
                            open.push_back(newState);
                        }
                    }
                    else
                    {
                        open.push_back(newState);
                    }
                }
            }
        }
    }

}

void printPath(int parentId, int stateSize, int steps)
{
    if (steps == 0)
    {
        cout << "step[" << steps << "] -->" << endl;
        printMatrix(path[stateSize].num);
        return;
    }
    for (int i = stateSize; i > 0; --i)
    {
        if (path[i].nowId == parentId)
        {
            printPath(path[i].parentId, i, steps - 1);
        }
    }
    cout << "step[" << steps << "] -->" << endl;
    printMatrix(path[stateSize].num);
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
        int steps = AStar(start, end);
        printPath((path.end() - 1)->parentId, path.size() - 1, steps);
        cout << "steps:" << steps << endl;
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