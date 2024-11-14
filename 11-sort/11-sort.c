#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

void generateRandomData(int list[]) {
    int n = SIZE;
   
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;  // 0-999 사이의 랜덤 데이터 생성
    }
}

void doSelectionSort(int list[]) {
    int n = SIZE;
    int i, j, least, temp;
  

    printf("선택 정렬");

    printf("\n");
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) { // 최솟값 탐색
            if (list[j] < list[least]) least = j;
        }
        SWAP(list[i], list[least], temp);

        // 10, 30, 50, ..., n-1 단계에서 출력
        if ((i + 1) % 20 == 10 || i == n - 2) {
            printf("step %d: ", (i + 1));
            for (int k = 0; k < n; k++) {
                printf("%d ", list[k]);
            }
            printf("\n");
        }
    }

}

void doInsertionSort(int randomData[]) {
    int n = SIZE;
    int totalComparisons = 0;  // 총 비교 횟수 변수
    srand(time(NULL));

    // 20회 삽입 정렬 시도
    for (int trial = 0; trial < 20; trial++) {
        int insertionData[SIZE];

        // 랜덤 데이터를 생성하여 삽입 정렬에 사용
        generateRandomData(insertionData, SIZE);  // 새로운 랜덤 데이터 생성


        // 랜덤 데이터 출력
        printf("삽입 정렬에 사용될 랜덤 데이터 (Trial %d): ", trial + 1);
        for (int k = 0; k < SIZE; k++) {
            printf("%d ", insertionData[k]);
        }
        printf("\n");

        int comparisons = 0;  // 현재 시도의 비교 횟수 초기화

        // 삽입 정렬 수행
        for (int i = 1; i < n; i++) {
            int key = insertionData[i];
            int j = i - 1;
            while (j >= 0 && insertionData[j] > key) {
                insertionData[j + 1] = insertionData[j]; // 레코드의 오른쪽 이동
                j--;
                comparisons++;  // 비교 횟수 증가
            }
            insertionData[j + 1] = key;
            comparisons++;  // 마지막 비교 횟수 증가
        }

        totalComparisons += comparisons;  // 시도에서의 비교 횟수 누적


    }
    printf("\n");
    // 평균 비교 횟수 출력
    printf("삽입 정렬 평균 비교 횟수: %d\n", totalComparisons / 20);

    printf("\n");
    // 정렬 결과만 출력
    printf("삽입 정렬 결과: ");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", randomData[k]);
    }
    printf("\n");


}


void doBubbleSort(int randomData[]) {
    int n = SIZE;
    int totalMoves = 0;  // 전체 이동 횟수 초기화
    srand(time(NULL));

    // 20회 버블 정렬 시도
    for (int trial = 0; trial < 20; trial++) {
        int bubbleData[SIZE];

        // 랜덤 데이터를 생성하여 버블 정렬에 사용
        generateRandomData(bubbleData, SIZE);  // 새로운 랜덤 데이터 생성

        // 랜덤 데이터 출력
        printf("버블 정렬에 사용될 랜덤 데이터 (Trial %d): ", trial + 1);
        for (int k = 0; k < SIZE; k++) {
            printf("%d ", bubbleData[k]);
        }
        printf("\n");
        

        int moves;  // 현재 시도의 이동 횟수 초기화
        for (int i = n - 1; i > 0; i--) {
            moves = 0; // 매 반복에서 이동 횟수 초기화
            for (int j = 0; j < i; j++) { // 앞뒤의 레코드를 비교한 후 교체
                if (bubbleData[j] > bubbleData[j + 1]) {
                    // 스왑
                    int temp = bubbleData[j];
                    bubbleData[j] = bubbleData[j + 1];
                    bubbleData[j + 1] = temp;
                    moves += 3; // 스왑 시 3회 이동으로 계산
                }
            }
            totalMoves += moves; // 전체 이동 횟수에 추가
        }


    }

    printf("\n");
    // 평균 이동 횟수 출력
    printf("버블 정렬 평균 이동 횟수: %d\n", totalMoves / 20);
    printf("\n");


    // 정렬 결과 출력
    printf("버블 정렬 결과:");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", randomData[k]);
    }


}

int main() {

    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
