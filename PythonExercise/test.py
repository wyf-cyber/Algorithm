def gcd(m, n)->int:
    while m != n:
        if m > n:
            m = m - n
        else:
            n = n - m
    return m

# 求解多个数的最大公因数
def multi_gcd(nums:list[int])->int:
    n = len(nums)
    if n == 1:
        return nums[0]
    elif n == 2:
        return gcd(nums[0], nums[1])
    else:
        return gcd(multi_gcd(nums[:n//2]), multi_gcd(nums[n//2:]))

n = int(input())
nums = [int(i) for i in input().split()]
nums = sorted(nums)
# 求出新等差数列首尾项之间的差
dist = nums[n-1] - nums[0]
# 求出新等差数列的最大公差（给定元素的差的最大公因数）
# 给定数字序列的最小差不一定就是等差数列的差，因为不同项在原等差数列中不一定有相等或成倍数的间距
l = [nums[i] - nums[i-1] for i in range(1, n)]
d = multi_gcd(l)
print(d)
print(dist//d + 1)