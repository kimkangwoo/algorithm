#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CSVFILE "library.csv"
#define MAX_LINE 30000
#define MAX_TOK 15

clock_t start, end;

struct BookInfo {
    int category;
    int symbol;
    int date;
};

int index_a, index_b;

struct BookInfo convert(char str[MAX_TOK]) {
    struct BookInfo book;

    // 각각의 부분을 적절히 변환하여 구조체에 저장
    char tempCategory[4];
    char tempSymbol[4];
    char tempDate[9];

    strncpy(tempCategory, str, 3);
    tempCategory[3] = '\0';
    strncpy(tempSymbol, str + 3, 3);
    tempSymbol[3] = '\0';
    strncpy(tempDate, str + 6, 8);
    tempDate[8] = '\0';

    book.category = atoi(tempCategory);
    book.symbol = atoi(tempSymbol);
    book.date = atoi(tempDate);

    return book;
}

void readcsv(char data[MAX_LINE][MAX_TOK]) {
    FILE *file = fopen(CSVFILE, "r");

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(EXIT_FAILURE);
    } else {
        printf("파일 열기 성공\n");
    }

    size_t cnt = 0;

    while (fscanf(file, "%s", data[cnt]) == 1 && cnt < MAX_LINE) {
        cnt++;
    }

    fclose(file);
}

void separate(char data[MAX_LINE][MAX_TOK], char a[MAX_LINE][MAX_TOK], char b[MAX_LINE][MAX_TOK]) {
    int aIndex = 0;
    int bIndex = 0;

    for (int i = 0; i < MAX_LINE; i++) {
        if (strlen(data[i]) == 14) {
            strcpy(a[aIndex], data[i]);
            aIndex++;
        } else if (strlen(data[i]) == 11) {
            strcpy(b[bIndex], data[i]);
            bIndex++;
        }
    }

    index_a = aIndex;
    index_b = bIndex;
}

void bubbleSort(struct BookInfo arr[], int n, int field) {
    start = clock();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            switch (field) {
                case 1:
                    if (arr[j].category > arr[j + 1].category) {
                        struct BookInfo temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                    break;
                case 2:
                    if (arr[j].symbol > arr[j + 1].symbol) {
                        struct BookInfo temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                    break;
                case 3:
                    if (arr[j].date > arr[j + 1].date) {
                        struct BookInfo temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                    break;
            }
        }
    }

    end = clock();
}

void printBooks(struct BookInfo arr[], int n, int field) {
    switch (field) {
        case 1:
            printf("도서 분류 코드를 기준으로 정렬:\n");
            break;
        case 2:
            printf("분류 기호 코드를 기준으로 정렬:\n");
            break;
        case 3:
            printf("연도를 기준으로 정렬:\n");
            break;
    }

    for (int i = 0; i < n; i++) {
        printf("도서 분류 코드: %d, 분류 기호 코드: %d, 날짜: %d\n", arr[i].category, arr[i].symbol, arr[i].date);
    }
}

void trash(char abnormal[MAX_LINE][MAX_TOK]) {
    for (int i = 0; i < index_b; i++) {
        printf("%d - %s\n", i + 1, abnormal[i]);
    }
}

void symbolSort(struct BookInfo arr[], int n) {
    bubbleSort(arr, n, 2);
    printBooks(arr, n, 2);
}

void dateSort(struct BookInfo arr[], int n) {
    bubbleSort(arr, n, 3);
    printBooks(arr, n, 3);
}

void overallSort(struct BookInfo arr[], int n) {
    bubbleSort(arr, n, 1);

    // 도서 코드가 같으면 분류 기호 코드로 정렬
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].category == arr[j + 1].category && arr[j].symbol > arr[j + 1].symbol) {
                struct BookInfo temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 분류 기호 코드가 같으면 날짜로 정렬
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].category == arr[j + 1].category && arr[j].symbol == arr[j + 1].symbol &&
                arr[j].date > arr[j + 1].date) {
                struct BookInfo temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 정렬된 결과 출력
    printBooks(arr, n, 1);
}

int main(void) {
    char data[MAX_LINE][MAX_TOK];
    char a[MAX_LINE][MAX_TOK];
    char b[MAX_LINE][MAX_TOK];

    readcsv(data);
    separate(data, a, b);

    int sc;
    printf("\t\t\t\t\t원하시는 작업을 선택해주세요.\n\n");
    printf("\t[1] 도서 분류 코드 기준 정렬 [2] 분류 기호 코드 기준 정렬 [3] 날짜 기준 정렬 [4] 전체 정렬 [5] 비정상 도서 출력\n입력 : ");
    scanf("%d", &sc);

    struct BookInfo books[MAX_LINE];

    switch (sc) {
        case 1:
            // 도서 분류 코드를 기준으로 정렬
            for (int i = 0; i < index_a; i++) {
                books[i] = convert(a[i]);
            }
            bubbleSort(books, index_a, 1);
            printBooks(books, index_a, 1);
            break;
        case 2:
            // 분류 기호 코드를 기준으로 정렬
            for (int i = 0; i < index_a; i++) {
                books[i] = convert(a[i]);
            }
            symbolSort(books, index_a);
            break;
        case 3:
            // 날짜를 기준으로 정렬
            for (int i = 0; i < index_a; i++) {
                books[i] = convert(a[i]);
            }
            dateSort(books, index_a);
            break;
        case 4:
            // 전체 정렬
            for (int i = 0; i < index_a; i++) {
                books[i] = convert(a[i]);
            }
            overallSort(books, index_a);
            break;
        case 5:
            // 비정상 도서 출력
            trash(b);
            break;
        default:
            printf("잘못된 입력입니다.\n");
            break;
    }
    printf("정렬 소요 시간 : %f 초\n", (float)(end - start) / CLOCKS_PER_SEC);
    return 0;
}