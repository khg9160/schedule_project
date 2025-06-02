#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    char title[50];       // 일정 제목
    char date[11];        // 날짜: yyyy-mm-dd
    int priority;         // 우선순위
} schedule;

void addschedule(schedule* list, int* count);
void print_schedule(schedule* list, int count);
void delete_schedule(schedule* list, int* count);
void update_schedule(schedule* list, int count);
void sort_by_priority(schedule* list, int count);
void sort_by_date(schedule* list, int count);
void print_by_priority(schedule* list, int count);
void search_by_date(schedule* list, int count);
void show_schedule_stats(schedule* list, int count);
void recommend_important_schedule(schedule* list, int count);
int date_difference(const char* date1, const char* date2);
void save_to_file(schedule* list, int count);
void load_from_file(schedule* list, int* count);

int main() {
    schedule list[MAX];
    int count = 0;
    int menu;

    while (1) {
        printf("\n=========== 일정 관리 프로그램 ===========\n");
        printf(" 1. 일정 추가\n");
        printf(" 2. 일정 출력 \n");
        printf(" 3. 일정 삭제\n");
        printf(" 4. 일정 수정\n");
        printf(" 5. 우선순위 정렬\n");
        printf(" 6. 날짜로 일정 검색\n");
        printf(" 7. 일정 통계 출력\n");
        printf(" 8. 가장 중요한 일정 추천\n");
        printf(" 9. 일정 파일 저장\n");
        printf("10. 일정 파일 불러오기\n");
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
        else if (menu == 5)
            print_by_priority(list, count);
        else if (menu == 6)
            search_by_date(list, count);
        else if (menu == 7)
            show_schedule_stats(list, count);
        else if (menu == 8)
            recommend_important_schedule(list, count);
        else if (menu == 9)
            save_to_file(list, count);
        else if (menu == 10)
            load_from_file(list, &count);
        else if (menu == 0)
            break;
        else
            printf("잘못된 입력입니다.\n");
    }

    return 0;
}

void addschedule(schedule* list, int* count) {
    printf("일정 제목을 입력하세요: ");
    scanf(" %[^\n]", list[*count].title);

    printf("날짜를 입력하세요(YYYY-MM-DD): ");
    scanf("%s", list[*count].date);

    printf("우선순위를 입력하세요 (1:높음, 2:중간, 3:낮음): ");
    scanf("%d", &list[*count].priority);

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

    sort_by_date(list, count); // 날짜순 정렬

    printf("\n=========== 일정 목록 ===========\n");

    for (int i = 0; i < count; i++) {
        printf("%d. [%s] %s (우선순위: %d)\n", i + 1,
            list[i].date, list[i].title, list[i].priority);
    }
}


void delete_schedule(schedule* list, int* count) {
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

    for (int i = num - 1; i < *count - 1; i++) {
        list[i] = list[i + 1];
    }
    (*count)--;

    printf("일정이 삭제되었습니다.\n");
}

void update_schedule(schedule* list, int count) {
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

void sort_by_priority(schedule* list, int count) {
    schedule temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[i].priority > list[j].priority) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void sort_by_date(schedule* list, int count) {
    schedule temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(list[i].date, list[j].date) > 0) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}


void print_by_priority(schedule* list, int count) {
    if (count == 0) {
        printf("등록된 일정이 없습니다.\n");
        return;
    }

    sort_by_priority(list, count);

    printf("\n======= 우선순위 기준 일정 목록 =======\n");
    for (int i = 0; i < count; i++) {
        printf("%d. (우선순위: %d) %s [%s]\n", i + 1,
            list[i].priority, list[i].title, list[i].date);
    }
}

void search_by_date(schedule* list, int count) {
    char target_date[11];
    int found = 0;

    if (count == 0) {
        printf("검색할 일정이 없습니다.\n");
        return;
    }

    printf("검색할 날짜를 입력하세요 (YYYY-MM-DD): ");
    scanf("%s", target_date);

    printf("\n===== [%s] 일정 목록 =====\n", target_date);
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].date, target_date) == 0) {
            printf("%d. %s (우선순위: %d)\n", i + 1, list[i].title, list[i].priority);
            found = 1;
        }
    }

    if (!found) {
        printf("해당 날짜에 일정이 없습니다.\n");
    }
}

void show_schedule_stats(schedule* list, int count) {
    int high = 0, mid = 0, low = 0;

    if (count == 0) {
        printf("등록된 일정이 없습니다.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (list[i].priority == 1) high++;
        else if (list[i].priority == 2) mid++;
        else if (list[i].priority == 3) low++;
    }

    printf("\n=========== 일정 통계 ===========\n");
    printf("총 일정 수: %d\n", count);
    printf("우선순위 높음(1): %d개\n", high);
    printf("우선순위 중간(2): %d개\n", mid);
    printf("우선순위 낮음(3): %d개\n", low);
}

void recommend_important_schedule(schedule* list, int count) {
    if (count == 0) {
        printf("등록된 일정이 없습니다.\n");
        return;
    }

    char today[11];
    printf("기준 날짜를 입력하세요 (YYYY-MM-DD): ");
    scanf("%s", today);

    int max_score = -1;
    int best_index = -1;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].date, today) < 0) continue;

        int priority_score = (list[i].priority == 1) ? 3 : (list[i].priority == 2) ? 2 : 1;
        int days_diff = date_difference(today, list[i].date);
        int date_score = 100 - days_diff;
        if (date_score < 0) date_score = 0;

        int total_score = priority_score * 10 + date_score;

        if (total_score > max_score) {
            max_score = total_score;
            best_index = i;
        }
    }

    if (best_index == -1) {
        printf("오늘 이후의 중요한 일정이 없습니다.\n");
    }
    else {
        printf("\n 추천 일정:\n");
        printf("[%s] %s (우선순위: %d)\n",
            list[best_index].date,
            list[best_index].title,
            list[best_index].priority);
    }
}

int date_difference(const char* date1, const char* date2) {
    int y1, m1, d1, y2, m2, d2;
    sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);
    return (y2 - y1) * 365 + (m2 - m1) * 30 + (d2 - d1); // 간단 계산
}



void save_to_file(schedule* list, int count) {
    FILE* fp = fopen("schedules.txt", "w");
    if (fp == NULL) {
        printf("파일 저장에 실패했습니다.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%d\n",
            list[i].title,
            list[i].date,
            list[i].priority);
    }

    fclose(fp);
    printf("일정이 파일에 저장되었습니다.\n");
}

void load_from_file(schedule* list, int* count) {
    FILE* fp = fopen("schedules.txt", "r");
    if (fp == NULL) {
        printf("저장된 파일이 없어 불러오지 못했습니다.\n");
        return;
    }

    *count = 0;
    while (fscanf(fp, " %49[^,],%10[^,],%d\n",
        list[*count].title,
        list[*count].date,
        &list[*count].priority) == 3) {
        (*count)++;
    }

    fclose(fp);
    printf("일정이 파일에서 불러와졌습니다.\n");
} 