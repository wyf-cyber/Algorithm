#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct ENode {
    int end;
    int weight;
    ENode* next;
    bool visited;
    ENode():end(0),weight(0),next(nullptr),visited(false) {}
};

struct HNode {
    ENode* next;
};

void dfs(vector<HNode*>& g, int begin) {
    ENode* cur = g[begin]->next;
    while(cur) {
        if(!cur->visited) {
            // 将两个边节点的visited=true
            cur->visited = true;
            ENode* p = g[cur->end]->next;
            while(p) {
                if(p->end == begin) p->visited = true;
            } 
            // 继续深搜
            dfs(g, cur->end);
        } 
        cur = cur->next;
    }
}
void bfs(vector<HNode*>& g, int begin) {
    queue<int> q;
    q.push(begin);
    vector<bool> visit(g.size(), false);
    while(!q.empty()) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            int node = q.front();
            q.pop();
            if(visit[node]) continue;
            visit[node] = true;
            cout << node << " ";
            // 将当前节点的邻接点入队
            ENode* cur = g[node]->next;
            while(cur) {
                if(!visit[cur->end]) q.push(cur->end);
                cur = cur->next;
            }
        }
    }
}

void bfs(const vector<vector<int>>& g) {
    queue<int> q;
    vector<bool> visit(g.size(), false);
    q.push(0);
    while(!q.empty()) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            int node = q.front();
            q.pop();
            if(visit[node]) continue;
            visit[node] = true;
            cout << node << " ";
            // 将node的邻接点加入队列
            for(int j = 0; j < g.size(); j++) {
                if(visit[j]) continue;
                if(g[node][j] != 0) {
                    q.push(j);
                }
            }
        }
    }
}
void BFS(const vector<vector<int>>& g) {
    queue<pair<int, int>> q;   // 存储起始节点和终末节点
    vector<bool> visit(g.size(), false);
    // 从0号节点开始遍历
    visit[0] = true;
    for(int k = 0; k < g.size(); k++) {
        if(g[0][k] != 0) {
            q.push({0, k});
        }
    }
    while(!q.empty()) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            pair<int, int> p = q.front();
            q.pop();
            if(visit[p.second]) continue;
            visit[p.second] = true;
            cout << "("<< p.first<<","<< p.second << ")"<< g[p.first][p.second] << " " << endl;
            for(int j = 0; j < g.size(); j++) {
                if(g[p.second][j] != 0 && visit[j] == false) {
                    q.push({p.second, j});
                }
            }
        } 
    }
}