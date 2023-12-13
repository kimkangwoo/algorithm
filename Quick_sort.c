#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define CSVFILE "library.csv"
#define MAX_LINE 30000
#define MAX_TOK 15
#define SWAP(x, y, temp) ((temp)=(x), (x)=(y), (y)=(temp))
#define INPUT1 3
#define INPUT2 3

// ctrl + alt + N : 실행
// 실행 화면 : OUTPUT
//---------------------------------------------------------------
int d_cnt;      // 오류 코드 개수
int file_cnt;   // 파일의 총 길이
int r_cnt;      // 정상 파일의 길이
clock_t std, end;

struct cov{
    char one[4];
    char two[4];
    char three[9]; 
}con[MAX_LINE], mstruc;

// csv 파일 배열 생성 
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

// csv 파일 배열에서 쓰레기 값 && 정상값 배열 생성
void generation(char data[MAX_LINE][MAX_TOK], 
char def[MAX_LINE][MAX_TOK], char result[MAX_LINE][MAX_TOK] ){
    
    int cnt;
    int dcnt=0;
    int rcnt =0;

    for(cnt=0; cnt<MAX_LINE; cnt++){
        if(strlen(data[cnt])<MAX_TOK-1 && strlen(data[cnt])>0){
            strcpy(def[dcnt], data[cnt]);
            dcnt++;
        }
        if(strlen(data[cnt])==MAX_TOK-1){
            strcpy(result[rcnt], data[cnt]);
            rcnt++;
        }
    }

    d_cnt = dcnt;
    file_cnt = cnt;
    r_cnt = rcnt;
}

// 2개의 비균등 배열의 합병과정
int partition(long long list[MAX_LINE], int left, int right){
    long long pivot, temp;
    int low, high;

    low = left;
    high = right +1;
    pivot = list[left];

    do{
        do{
            low++;
        }while(low<=right && list[low]<pivot);

        do{
            high--;
        }while(high>=left && list[high]>pivot);

        if(low<high){
            SWAP(list[low], list[high], temp);
        }
    }while(low<high);

    SWAP(list[left], list[high], temp);

    return high;
}

void Quick_sort(long long list[MAX_LINE], int left, int right){
    if(left<right){
        int q = partition(list, left, right); // 정복

        Quick_sort(list, left, q-1); // 분할
        Quick_sort(list, q+1, right);  // 분할
    }
}

int pt(int left, int right){
    long long pivot; 
    char temp[9];
    int low, high;

    low = left;
    high = right +1;
    if(INPUT2==1){
        pivot = atoll(con[left].one);
    do{
        do{
            low++;
        }while(low<=right && atoll(con[low].one)<pivot);

        do{
            high--;
        }while(high>=left && atoll(con[high].one)>pivot);

        if(low<high){
            mstruc = con[low];
            con[low] = con[high];
            con[high] = mstruc;
        }
    }while(low<high);

        mstruc = con[left];
        con[left] = con[high];
        con[high] = mstruc;

    return high;
    }
    else if(INPUT2==2){ // ---------------------------
        pivot = atoll(con[left].two);
    do{
        do{
            low++;
        }while(low<=right && atoll(con[low].two)<pivot);

        do{
            high--;
        }while(high>=left && atoll(con[high].two)>pivot);

        if(low<high){
            mstruc = con[low];
            con[low] = con[high];
            con[high] = mstruc;
        }
    }while(low<high);

        mstruc = con[left];
        con[left] = con[high];
        con[high] = mstruc;

    return high;    
    }
    else if(INPUT2==3){ // --------------------------
        pivot = atoll(con[left].three);
    do{
        do{
            low++;
        }while(low<=right && atoll(con[low].three)<pivot);

        do{
            high--;
        }while(high>=left && atoll(con[high].three)>pivot);

        if(low<high){
            mstruc = con[low];
            con[low] = con[high];
            con[high] = mstruc;
        }
    }while(low<high);

        mstruc = con[left];
        con[left] = con[high];
        con[high] = mstruc;

    return high;  
    }
    else{printf("잘못된 입력");exit(EXIT_FAILURE);}
}

void quic(int left, int right){
    if(left<right){
        int q = pt(left, right); // 정복

        quic(left, q-1); // 분할
        quic(q+1, right);  // 분할
    }
}



int main(void) {
    char data[MAX_LINE][MAX_TOK];
    char def[MAX_LINE][MAX_TOK];
    char result[MAX_LINE][MAX_TOK];

    // CSV 파일 읽기 및 정제
    readcsv(data);
    generation(data, def, result);

    printf("파일 길이 : %d \n", file_cnt);
    printf("정상 파일 길이 : %d \n", r_cnt);
    printf("오류 코드 갯수 : %d \n", d_cnt);
    printf("---------------------------------\n");
    printf("<-----도서관 분류 코드입니다.----->\n");
    printf("---------------------------------\n");
    printf("정렬하고싶은 데이터를 말해주세요\n");
    printf("1. 전체 2. 정상 코드 3. 비정상 코드]\n\n");
    printf("정렬 [ %d ] 선택했습니다.\n\n",  INPUT1);
    
    if(INPUT1 == 1){// 전체 코드 정렬 (data)
        int cnt =0;
        long long code[MAX_LINE];
        while(cnt != MAX_LINE){
            code[cnt] = atoll(data[cnt]);
            cnt++;
        }

        std = clock();
        Quick_sort(code, 0, MAX_LINE-1);
        end = clock();

        for (size_t i = 0; i < MAX_LINE; i++) {
            printf("%lld\n", code[i]);
        }
    }
    if(INPUT1==2){
        printf("정렬하고싶은 위치를 말해주세요.\n");
        printf("[ 1 ][ 2 ][ 3 ]\n\n");
        printf("[ %d ] 선택하셨습니다.\n\n", INPUT2);

        for(int i=0;i<r_cnt;i++){
            sscanf(result[i], "%3s%3s%8s", con[i].one, con[i].two, con[i].three);
        }
        std = clock();
        quic(0, r_cnt-1);
        end = clock();
        
        for(int i=0;i<r_cnt;i++){
                printf("%s%s%s\n", con[i].one, con[i].two, con[i].three);
        }
    }
    if(INPUT1==3){
        printf("정렬하고싶은 위치를 말해주세요.\n");
        printf("[ 2 ][ 3 ]\n\n");
        printf("[ %d ] 선택하셨습니다.\n\n", INPUT2);

        if(INPUT2 == 1){
            printf("잘못된 입력");
            return 1;
        }

        for(int i=0;i<d_cnt;i++){
            sscanf(def[i], "%3s%8s", con[i].two, con[i].three);
        }
        std = clock();
        quic(0, d_cnt-1);
        end = clock();

        for(int i=0;i<d_cnt;i++){
                printf("%s%s\n", con[i].two, con[i].three);
        }
    }

    double time = ((double) (end - std))/ CLOCKS_PER_SEC;
    printf("정렬하는데 걸린 시간 : %f 초 입니다.", time);

    return 0;
}