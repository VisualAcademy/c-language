#include <stdio.h>
void Hi(void) {
	printf("�ȳ�\n");
}
void Hello(char c[]) {
	printf("%s\n", c);
}
int Hap(int a, int b) {
	return (a + b);
}
// main() �Լ� : ���α׷��� ������(Entry Point)
void main(void) {
	int intReturn = 0;
	//[0] ����(Builtin) �Լ� : ������� �ִ� ���
	printf("�ȳ��ϼ���.\n");
	//[!] ���������(UserDefined) �Լ� : ���� ��� ����
	Hi(); Hi();//[a]�Ű������� ���� ��ȯ���� ���� ���
	Hello("�ȳ�"); Hello("�氡");//[b]�Ű������� �ִ� ���
	intReturn = Hap(3, 5);//[c]��ȯ���� �ִ� ���
	printf("����� : %d\n", intReturn);
}