#include <iostream>
#include <vector>
using namespace std;

vector<int> findPath(const vector<vector<int>>& g, int begin) {
    vector<int> minDist(g.size(), INT_MAX);
    vector<bool> inS(g.size(), false);
    vector<int> parent(g.size(), -1);
    minDist[begin] = 0;
    int count = 0;
    for(int i = 0; i < g.size(); i++) {
        // 找出当前距离最短的节点
        int tempMinDist = INT_MAX;
        int tempNode = -1;
        for(int j = 0; j < g.size(); j++) {
            if(inS[j]) continue;
            if(minDist[j] < tempMinDist) {
                tempMinDist = minDist[j];
                tempNode = j;
            }
        }
        if(tempNode == -1) break;
        // 将tempNode加入集合S中并更新其余未在S中的节点到S的距离
        inS[tempNode] = true;
        for(int k = 0; k < g.size(); k++) {
            if(inS[k]) continue;
            if(g[tempNode][k]+minDist[tempNode] < minDist[k]) {
               minDist[k] = g[tempNode][k]+minDist[tempNode];
               parent[k] = tempNode;
            }
        } 
    }
    return minDist;
}

// 找出从某点到另一点的最短路径
int Find(const vector<vector<int>>& g, int start, int end) {
    int n = g.size();
    vector<int> minDist(n, INT_MAX);
    vector<bool> inS(n, false);
    vector<int> parent(n, -1);
    minDist[start] = 0;
    for(int i = 0; i < n; i++) {
        int tempMinDist = INT_MAX;
        int tempNode = -1;
        for(int j = 0; j < n ; j++) {
            if(inS[j]) continue;
            if(tempMinDist > minDist[j]) {
                tempMinDist = minDist[j];
                tempNode = j;
            }
        }
        if(tempNode == -1) break;
        inS[tempNode] = true;
        for(int k = 0; k < n; k++) {
            if(inS[k]) continue;
            if(g[tempNode][k]!=0&& g[tempNode][k] + minDist[tempNode] < minDist[k]) {
                minDist[k] = g[tempNode][k] + minDist[tempNode];
                parent[k] = tempNode;
            }
        }
    }
    return minDist[end];
}

vector<int> Prim(const vector<vector<int>>& g, int start) {
    int n = g.size();
    vector<int> minDist(n, INT_MAX);
    vector<bool> inS(n, false);
    vector<int> parent(n, -1);
    minDist[start] = 0;
    for(int i = 0; i < n; i++) {
        int tempNode = -1;
        int tempDist = INT_MIN;
        for(int j = 0; j < n; j++) {
            if(inS[j]) continue;
            if(minDist[j] < tempDist) {
                tempDist = minDist[j];
                tempNode = j;
            }
        }
        if(tempNode == -1) {
            cout << "No suitable answer."<< endl;
            break;
        }
        inS[tempNode] = true;
        for(int k = 0; k < n; k++) {
            if(inS[k]) continue;
            if(g[tempNode][k]!=0 && minDist[k] > g[tempNode][k]) {
                parent[k] = tempNode;
                minDist[k] = g[tempNode][k];
            }
        }
    }
    return parent;
}

int printAns(const vector<vector<int>>& g, vector<int> parent) {
    int ans = 0;
    for(int i = 0; i < g.size(); i++) {
        if(parent[i] == -1) continue;
        ans += g[parent[i]][i];
    }    
    return ans;
}

int main() {
    vector<vector<int>> g = {
        {0, 1, 4, 0, 0},
        {0, 0, 2, 5, 0},
        {0, 0, 0, 0, 4},
        {0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0}
    };
    cout << printAns(g, Prim(g, 0));
}