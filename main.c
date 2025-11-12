#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student 구조체 정의
typedef struct {
    int id;          // 학번 (정수)
    char name[20];   // 이름 (문자열)
    double score;    // 점수 (실수)
} Student;

/**
 * @brief 전체 학생의 평균 점수를 계산합니다.
 * @param students Student 구조체 배열의 포인터
 * @param count 학생 수
 * @return double 평균 점수
 */
double getAverage(const Student *students, int count) {
    double sum = 0.0;
    // 포인터 연산을 사용하여 배열 순회
    for (int i = 0; i < count; i++) {
        sum += (students + i)->score;
    }
    return sum / count;
}

/**
 * @brief 최고 성적을 받은 학생의 포인터를 반환합니다.
 * @param students Student 구조체 배열의 포인터
 * @param count 학생 수
 * @return Student* 최고 성적 학생 구조체의 포인터
 */
Student* getHigh(Student *students, int count) {
    Student *highest = students; // 첫 번째 학생을 초기 최고 성적자로 가정

    // 포인터 연산을 사용하여 배열 순회
    for (int i = 1; i < count; i++) {
        Student *current = students + i;
        
        if (current->score > highest->score) {
            highest = current;
        }
    }
    return highest;
}

/**
 * @brief 최저 성적을 받은 학생의 포인터를 반환합니다.
 * @param students Student 구조체 배열의 포인터
 * @param count 학생 수
 * @return Student* 최저 성적 학생 구조체의 포인터
 */
Student* getLow(Student *students, int count) {
    Student *lowest = students; // 첫 번째 학생을 초기 최저 성적자로 가정

    // 포인터 연산을 사용하여 배열 순회
    for (int i = 1; i < count; i++) {
        Student *current = students + i;

        if (current->score < lowest->score) {
            lowest = current;
        }
    }
    return lowest;
}

int main(void) {
    int num_students;
    Student *student_list = NULL;
    
    // 1. 학생 수 입력 및 최소 요구사항 확인
    while (1) {
        printf("학생 수: ");
        if (scanf("%d", &num_students) != 1 || num_students < 5) {
            // fprintf(stderr, ...) 대신 printf를 사용하여 출력
            printf("오류: 5명 이상의 정수를 입력해야 합니다.\n");
            // 버퍼 비우기
            while (getchar() != '\n'); 
        } else {
            break;
        }
    }

    // 2. 학생 수만큼 Student 구조체 배열 동적 할당
    student_list = (Student *)malloc(num_students * sizeof(Student));
    if (student_list == NULL) {
        // fprintf(stderr, ...) 대신 printf를 사용하여 출력
        printf("메모리 할당 실패!\n");
        return 1;
    }

    // 3. 학생 정보 입력 (예시 형식에 맞춰 출력)
    for (int i = 0; i < num_students; i++) {
        Student *current = student_list + i; 

        printf("%d번 학번: ", i + 1);
        scanf("%d", &(current->id));

        printf("%d번 이름: ", i + 1);
        scanf("%s", current->name);

        printf("%d번 성적: ", i + 1);
        scanf("%lf", &(current->score));
    }

    // 4. 결과 분석
    double average = getAverage(student_list, num_students);
    Student *high_scorer = getHigh(student_list, num_students);
    Student *low_scorer = getLow(student_list, num_students);

    // 5. 결과 출력 (채점 스크립트에 맞춘 형식: 이름 - 점수점)
    printf("\nAverage: %.1f\n", average);
    
    // 최고 성적자 출력: High: Choi - 92점
    // %.0f를 사용하여 소수점 없이 점수를 출력하고 '점'을 붙임
    printf("High: %s- %.0f점\n", 
            high_scorer->name, high_scorer->score);
    
    // 최저 성적자 출력: Low: Kim - 80점
    printf("Low: %s- %.0f점\n", 
            low_scorer->name, low_scorer->score);

    // 6. 메모리 해제
    if (student_list != NULL) {
        free(student_list);
    }

    return 0;
}
