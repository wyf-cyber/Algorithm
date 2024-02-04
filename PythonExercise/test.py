def multi(a,b):
    # 将结果存入矩阵 c 并返回
    c = []
    rowA = len(a)
    colA = len(a[0])
    rowB = len(b)
    colB = len(b[0])
    # colA = rowB
    # colC = colB
    # rowC = rowA
    for i in range(rowA):
        line = []
        for j in range(colB):
            # 计算c[i][j]
            temp = 0
            for m in range(colA):
                temp += a[i][m] * b[m][j]
            line.append(temp)
        c.append(line)
    return c

def powM(a,n):
    if n == 0:
        l = len(a)
        for p in range(l):
            for q in range(l):
                if p == q:
                    print('1', end = ' ')
                else :
                    print('0', end = ' ')
            print()
    ans = a
    for i in range(n-1):
        ans = multi(ans, a)
    return ans
def printM(a):
    for i in a:
        for j in i:
            print(j, end = ' ')
        print()

# 接收输入
n,m = map(int,input().split())
b = []
for i in range(n):
    b.append([int(i) for i in input().split()])

printM(powM(b,m))