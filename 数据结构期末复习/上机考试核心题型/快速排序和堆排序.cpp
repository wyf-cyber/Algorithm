#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
QuickSort Rules:
1.初始化：默认选取当前区间最左段的点作为base，左指针指向base，右指针指向区间最右侧端点
2.比较两个指针所指节点的值，若左指针指向元素的值大于右指针，则交换两个节点的位置，此时base的状态也将随之转换到另一个指针上
3.比较过程完成后，拥有base状态的指针不动，另一个指针向base指针移动一步，继续进行比较
4.当两个指针指向同一个节点时，本轮排序结束，将除终止节点以外的左右两个区间调用递归函数，继续检查
*/

void quickSort(vector<int>& nums, int left, int right) {
    int begin = left;            // 记录区间的位置
    int end = right;
    bool leftIsBase = true;      // 记录轴点的位置
    while (left < right) {
        // 比较两个节点的大小
        if (nums[left] > nums[right]) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            // 转换base节点位置
            if (leftIsBase) {
                leftIsBase = false;
            }
            else {
                leftIsBase = true;
            }
        }
        // 更新指针位置
        if (leftIsBase) {
            right--;
        }
        else {
            left++;
        }
    }
    // 递归处理左右子序列
    if (begin < left - 1) quickSort(nums, begin, left - 1);
    if (left + 1 < end) quickSort(nums, left + 1, end);
}

/*
heapSort Rules:
1.使用大根堆可以得到升序序列，使用小根堆可以得到降序序列
2.使用完全二叉树存储所要排序的数组（该树用一维数组表示）
3.存储树的一维数组中某一节点nums[i]的左子树在nums[i*2+1]，右子树在nums[i*2+2]
4.编写一个自顶向下筛选的算法函数shiftDown()，该函数将会将指定区间内的数据按照大根堆排列
5.shiftDown()函数首先让指针i指向根节点（当前区间的第一个节点），然后将根节点的值临时存储在变量temp中，随后将指针j指向根节点较大的孩子
6.比较temp与nums[j]，若temp<nums[j]则将nums[j]调整到其双亲位置上，并将i = j,j指向i的最大子节点，以检查调整后的子堆是否满足大根堆
7.终止条件：
（1）temp>nums[j]
（2）j>区间右端
8.初始堆：初始堆具有局部堆序性，即前n/2-1个节点均大于其左右子节点，且根节点值最大
*/

void shiftDown(vector<int>& nums, int begin, int end) {
    // 在区间[begin, end]内排序
    int i = begin;
    int j = 2 * i + 1;
    int temp = nums[i];
    while (j <= end) {
        if (j < end && nums[j] < nums[j + 1]) {
            j = j + 1;
        }
        if (nums[j] > temp) {
            nums[i] = nums[j];
            // 更新指针，检查调整后的子堆是否满足大根堆条件
            i = j;
            j = 2 * i + 1;
        }
        else {
            // 已经是大根堆了
            break;
        }
    }
    // 将最初的根节点的值存入数组
    nums[i] = temp;
}

void heapSort(vector<int>& nums) {
    int n = nums.size();
    // 循环建立初始堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        shiftDown(nums, i, n - 1);
    }
    // 进行n-1趟排序，每一次排序后无序区的元素个数减一
    for (int i = n - 1; i > 0; i--) {
        int temp = nums[i];        // 将大根堆堆顶元素加入有序区，因为堆顶元素是无序区的最大元素
        nums[i] = nums[0];
        nums[0] = temp;
        shiftDown(nums, 0, i - 1);   // 调整无序区[0, i-1]
    }
}

int main() {
    vector<int> nums = { 3,4,5,1,8,4,7,13 };
    vector<int> compare = { 3,4,5,1,8,4,7,13 };
    sort(compare.begin(), compare.end());
    // quickSort(nums, 0, nums.size() - 1);
    heapSort(nums);
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != compare[i]) {
           cout << "ERROR";
        }
        // cout << nums[i] << " ";
        if (i == nums.size() - 1) cout << "Success!";
    }
}