#include <stdio.h>
#define MAX 100
typedef struct {

	char title[50]; //일정제목
	char date[11]; // 날짜: yyyy-mm-dd
	int priority; // 우선순위
	int is_repeating; // 반복 일정 여부 0:없음, 1:있음


} schedule;

void addschedule(schedule* list, int* count);
void print_schedule(schedule* list, int count);
void delete_schedule(schedule* list, int* count);
void update_schedule(schedule* list, int count);

int main() {

	schedule list[MAX];
	int count = 0;
	int menu;

	while (1) {
		printf("\n--- 일정 관리 프로그램 ---\n");
		printf("1. 일정 추가\n");
		printf("2. 일정 출력\n");
		printf("3. 일정 삭제\n");
		printf("4. 일정 수정\n");
		printf("0. 종료\n");
		printf("메뉴를 선택하세요: ");
		scanf("%d", &menu);

		if (menu == 1)
			addschedule(list, &count);
		else if (menu == 2)
			print_schedule(list, count);
		else if (menu == 3)
			delete_schedule(list, &count);
		else if (menu == 4)
			update_schedule(list, count);
		else if (menu == 0)
			break;
		else
			printf("잘못된 입력입니다.\n");

	}




	return 0;
}

void addschedule(schedule* list, int* count)
{
	printf("일정 제목을 입력하세요: ");
	scanf(" %[^\n]", list[*count].title);

	printf("날짜를 입력하세요(YYYY-MM-DD): ");
	scanf("%s", list[*count].date);

	printf("우선순위를 입력하세요 (1:높음, 2:중간, 3:낮음): ");
	scanf("%d", &list[*count].priority);

	list[*count].is_repeating = 0;// 기본설정:반복X
	(*count)++;

	printf("일정이 추가되었습니다.\n");


}

void print_schedule(schedule* list, int count)
{
	if (count == 0)
	{
		printf("등록된 일정이 없습니다.\n");

		return;
	}

	printf("\n===== 일정 목록 =====\n");

	for (int i = 0; i < count; i++) {
		printf("%d. [%s] %s (우선순위: %d)\n", i + 1,
			list[i].date, list[i].title, list[i].priority);
	}

}

void delete_schedule(schedule* list, int* count)
{
	int num;
	if (*count == 0) {
		printf("삭제할 일정이 없습니다.\n");
		return;
	}

	print_schedule(list, *count);
	printf("삭제할 일정 번호를 입력하세요: ");
	scanf("%d", &num);

	if (num < 1 || num > *count) {
		printf("잘못된 번호입니다.\n");
		return;
	}

	// 배열을 앞으로 당기기
	for (int i = num - 1; i < *count - 1; i++) {
		list[i] = list[i + 1];
	}
	(*count)--;

	printf("일정이 삭제되었습니다.\n");
}


void update_schedule(schedule* list, int count) 
{
	int num;
	if (count == 0) {
		printf("수정할 일정이 없습니다.\n");
		return;
	}

	print_schedule(list, count);
	printf("수정할 일정 번호를 입력하세요: ");
	scanf("%d", &num);

	if (num < 1 || num > count) {
		printf("잘못된 번호입니다.\n");
		return;
	}

	int i = num - 1;
	printf("새 일정 제목: ");
	scanf(" %[^\n]", list[i].title);

	printf("새 날짜 (YYYY-MM-DD): ");
	scanf("%s", list[i].date);

	printf("새 우선순위 (1:높음, 2:중간, 3:낮음): ");
	scanf("%d", &list[i].priority);

	printf("일정이 수정되었습니다.\n");
}
