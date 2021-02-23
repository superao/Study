#include <stdio.h>
#include <stdlib.h>

int main() {
	int i,j;
	int num[1024];
	int temp = 0;

	// 输入
	printf("请输入 10 个数字：\n");
	for(  i = 0; i < 10; i++ ) {
		scanf("%d", &num[i]);
	}
	
	// 排序：
	for(i = 0; i < 9; i++) {       // 排序所进行的次数。
		for(j = 0; j < 9 - i; j++) {
			if(num[j] > num[j + 1]) {
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}

	// 输出：
	for ( i = 0; i < 10; i++) {
		printf("%d\n",num[i]);
	}
	
	return 0;
}
