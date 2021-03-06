﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
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
 (2) 采用删除数据的方法, 遇到第一个val后, 找下一个不是val的值 然后用它覆盖val的位置
 给定i: 当前遍历的位置 
 idx: 被保留下来的最后一个数据的位置(遇到的第一个val的位置)

*/
int removeElement(int* nums, int numSize, int val){
	int i = 0;
	int idx = 0;
/*  while (i++ < numSize){
		if (nums[i] != val){
		
			nums[idx] = nums[i];
			idx++;
		}
	}
*/
	for(i = 0; i < numSize; i++){
		// 如果没找到与val相等的数据,将i位置的元素放在idx处, idx向后移动,
		if (nums[i] != val){
			nums[idx] = nums[i];
			// 在遇到与val相等的数据前, idx总比i快一步 直到遇到val后 idx开始跟着i走
			++idx;
		}
		// 如果找到与val相等的数据, idx不变 i继续向后移动
	}
	return idx;
}
int main1(){
	int nums[] = { 3, 2, 4, 6, 1, 5, 6 };
	int numSize = sizeof(nums) / sizeof(nums[0]);
	int val = 6;
	printf("长度 = %d", removeElement(nums, numSize, val));

	system("pause");
	return 0;
}

/*2. 删除排序数组中的重复元素
  给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
  不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
  就是把重复的数字不要全部删除 值保留一个, 
  帕努单当前位置是否和下一个元素相等, 找下一个不重复的元素, 然后把这个不重复的元素 挪到第二个重复 的元素位置, 
  i: 当前遍历的位置(找下一个不重复的位置)
  idx: 位于要被替换的元素位置,第一次位于第二个重复元素的位置 后面就一直+1,
  */

int removeDuplicates(int* nums, int numSize){

	int idx = 0;
	int i = 1;
	if (numSize == 0)
		return 0;
	for (int i = 1; i < numSize; i++){

		if (nums[i] != nums[i - 1])
			nums[++idx] = nums[i];
	}
	return idx + 1;
}
int removeDuplicates2(int* nums, int numSize){
	int idx = 0;
	int i = 0;
	int j = 1;
	while (j < numSize){
		nums[idx++] = nums[i];
		if (nums[i] != nums[j]){
			++i;
			++j;
		}
		else{
			// 找第一个不相同的位置
			while (j < numSize && nums[i] == nums[j])
				++j;
			i = j;
			++j;
		}
	}
	// 此时i位于最后一个元素的位置, 需要将i位置的元素赋给idx
	if (i < numSize)
		nums[idx++] = nums[i];

	return idx;
}
int main2(){
	int nums[] = { 0, 1, 1, 1, 2, 2, 3, 4, 4, 4 };
	int numSize = sizeof(nums) / sizeof(nums[0]);
	printf("长度 = %d\n", removeDuplicates2(nums, numSize));

	system("pause");
	return 0;
}

/*
3. 合并两个有序数组
  给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
  说明:
 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 (1). 申请一个m + n 的数组空间
 (2). 分别遍历第一个和第二个数组元素
	如果: nums[i] < nums2[j] : ret[idx] = nums[i], ++i
	如果: nums[i] >= nums2[j] : ret[idx] = nums2[j], ++j;
	idx++;
 (3). 如果还有某个数组的元素没有遍历完, 剩余元素直接拼接到结果数组ret中

*/

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){

	int total = m + n;
	// 开一个新数组
	int* ret = (int*)malloc(sizeof(int)* total);
	// 同时遍历两个数组
	int n1 = 0;
	int n2 = 0;
	int idx = 0;
	while (n1 < m && n2 < n){
		// 选小的数据存放到新数组
		if (nums1[n1] <= nums2[n2]){
			ret[idx++] = nums1[n1++];
		}
		else{
			ret[idx++] = nums2[n2++];
		}
	}
	//  有可能还有未合并的数据
	if (n1 < m){
		memcpy(ret + idx, nums1 + n1, sizeof(int)* (m - n1));
	}
	if (n2 < n){
		memcpy(ret + idx, nums2 + n2, sizeof(int)* (n - n2));
	}
	// 把ret的数据再放大nums1中,
	memcpy(nums1, ret, sizeof(int) * total);

}
//(2) 从后向前先合并大元素
// 先确定合并后的最后一个元素的位置, pos = m + n -1, 
// 两个索引 i, j, 分别指向nums1[m], nums2[n], 遍历第一个和第二个数组, 
// nums[j] 和nums[i]比较, 分别从后向前选最大, 放入pos,
//		如果nums1[i] >= nums2[j], nums1[pos--] == nums1[i--];
//		如果nums1[i] < nums2[j], nums1[pos--] == nums2[j--];
// 判断 如果第二个数组没有遍历完(若第一个数组未遍历完 不用担心, 最中是合并到nums1的), 把第二个数组剩余元素存入第一个数组首位,
// 时间复杂度为O(N), 空间为O(1).
void merge2(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int pos = m + n - 1;
	int n1 = m - 1;
	int n2 = n - 1;
	// 从后向前先合并大元素
	while (n1 >= 0 && n2 >= 0){
		if (nums1[n1] >= nums2[n2]){
			nums1[pos--] = nums1[n1--];
		}
		else{
			nums1[pos--] = nums2[n2--];
		}
	}
	// 遍历完后 检查第二个数组还有剩余元素
	if (n2 >= 0){
		memcpy(nums1, nums2, (n2 + 1)*sizeof(int));
	}
}
#define nums1Size 6
#define nums2Size 3
int main3(){
	int nums1[] = { 1, 2, 8 };
	int nums2[] = { 2, 4, 9 };
	int m = sizeof(nums1) / sizeof(int);
	int n = sizeof(nums1) / sizeof(int);
	//merge(nums1, nums1Size, m, nums2, nums2Size, n);
	merge2(nums1, nums1Size, m, nums2, nums2Size, n);
	for (int i = 0; i < nums1Size; i++){
		printf("%d ", nums1[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

/*
4. 旋转数组
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
	若k = 3:
	前面n-k逆转 --> 剩余元素进行逆转 --> 整体逆转

*/
void part_reverse(int* begin, int* end){
	int tmp;
	for (; begin < end; begin++, end--){
		tmp = *begin;
		*begin = *end;
		*end = tmp;
	}
}
void rotate(int* nums, int numsSize, int k){

	k %= numsSize;
	part_reverse(nums, nums + k - 1);
	part_reverse(nums + k, nums + numsSize - 1);
	part_reverse(nums, nums + numsSize - 1);
	
}
int main4(){
	int nums[] = { 1, 2, 3, 4, 5, 6, 7 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int k = 0;
	scanf("%d", &k);
	for (int i = 0; i < numsSize; i++){
		printf("%d ", nums[i]);
	}
	printf("\n");
	rotate(nums, numsSize, k);
	for (int i = 0; i < numsSize; i++){
		printf("%d ", nums[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

/*
5. 数组形式的整数加法
给定非负整数 X 的数组形式 A，返回整数 X+K 的数组形式。
输入：A = [1,2,0,0], K = 34
输出：[1,2,3,4]
解释：1200 + 34 = 1234

逐位相加, 如果每一位两个数都存在的话 才进行相加的操作
每一位的结果: 对应位的数字和 + 上一步的进位 --> 考虑是否有进位 --> 更新结果和进位
1. 获取整数的每一位数 %10/10 
  需考虑最高位的进位
*/
void reverse(int* ret, int left, int right){
	while (left < right){
		int tmp = ret[left];
		ret[left] = ret[right];
		ret[right] = tmp;
		++left;
		--right;
	}
}
int* addToArrayForm(int* A, int ASize, int K, int* returnSize){

	// 新开空间, 保存结果
	// 获取两数的最大长度
	// ASize已知, 但是K的大小未知, 先算K的大小, 
	int klen = 0;
	int tmp = K;
	while (tmp){
		++tmp;
		tmp /= 10;
	}
	// 再比较数组与数字的长度 决定最终新开存储空间的大小
	// 考虑进位的存放 开数组保存最终值 谁的长度最大 最终的长度为大数组或大数字长度+1,
	int retSize = ASize > klen ? ASize + 1 : klen + 1;
	int* ret = (int*)malloc(sizeof(int)* retSize);

	// 获取数组的长度
	int len = ASize - 1;
	int step = 0;// 进位
	int idx = 0;
	// 当长度>=0(最后一位为个位)或者数字大于0, 说明两数还有没加完的位
	while (len >= 0 || K > 0){
		// 当前对应位的结果, 首先加上上一步的进位, 最终整个的值用ret[idx]去接收
		ret[idx] = step;
		// 逐位相加
		if (len >= 0){ // 如果数组还有值 再加数组当前位置的值
			ret[idx] += A[len];
		}
		if (K > 0){ // 如果K还有值, 再加K的末位值
			ret[idx] += K % 10;
		}
	    //更新结果 
		//如果相加之后的结果大于10, 则step进1, ret[idx]为此时进位后的值(比如 11 --> 1)
		if (ret[idx] > 9){
			ret[idx] %= 10;
			step = 1;
		}
		else{
			step = 0;
		}

		// 保存当前位的结果(需要开一个数组 malloc)
		--len; // 数组前移一个元素(最后一个到倒数第二个)
		K /= 10;// 数字前移一个位数(个位到十位) 
		++idx;// idx为和的位索引(个十百千...)
	}
	// 此时所有的数都已加完, idx到了最高位, 看最高位是否有进位(step)
	// 是逆序 数组里第一位是个位, 第二位是十位,....
	if (step == 1){
		ret[idx++] = 1;// 如果有, 则产生新的最高位为1,
	}
	// 需逆转
	reverse(ret, 0, idx - 1);
	*returnSize = idx; // 最终返回的长度
	return ret;// 在返回当期那新开辟的数组的首地址
}
int main(){
	int A[] = { 1, 2, 0, 0 };
	int K = 34;
	int ASize = sizeof(A) / sizeof(A[0]);
	int returnSize[] = {0};
	for (int i = 0; i < ASize; i++){
		printf("%d ", addToArrayForm(A, ASize, K, returnSize));
	}
	printf("\n");

	system("pause");
	return 0;
}