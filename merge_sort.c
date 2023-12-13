#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 30000
#define MAX_TOK 15
int sc, a=0, b=0; //정상, 비정상 도서코드 개수
clock_t start, end;

struct BookInfo {
    int category;
    int symbol;
    int year;
};

// CSV 파일 읽기 및 정제
void readcsv(char list[MAX_SIZE][MAX_TOK], char normal[MAX_SIZE][MAX_TOK], char abnormal[MAX_SIZE][MAX_TOK]) {
    FILE *fp = fopen("library.csv", "r");
    int t = 0;
    while (fscanf(fp, "%s", list[t++]) == 1 && t < MAX_SIZE) { // 문자열 데이터 읽어오기
    }
    fclose(fp);

    for (int i = 0; i < MAX_SIZE; i++) {
        if (strlen(list[i]) == MAX_TOK - 1) {
            strcpy(normal[a++], list[i]); // 정상 도서코드를 normal 배열에 복사
        } else{
            strcpy(abnormal[b++], list[i]); // 비정상 도서 코드를 abnormal 배열에 복사
        }
    }
}

void trash(char abnormal[MAX_SIZE][MAX_TOK]){
    for(int i=0; i<b;i++){
        printf("%d - %s\n",i+1, abnormal[i]);
    }
}

// 도서 분류 정렬
void merge_category(struct BookInfo book[], int left, int mid, int right) {
    int i, j, k, l;
    struct BookInfo temp[MAX_SIZE];
    i = left;
    j = mid+1;
    k = left;

    while (i <= mid && j <= right) {
        if (book[i].category <= book[j].category) {
            temp[k++] = book[i++];
        } else {
            temp[k++] = book[j++];
        }
    }

    // 남은 요소들을 복사
    if(i>mid){
        for(l=j;l<=right;l++){
            temp[k++] = book[l];
        }
    }
    else{
        for(l=i;l<=mid;l++) {
            temp[k++] = book[l];
        }
    }
    for(l=left;l<=right;l++){
        book[l]=temp[l];
    }

    end=clock();
}
// 분류 기호 정렬
void merge_symbol(struct BookInfo book[], int left, int mid, int right) {
    int i, j, k, l;
    struct BookInfo temp[MAX_SIZE];
    i = left;
    j = mid+1;
    k = left;

    while (i <= mid && j <= right) {
        if (book[i].symbol <= book[j].symbol) {
            temp[k++] = book[i++];
        } else {
            temp[k++] = book[j++];
        }
    }

    // 남은 요소들을 복사
    if(i>mid){
        for(l=j;l<=right;l++){
            temp[k++] = book[l];
        }
    }
    else{
        for(l=i;l<=mid;l++) {
            temp[k++] = book[l];
        }
    }
    for(l=left;l<=right;l++){
        book[l]=temp[l];
    }

    end=clock();
}

// 연도 정렬
void merge_year(struct BookInfo book[], int left, int mid, int right) {
    int i, j, k, l;
    struct BookInfo temp[MAX_SIZE];
    i = left;
    j = mid+1;
    k = left;
    while (i <= mid && j <= right) { // 분할 정렬된 배열 합병
        if (book[i].year <= book[j].year) {
            temp[k++] = book[i++];
        } else {
            temp[k++] = book[j++];
        }
    } 
    if(i>mid){
        for(l=j;l<=right;l++){ // 남은 요소들을 일괄 복사
            temp[k++] = book[l];
        }
    }
    else{
        for(l=i;l<=mid;l++) {
            temp[k++] = book[l];
        }
    }
    for(l=left;l<=right;l++){ // tmpe를 book으로 재복사
        book[l]=temp[l];
    }

    end=clock();
}
//전체 정렬
void merge_all(struct BookInfo book[], int left, int mid, int right) {
    int i, j, k, l;
    struct BookInfo temp[MAX_SIZE];
    i = left;
    j = mid+1;
    k = left;


    while (i <= mid && j <= right) {
        if (book[i].category < book[j].category) {
            temp[k++] = book[i++];
        } else if (book[i].category == book[j].category) {
            if (book[i].symbol < book[j].symbol) {
                temp[k++] = book[i++];
            } else if (book[i].symbol == book[j].symbol) {
                if (book[i].year <= book[j].year) {
                    temp[k++] = book[i++];
                } else {
                    temp[k++] = book[j++];
                }
            } else {
                temp[k++] = book[j++];
            }
        } else {
            temp[k++] = book[j++];
        }
    }
    // 남은 요소들을 복사
    if(i>mid){
        for(l=j;l<=right;l++){
            temp[k++] = book[l];
        }
    }
    else{
        for(l=i;l<=mid;l++) {
            temp[k++] = book[l];
        }
    }
    for(l=left;l<=right;l++){
        book[l]=temp[l];
    }

    end=clock();
}

void merge_sort(struct BookInfo book[], int left, int right) {
    if (left < right) {

        int mid = (left + right) / 2; //리스트 균등분할
        merge_sort(book, left, mid); // 왼쪽 부분 배열을 재귀적으로 정렬
        merge_sort(book, mid + 1, right); // 오른쪽 부분 배열을 재귀적으로 정렬
        
        switch (sc) {
            case 1: // 도서 분류 코드로 정렬
                merge_category(book, left, mid, right);
                break;
            case 2: // 분류 기호 코드로 정렬
                merge_symbol(book, left, mid, right);
                break;
            case 3: // 연도로 정렬
                merge_year(book, left, mid, right);
                break;
            case 4: // 분류 기준 전체로 정렬
                merge_all(book, left, mid, right);
                break;
            default:
                printf("잘못된 접근입니다. 프로그램을 정지합니다.");
                exit(0);
        }
    }
}

// 도서 출력
void printBooks(struct BookInfo book[], int n) {
    for (int i = 0; i < n; i++) {
        printf("도서 분류 : %d, 분류 기호 : %d, 연도: %d\n", book[i].category, book[i].symbol, book[i].year);
    }
}

// 문자열을 BookInfo 구조체로 변환
struct BookInfo convertToBookInfo(char normal[]) {
    struct BookInfo bk;

    char tempCategory[4];
    char tempSymbol[4];
    char tempYear[9];

    strncpy(tempCategory, normal, 3); // 문자열 일부분 복사
    tempCategory[3] = '\0';
    strncpy(tempSymbol, normal + 3, 3); 
    tempSymbol[3] = '\0'; 
    strncpy(tempYear, normal + 6, 8); 
    tempYear[8] = '\0'; 

    bk.category = atoi(tempCategory); // 문자열 정수 변환후 구조체에 저장
    bk.symbol = atoi(tempSymbol); 
    bk.year = atoi(tempYear); 

    return bk;
}

int main(void) {
    char list[MAX_SIZE][MAX_TOK];
    char normal[MAX_SIZE][MAX_TOK]; //정상 도서코드 배열
    char abnormal[MAX_SIZE][MAX_TOK]; //비정상 도서코드 배열
    readcsv(list, normal, abnormal); // csv파일 읽기 및 정제
    printf("\t\t\t\t\t원하시는 작업을 선택해주세요.\n\n");
    printf("\t[1] 도서 분류 기준 정렬 [2] 분류 기호 기준 정렬 [3] 연도 기준 정렬 [4] 전체 정렬 [5] 비정상 도서 출력\n입력 : ");
    scanf("%d", &sc);
    if(sc==5){
        trash(abnormal);
        exit(0);
    }
    struct BookInfo books[MAX_SIZE];
    for (int i = 0; i < a; i++) {
        struct BookInfo bookInfo = convertToBookInfo(normal[i]); // 문자열을 구조체로 변환
        books[i] = bookInfo; // 구조체 배열에 저장
    }
    start=clock();
    merge_sort(books, 0, a - 1); // 합병 정렬 수행
    printBooks(books, a); // 정렬된 결과 출력
    printf("소요 시간 : %f\n", (float)(end - start)/CLOCKS_PER_SEC);
    return 0;
}
