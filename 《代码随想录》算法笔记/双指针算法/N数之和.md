# 一、题目特征
给定一个整数数组 nums 和一个整数目标值 target，需要在该数组中找出并返回满足全部条件且**不重复**的N元组（或下标）。特别地，对于N的不同取值，N元组需要满足的附加条件也不完全相同。

# 二、思路
## 1.滑动窗口
对于要求返回N元组的题，设置四个指针使用for循环暴力求解的时间复杂度为 $O(n^n)$。由于题目不要求返回下标，因此我们可以使用sort()库函数将数组修改为有序数组，再结合滑动窗口法可以将右侧两个指针的遍历操作的时间复杂度由 $O(n^2)$ 降低到 $O(n)$，获得更快的效率。
## 2.去重操作
由于原数组中可能存在**具有相同值**的元素，这类题还需要考虑如何实现去重操作，保证结果中的数组互不相同。由于比较并删除相同数组比较困难，最好的办法是在遍历的过程中跳过具有相同值的元素，此处注意对于**for循环的变量**跳过的条件一定是**本次**的操作数与**上一次**的相同(nums[i] = nums[i-1])而不是和下一次进行比较然后跳过本轮遍历。因为for循环变量的取值范围：**上轮操作 > 本轮操作 > 下一轮操作**，如果和下一次进行比较然后跳过本轮遍历，相当于舍弃大范围搜找小范围，很有可能会忽略[-1,-1,2]之类的情况。而如果与上一次的进行比较后跳过，相当于搜索完大范围以后跳过小范围，这个小范围一定是大范围的子集，所以可以跳过。

## 3.剪枝操作
在左侧指针用for循环遍历的过程中，如果发现第一个元素（也就是n个元素中最小的元素）的值已经大于target且不小于0，则说明在本轮循环中不可能有合适的解。注意该元素必须是非负数，因为多个负数相加可以产生更小的数，不满足上述规则。

# 三、相关题目
## 1.两数之和
**题目链接：**[1.两数之和（LeetCode）](https://leetcode.cn/problems/two-sum/description/)
**题目描述：**
>给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
你可以按任意顺序返回答案。

示例：
>输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

提示：
>2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案

**解题思路：**
- 因为函数要返回下标，所以不能对数组排序（否则将修改下标）， 因为原数组不一定是有序数组，所以不能用双指针法。
- 因为下标不重复，提示中说明结果只有一个，所以不用考虑去重
- 直接使用两重for循环遍历数组

**代码示例：**
~~~cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        for(int i = 0; i < nums.size()-1; ++i) {
            for(int j = i+1; j < nums.size(); ++j) {
                if(nums[i]+nums[j] == target) {
                    ans.push_back(i);
                    ans.push_back(j);
                }
            }
        }
        return ans;
    }
};
~~~
**时空复杂度：**

- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(1)$

## 2.三数之和
**题目链接：**[15.三数之和（LeetCode）](https://leetcode.cn/problems/3sum/description/)
**题目描述：**
>给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。

示例1：
>输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。

示例2：
>输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。

提示：
>3 <= nums.length <= 3000
-105 <= nums[i] <= 105

**解题思路：**

- 因为要返回三元组，组中元素位置无影响，所以可以用sort()排序，确保数组是有序数组
- 对有序数组可以使用滑动窗口法，右侧两个指针构成滑动窗口，左侧指针使用for循环遍历数组
- 注意对左侧指针的去重操作是和上一轮的操作数比较
- 窗口指针的去重操作的位置在记录符合条件的数组之后

**代码示例：**
~~~cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        // 如果数组长度小于3，必定不满足条件
        if(nums.size() < 3) return ans;
        // 排序
        sort(nums.begin(), nums.end());
        // m,n构成滑动窗口，i遍历数组
        for(int i = 0; i < nums.size(); ++i) {
            if(nums[i] > 0) return ans;
            // 对i的去重操作
            if(i > 0 && nums[i] == nums[i-1]) {
                // 可能成立的数值（如[-1, -1, 2]）在上一次（大范围）已经取过，本次必须跳过
                continue;
            }
            int m = i + 1;
            int n = nums.size() - 1;
            while(m < n) {
                int temp = nums[i] + nums[m] + nums[n];
                if(temp > 0) {
                    n--;
                }else if(temp < 0) {
                    m++;
                }else {
                    ans.push_back(vector<int>{nums[i], nums[m], nums[n]});
                    // 去重操作
                    // 注意滑动窗口指针的去重方法与for循环遍历指针的不完全相同
                    // 
                    while(m < n && nums[m] ==nums[m+1]) m++;
                    while(m < n && nums[n] == nums[n-1]) n--;
                    // 找到合适解，两指针同时收缩
                    m++;
                    n--;
                }
            }
        }
        return ans;
    }
};
~~~
**时空复杂度：**

- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(1)$

## 3.四数之和
**题目链接：**[18.四数之和（LeetCode）](https://leetcode.cn/problems/4sum/)
**题目描述：**
>给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按任意顺序返回答案。

示例：
>输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

提示：
>1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

**解题思路：**

- 因为要返回四元组，组中元素位置无影响，所以可以用sort()排序，确保数组是有序数组
- 对有序数组可以使用滑动窗口法，右侧两个指针构成滑动窗口，左侧指针使用两重for循环遍历数组
- 解题思想和三数之和基本相同

**代码示例：**
~~~cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        if(nums.size() < 4) return ans;
        sort(nums.begin(), nums.end());
        // 嵌套两层for循环
        for(int i = 0; i < nums.size()-3; ++i) {
            // 剪枝操作
            // 需要判断其与0的关系，因为多个负数相加将使结果更小，即使满足nums[i]>target仍有可能满足题意
            if(nums[i] > target && nums[i] >= 0) 
                break;
            // 去重操作
            if(i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            // 设置第二重for循环
            for(int j = i + 1; j < nums.size()-2; j++) {
                // 剪枝操作
                // 注意此处不可使用return ans;
                if((nums[i]+nums[j]) > target && (nums[i]+nums[j]) >= 0)
                    break;
                // 去重操作
                if(j > (i + 1) && nums[j] == nums[j-1]) {
                    continue;
                }
                // 设置滑动窗口的两个指针
                int m = j + 1;
                int n = nums.size() - 1;
                while(m < n) {
                    // 不能直接相加,否则有溢出风险
                    if((long)nums[i]+nums[j]+nums[m]+nums[n] > target) {
                        n--;
                    }else if((long)nums[i]+nums[j]+nums[m]+nums[n] < target) {
                        m++;
                    }else {
                        ans.push_back(vector<int>{nums[i], nums[j], nums[m], nums[n]});
                        // 对m,n的去重操作
                        while(m < n && nums[m] == nums[m+1]) m++;
                        while(m < n && nums[n] == nums[n-1]) n--;
                        // 同时更新指针
                        m++;
                        n--;
                    }
                }
            }
        }
        return ans;
    }
};
~~~

**时空复杂度：**

- 时间复杂度：$O(n^3)$
- 空间复杂度：$O(1)$
