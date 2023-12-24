#include <iostream>
#include <vector>
#include <string>
using namespace std;

void insertSort(vector<int> nums) {
    for(int i = 1; i < nums.size(); i++) {
        int cur = i;
        int pre = cur - 1;
        while(cur > 0) {
            if(nums[cur] < nums[pre]) {
                // 交换位置
                int temp = nums[pre];
                nums[pre] = nums[cur];
                nums[cur] = temp;
                // 更新指针位置
                cur = pre;
                pre = cur - 1;
            } else {
                break;
            }
        }
    }
}