#include <stdio.h>
void Hi(void) {
	printf("안녕\n");
}
void Hello(char c[]) {
	printf("%s\n", c);
}
int Hap(int a, int b) {
	return (a + b);
}
// main() 함수 : 프로그램의 진입점(Entry Point)
void main(void) {
	int intReturn = 0;
	//[0] 내장(Builtin) 함수 : 만들어져 있는 기능
	printf("안녕하세요.\n");
	//[!] 사용자정의(UserDefined) 함수 : 직접 기능 정의
	Hi(); Hi();//[a]매개변수도 없고 반환값도 없는 경우
	Hello("안녕"); Hello("방가");//[b]매개변수가 있는 경우
	intReturn = Hap(3, 5);//[c]반환값이 있는 경우
	printf("결과값 : %d\n", intReturn);
}