#include <stdio.h>
#include <stdlib.h>

int main() {

        int i, j, k;
	int num[1024];
	int temp = 0;
	
	// 提示信息：
	printf("请输入 10 个数字：");
	for( i = 0; i < 10; i++ ) {
		scanf("%d", &num[i]);
	}

	// 排序：	
	for( i = 0; i < 10; i++ ) { // 遍历数组，对每一个数都需要和后面的数进行比较。
		k = i; // 将最小的数的下标储存到 临时变量 中。
		for( j = i + 1; j < 10; j++) {
			 if( num[k] > num[j] ) { //  将前面储存的数与后面的数进行比较。
				temp = num[k];
				num[k] = num[j];
				num[j] = temp;
			}
		}
	}

	// 输出;
	for( i = 0; i < 10; i++ ) {
		printf("%d\t", num[i]);
	} 
	
	return 0;
}			
