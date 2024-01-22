#include <iostream>
#include <vector>
using namespace std;

bool isOdd(int i) {
    return i%2;
}

// 将奇数放左边，偶数放右边
void divide(vector<int>& nums) {
    int data = nums[0];
    int left = 0;
    int right = nums.size() - 1;
    while(left < right) {
        while(left < right && !isOdd(nums[right])) right--;
        if(left < right) {
            nums[left] = nums[right];
            left++;
        }
        while(left < right && isOdd(nums[left])) left++;
        if(left < right) {
            nums[right] = nums[left];
            right--;
        }
    }
    nums[left] = data;
}

int main() {
    vector<int> nums = {2,3,4,5,6,7,8};
    divide(nums);
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
}