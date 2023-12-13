#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define CSVFILE "library.csv"
#define MAX_LINE 30000
#define MAX_TOK 15
#define INPUT 3

struct BookInfo {
    int category;
    int symbol;
    int date;
};

int index_a, index_b;

void readcsv(char data[MAX_LINE][MAX_TOK]) {
    FILE *file = fopen(CSVFILE, "r");

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(EXIT_FAILURE);
    } else {
        printf("파일 열기 성공\n");
    }

    size_t cnt = 0;

    // 파일에서 문자열 데이터를 읽어옴
    while (fscanf(file, "%s", data[cnt]) == 1 && cnt < MAX_LINE) {
        cnt++;
    }

    // 파일 닫기
    fclose(file);
}

void separate(char data[MAX_LINE][MAX_TOK], char a[MAX_LINE][MAX_TOK], char b[MAX_LINE][MAX_TOK]) {
    int aIndex = 0;
    int bIndex = 0;

    for (int i = 0; i < MAX_LINE; i++) {
        if (strlen(data[i]) == MAX_TOK - 1) {
            // 14자리인 경우
            strcpy(a[aIndex], data[i]);
            aIndex++;
        } else if (strlen(data[i]) == MAX_TOK - 4) {
            // 11자리인 경우
            strcpy(b[bIndex], data[i]);
            bIndex++;
        }
    }

    index_a = aIndex;
    index_b = bIndex;
}

void radixSortCategory(struct BookInfo arr[], int n, int index, int count[]) {
    const int RANGE = 10; // 기수 정렬에서 사용할 기수, 0부터 9까지
    struct BookInfo *output = malloc(n * sizeof(struct BookInfo));

    // 기수 정렬을 위한 배열 동적 할당
    int *countArray = (int *)malloc(RANGE * sizeof(int));

    // 각 기수별로 등장 횟수 초기화
    for (int i = 0; i < RANGE; i++)
        countArray[i] = 0;

    // 각 기수별로 등장 횟수를 세기
    for (int i = 0; i < n; i++)
        countArray[(arr[i].category / index) % RANGE]++;

    // 전체 정렬에 대한 기수별 등장 횟수 업데이트
    for (int i = 0; i < RANGE; i++)
        count[i] += countArray[i];

    // 누적 등장 횟수 계산
    for (int i = 1; i < RANGE; i++)
        countArray[i] += countArray[i - 1];

    // 기수에 따라 정렬
    for (int i = n - 1; i >= 0; i--) {
        output[countArray[(arr[i].category / index) % RANGE] - 1] = arr[i];
        countArray[(arr[i].category / index) % RANGE]--;
    }

    // 정렬된 결과 복사
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    // 메모리 해제
    free(output);
    free(countArray);
}

void radixSort(struct BookInfo arr[], int n, int index, int count[]) {
    const int RANGE = 10; // 기수 정렬에서 사용할 기수, 0부터 9까지
    // 메모리 할당
    struct BookInfo *output = malloc(n * sizeof(struct BookInfo));

    // 기수 정렬을 위한 배열 동적 할당
    int *countArray = (int *)malloc(RANGE * sizeof(int));

    // 각 기수별로 등장 횟수 초기화
    for (int i = 0; i < RANGE; i++)
        countArray[i] = 0;

    // 각 기수별로 등장 횟수를 세기
    for (int i = 0; i < n; i++)
        countArray[(arr[i].symbol / index) % RANGE]++;

    // 전체 정렬에 대한 기수별 등장 횟수 기록
    for (int i = 0; i < RANGE; i++)
        count[i] += countArray[i];

    // 누적 등장 횟수 계산(한 리스트의 n번큐 인덱스만큼의 구역 설정)
    for (int i = 1; i < RANGE; i++)
        countArray[i] += countArray[i - 1];

    // 기수에 따라 정렬
    /*
        * 리스트의 맨 마지막부터 읽음
        * 읽은 값을 할당된 인덱스 만큼 output의 인덱스에 저장
        * 읽은 값에 해당하는 인덱스 값 감소 == n번 큐 인덱스 만큼의 구역만 리스트에 저장
    */
    for (int i = n - 1; i >= 0; i--) {
        output[countArray[(arr[i].symbol / index) % RANGE] - 1] = arr[i];
        countArray[(arr[i].symbol / index) % RANGE]--;
    }

    // 정렬된 결과 복사
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    // 메모리 해제
    free(output);
    free(countArray);
}

// "날짜"에 대한 기수 정렬 함수
void radixSortDate(struct BookInfo arr[], int n, int index, int count[]) {
    const int RANGE = 10; // 기수 정렬에서 사용할 기수, 0부터 9까지
    struct BookInfo *output = malloc(n * sizeof(struct BookInfo));

    // 기수 정렬을 위한 배열 동적 할당
    int *countArray = (int *)malloc(RANGE * sizeof(int));

    // 각 기수별로 등장 횟수 초기화
    for (int i = 0; i < RANGE; i++)
        countArray[i] = 0;

    // 각 기수별로 등장 횟수를 세기
    for (int i = 0; i < n; i++)
        countArray[(arr[i].date / index) % RANGE]++;

    // 전체 정렬에 대한 기수별 등장 횟수 업데이트
    for (int i = 0; i < RANGE; i++)
        count[i] += countArray[i];

    // 누적 등장 횟수 계산
    for (int i = 1; i < RANGE; i++)
        countArray[i] += countArray[i - 1];

    // 기수에 따라 정렬
    for (int i = n - 1; i >= 0; i--) {
        output[countArray[(arr[i].date / index) % RANGE] - 1] = arr[i];
        countArray[(arr[i].date / index) % RANGE]--;
    }

    // 정렬된 결과 복사
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    // 메모리 해제
    free(output);
    free(countArray);
}

struct BookInfo convertToBookInfo(char number[]) {
    struct BookInfo bookInfo;

    // 문자열을 정수로 변환하여 구조체에 저장
    bookInfo.category = atoi(strncpy((char[4]){}, number, 3));
    bookInfo.symbol = atoi(strncpy((char[4]){}, number + 3, 3));
    bookInfo.date = atoi(strncpy((char[9]){}, number + 6, 8));

    return bookInfo;
}

void printBooks(struct BookInfo arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("도서 분류 코드: %d, 분류 기호 코드: %d, 날짜: %d\n", arr[i].category, arr[i].symbol, arr[i].date);
    }
}

double getElapsedTime(struct timeval start, struct timeval end) {
    return (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
}

int main(void) {
    char data[MAX_LINE][MAX_TOK];
    char a[MAX_LINE][MAX_TOK];
    char b[MAX_LINE][MAX_TOK];

    // CSV 파일 읽기
    readcsv(data);
    separate(data, a, b);

    // 구조체에 데이터 복사
    struct BookInfo books[MAX_LINE];
    for (int i = 0; i < index_a; i++) {
        struct BookInfo bookInfo = convertToBookInfo(a[i]);
        books[i] = bookInfo;
    }

    int selectedField = INPUT;
    printf("도서 분류 코드(1), 분류 기호 코드(2), 날짜(3) 중 선택하여 입력: ");
    //scanf("%d", &selectedField);

    struct timeval start, end;

    // 각 자릿수별로 기수 정렬 수행
    int count[10] = {0}; // 각 기수별로 등장 횟수를 세기 위한 배열 초기화

    switch (selectedField) {
        case 1:
            gettimeofday(&start, NULL);
            radixSortCategory(books, index_a, 1, count);
            radixSortCategory(books, index_a, 10, count);
            radixSortCategory(books, index_a, 100, count);
            gettimeofday(&end, NULL);
            printf("도서 분류 코드를 기준으로 기수 정렬:\n");
            break;
        case 2:
            gettimeofday(&start, NULL);
            radixSort(books, index_a, 1, count);
            radixSort(books, index_a, 10, count);
            radixSort(books, index_a, 100, count);
            gettimeofday(&end, NULL);
            printf("분류 기호 코드를 기준으로 기수 정렬:\n");
            break;
        case 3:
            gettimeofday(&start, NULL);
            radixSortDate(books, index_a, 1, count);
            radixSortDate(books, index_a, 10, count);
            radixSortDate(books, index_a, 100, count);
            radixSortDate(books, index_a, 1000, count);
            radixSortDate(books, index_a, 10000, count);
            radixSortDate(books, index_a, 100000, count);

            gettimeofday(&end, NULL);
            printf("날짜를 기준으로 기수 정렬:\n");
            break;
        default:
            printf("잘못된 입력\n");
            return 1;
    }

    printBooks(books, index_a);

    // 각 기수별로 등장 횟수 출력
    printf("각 기수별로 등장 횟수:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: %d\n", i, count[i]);
    }

    printf("소요 시간: %f초\n", getElapsedTime(start, end));

    return 0;
}