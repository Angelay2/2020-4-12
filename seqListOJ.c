#include <stdio.h>
#include <stdlib.h>

typedef struct seqList{
	int* _data;// 动态开辟
	size_t _size;// 大小
	size_t _capacity;// 容量
}seqList;

/*
1. 移除元素
 给你一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，
 并返回移除后数组的新长度。不要使用额外的数组空间 使用O(1)的额外空间并原地修改数组
 (1)最简单的做法 ---> 再新开一个根原始数组一样大的数组 然后把要删除的元素不动 把其他元素拷入新数组, 可是其空间复杂度为O(N) 舍弃
 (2) 采用删除数据的方法, 遇到第一个val后, 找下一个不是val的值 然后覆盖val的位置
 给定i: 当前遍历的位置 
 idx: 被保留下来的最后一个数据的位置(遇到的第一个val的位置)

*/
int removeElement(int* nums, int numSize, int val){
	int i = 0;
	int idx = 0;
	while (i++ < numSize){
		if (nums[i] != val){
			nums[idx] = nums[i];
			idx++;
		}
	}

//	for(i = 0; i < numSize; i++){
//		// 如果没找到与val相等的数据,将i位置的元素放在idx处, idx向后移动,
//		if (nums[i] != val){
//			nums[idx] = nums[i];
//			// 在遇到与val相等的数据前, idx总比i快一步 直到遇到val后 idx开始跟着i走
//			++idx;
//		}
//		// 如果找到与val相等的数据, idx不变 i继续向后移动
//	}
	return idx;
}
int main(){
	int nums[] = { 3, 2, 4, 6, 1, 5, 6 };
	int numSize = sizeof(nums) / sizeof(nums[0]);
	int val = 6;
	printf("长度 = %d", removeElement(nums, numSize, val));
	system("pause");
	return 0;
}