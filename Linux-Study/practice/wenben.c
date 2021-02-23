#include <stdio.h>
#include <stdlib.h>

int main() {
	
	char* arr[1024];
	// 文件操作：
	FILE* fp = fopen("/home/superao/456","r");    // 打开文件，返回文件指针。
	if( fp == NULL ) {
		printf("文件打开失败\n");
		perror("open failed");
		return 1;
	}
	else {
		printf("打开成功！\n");
		fread(arr ,1 ,100 ,fp);
		printf("%s", arr);
	}
	return 0;
}
