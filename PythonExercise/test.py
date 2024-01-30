# 除了自上而下的计算，还可以自下而上地求出dp列表的值
# 在自下而上的过程中，三角形每一层都只有一种节点，更为简单
def f()->int:
    n = int(input())
    tri = []
    for i in range(n):
        tri.append([int(j) for j in input().split()])
    # 算法主体
    # 创建dp列表
    dp = tri[:]
    for row in range(n-2, -1, -1):
        for col in range(row + 1):
            dp[row][col] = min(dp[row+1][col], dp[row+1][col+1]) + tri[row][col]
    return dp[0][0]

print(f())