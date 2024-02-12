import os
import sys
from queue import Queue

switchOne = [(1,0),(0,1),(-1,0),(0,-1)]
switchTwo = [(1,0),(0,1),(-1,0),(0,-1),(1,1),(1,-1),(-1,1),(-1,-1)]

def getData():
    m,n = map(int,input().split())
    d = [[0]*(n+2)]
    for i in range(m):
        line = [0] + [int(i) for i in input()] + [0]
        d.append(line)
    d.append([0]*(n+2))
    return d
# using BFS to add tag to the island
def bfs(i,j,d,visited,size):
    # search all the island
    q = Queue(maxsize = size)
    q.put([i,j])
    while not q.empty():
        # visit node
        node = q.get()
        if visited[node[0]][node[1]]:
            continue
        visited[node[0]][node[1]] = 1
        # add its neighber to the queue
        for k in switchOne:
            temp = [node[0]+k[0], node[1]+k[1]]
            if d[temp[0]][temp[1]] == 1 and visited[temp[0]][temp[1]] == 0:
                q.put(temp)
    return visited
def counter(b):
    # 创建visited数组记录是否遍历过
    m = len(b)
    n = len(b[0])
    size = m*n
    visited = [[0]*n for _ in range(m)]
    ans = 0
    q1 = Queue(maxsize = size)
    q1.put([0,0])
    while not q1.empty():
        cur = q1.get()
        if visited[cur[0]][cur[1]]:
            continue
        # analysis the current node
        if b[cur[0]][cur[1]]:
            bfs(cur[0],cur[1],b,visited,size)
            ans += 1
        else:
            visited[cur[0]][cur[1]] = 1
            for i in switchTwo:
                newI = cur[0]+i[0]
                newJ = cur[1]+i[1]
                if newI > -1 and newI < m and newJ > -1 and newJ < n:
                # valid site
                    if not visited[newI][newJ]:
                        q1.put([newI,newJ])
    return visited

board = getData()
# print(board)
visited = counter(board)
for i in visited:
    print(i) 