#include <stdio.h>
#include <stdlib.h>

typedef struct seqList{
	int* _data;// ��̬����
	size_t _size;// ��С
	size_t _capacity;// ����
}seqList;

/*
1. �Ƴ�Ԫ��
 ����һ������ nums ��һ��ֵ val������Ҫԭ���Ƴ�������ֵ���� val ��Ԫ�أ�
 �������Ƴ���������³��ȡ���Ҫʹ�ö��������ռ� ʹ��O(1)�Ķ���ռ䲢ԭ���޸�����
 (1)��򵥵����� ---> ���¿�һ����ԭʼ����һ��������� Ȼ���Ҫɾ����Ԫ�ز��� ������Ԫ�ؿ���������, ������ռ临�Ӷ�ΪO(N) ����
 (2) ����ɾ�����ݵķ���, ������һ��val��, ����һ������val��ֵ Ȼ�󸲸�val��λ��
 ����i: ��ǰ������λ�� 
 idx: ���������������һ�����ݵ�λ��(�����ĵ�һ��val��λ��)

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
//		// ���û�ҵ���val��ȵ�����,��iλ�õ�Ԫ�ط���idx��, idx����ƶ�,
//		if (nums[i] != val){
//			nums[idx] = nums[i];
//			// ��������val��ȵ�����ǰ, idx�ܱ�i��һ�� ֱ������val�� idx��ʼ����i��
//			++idx;
//		}
//		// ����ҵ���val��ȵ�����, idx���� i��������ƶ�
//	}
	return idx;
}
int main(){
	int nums[] = { 3, 2, 4, 6, 1, 5, 6 };
	int numSize = sizeof(nums) / sizeof(nums[0]);
	int val = 6;
	printf("���� = %d", removeElement(nums, numSize, val));
	system("pause");
	return 0;
}