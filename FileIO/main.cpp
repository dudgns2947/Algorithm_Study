#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>                  // 구조체를 정렬하기 위한 qsort함수가 들어간 헤더추가 
#include <Windows.h>

#define Director "\t\t\t\t2020 Project #3 - 김영훈\n"
#define Line1 "********************************************************************************************************************\n"
#define Line2 "\n--------------------------------------------------------------------------------------------------------------------\n"
#define EXPLANE "\n*** 이 프로그램은 한 학급의 학생들의 성적을 분석하여 다양한 통계를 계산하기 위한 프로그램입니다. ***\n"
#define MENU "선택할 메뉴를 입력하세요.\n\n"
#define MENU_ERR "\n\n*** 잘못된 번호를 입력하셨습니다. 다시 입력해주세요 ***\n"
#define EOFs "*** 프로그램을 종료합니다. ***\n"

#define SELECT_1 "1 : Student averages by student numbers \n"
#define SELECT_2 "2 : Student averages by grade point (descending order) \n"
#define SELECT_3 "3 : Student course pass rates\n"
#define SELECT_4 "4 : Student course averages per race\n"
#define SELECT_5 "5 : Student course pass rates per race \n"
#define SELECT_6 "6 : Histogram of student course pass rates per race \n"
#define SELECT_7 "7 : Exit the program\n"


#define MAX_STUDNET 50

// 전역변수
int std_num = 0;                                    // score.txt 파일에 있는 학생 수
double read_rate = 0;
double write_rate = 0;
double math_rate = 0;
double read_avg = 0;
double write_avg = 0;
double math_avg = 0;

// 인종 과목별 평균점수
double c_avg[3] = { 0.0, };                         // Caucasian
double b_avg[3] = { 0.0, };                         // Afro-American
double a_avg[3] = { 0.0, };                         // Asian
double h_avg[3] = { 0.0, };                         // Hispanic
double n_avg[3] = { 0.0, };                         // Native

// 인종 과목별 Pass비율
double c_pass[3] = { 0.0, };                        // Caucasian
double b_pass[3] = { 0.0, };                        // Afro-American
double a_pass[3] = { 0.0, };                        // Asian
double h_pass[3] = { 0.0, };                        // Hispanic
double n_pass[3] = { 0.0, };                        // Native

// 구조체
typedef struct _score{

	char race;             // 인종코드
	int num;               // 학생번호
	int wt;                // 쓰기점수
	int rd;                // 읽기점수
	int mt;                // 수학점수
	double avg;            // 점수평균

}score;


// 기능 함수
void avg_point(score* p);                               // 학생의 평균을 계산하는 함수
void std_course_avg(score* p);                          // 각 과목에 대한 평균을 구하는 함수
double tot_avg(score* p);                               // 전체 평균을 구하는 함수
void race_avg(score* p);                                // 평균 per race를 구하는 함수
void course_pass_rate(score*p);                         // 과목별 pass rate를 구하는 함수
void race_pass_rate(score*p);                           // 인종별 pass rate를 구하는 함수
void print_histogram_race(int i, double race[]);        // 과목별 인종에 대한 * = + 출력을 판단하는 함수 
int std_compare_num(const void *e1, const void *e2);    // 학번의 오름차순으로 compare 인수 함수
int std_compare_avg(const void *e1, const void *e2);    // 점수의 내림차순으로 compare 인수 함수


// SELECT 함수(print)
void std_avg_num(score* p);                             // SELECT_1
void std_avg_grade(score* p);                           // SELECT_2
void std_Pass_rate(score* p);                           // SELECT_3
void std_avg_race(score* p);                            // SELECT_4
void std_pass_race(score* p);                           // SELECT_5
void Histogram(score* p);                               // SELECT_6


/*      score.txt
*
* 순서 :학생 번호, 인종 코드, 쓰기 등급 점수(GP), 읽기 GP, 수학 GP
*
* ex) 1 a 85 70 90
*     3 c 85 80 80
*     4 h 70 50 40
*     6 b 80 50 70
*     5 n 70 60 30
*     9 n 100 40 50
*     7 a 95 100 80                               */




int main(){

	FILE *fp;

	fp = fopen("score.txt", "r");
	if (fp == NULL){
		printf("score.txt 파일이 없습니다.\n");
		printf(EOFs);
		fclose(fp);
		return -1;                                // EOF
	}


	score std[MAX_STUDNET];
	

	fscanf(fp, "%d", &std_num);

	if (std_num > MAX_STUDNET)                                            // 최대 학생수 초과 오류
	{
		puts("학급 내에 최대 학생수(50명)를 초과했습니다.");
		printf(EOFs);
		fclose(fp);
		return -1;
	}
		


	for (int i = 0; i < std_num; i++)                                               // 구조체에 학생부 저장하기
		fscanf(fp, "%d %c %d %d %d", &std[i].num, &std[i].race, &std[i].wt, &std[i].rd, &std[i].mt);


	for (int i = 0; i < std_num; i++)                                               // avg를 구조체에 저장하기
		avg_point(&std[i]); 



	// SELECT 함수를 이용하기 위해 함수 실행하기 
	race_pass_rate(std);
	course_pass_rate(std);
	std_course_avg(std);
	race_avg(std);

	printf(Line1);
	printf(Director);
	printf(Line1);
	printf(EXPLANE);
	

	while (1) {
		int menu;
		printf(Line2);
		printf(MENU);
		printf(SELECT_1);
		printf(SELECT_2);
		printf(SELECT_3);
		printf(SELECT_4);
		printf(SELECT_5);
		printf(SELECT_6);
		printf(SELECT_7);
		printf("Select menu(1~7): ");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			printf(Line1);
			printf(SELECT_1);
			std_avg_num(std);
			system("pause");
			break;

		case 2:
			printf(Line1);
			printf(SELECT_2);
			std_avg_grade(std);
			system("pause");
			break;

		case 3:
			printf(Line1);
			printf(SELECT_3);
			std_Pass_rate(std);
			system("pause");
			break;

		case 4:
			printf(Line1);
			printf(SELECT_4);
			std_avg_race(std);
			system("pause");
			break;

		case 5:
			printf(Line1);
			printf(SELECT_5);
			std_pass_race(std);
			system("pause");
			break;

		case 6:
			printf(Line1);
			printf(SELECT_6);
			Histogram(std);
			system("pause");
			break;

		case 7:
			printf(Line1);
			printf(EOFs);
			fclose(fp);
			return 0;

		default:
			printf(Line1);
			printf(MENU_ERR);
		
		}
	}
}



void avg_point(score* p) {

	int total = 0;
	double avg = 0;
	
	total += p->wt;
	total += p->rd;
	total += p->mt;

	p->avg = (double)total / 3;

}
double tot_avg(score* p){

	double tot_avg = 0;

	for (int i = 0; i < std_num; i++)
		tot_avg += (p[i]).avg;                                   // Total avg 구하기

	return (tot_avg / std_num);

}
void race_avg(score* p){

	// 초기화
	int c_cnt = 0;
	int b_cnt = 0;
	int a_cnt = 0;
	int h_cnt = 0;
	int n_cnt = 0;


	// 인종별 cource 평균점수 구하기

	for (int i = 0; i < std_num; i++)	
	{
		if (p[i].race == 'c'){
			c_avg[0] += p[i].rd;
			c_avg[1] += p[i].wt;
			c_avg[2] += p[i].mt;
			c_cnt++;
		}
		if (p[i].race == 'b'){
			b_avg[0] += p[i].rd;
			b_avg[1] += p[i].wt;
			b_avg[2] += p[i].mt;
			b_cnt++;
		}
		if (p[i].race == 'a'){
			a_avg[0] += p[i].rd;
			a_avg[1] += p[i].wt;
			a_avg[2] += p[i].mt;
			a_cnt++;
		}
		if (p[i].race == 'h'){
			h_avg[0] += p[i].rd;
			h_avg[1] += p[i].wt;
			h_avg[2] += p[i].mt;
			h_cnt++;
		}
		if (p[i].race == 'n'){
			n_avg[0] += p[i].rd;
			n_avg[1] += p[i].wt;
			n_avg[2] += p[i].mt;
			n_cnt++;
		}
	}

	for (int k = 0; k < 3; k++) {
		c_avg[k] /= (double)c_cnt;
		b_avg[k] /= (double)b_cnt;
		a_avg[k] /= (double)a_cnt;
		h_avg[k] /= (double)h_cnt;
		n_avg[k] /= (double)n_cnt;
	}

}
void std_course_avg(score* p){

	//초기화
	read_avg = 0;
	write_avg = 0;
	math_avg = 0;

	for (int i = 0; i < std_num; i++)
	{
		read_avg += p[i].rd;
		write_avg += p[i].wt;
		math_avg += p[i].mt;

	}
	read_avg /= std_num;
	write_avg /= std_num;
	math_avg /= std_num;
}
void course_pass_rate(score*p){

	// 초기화
	read_rate = 0;
	write_rate = 0;
	math_rate = 0;

	for (int i = 0; i < std_num; i++)    {

		if (p[i].rd >= 60)
			read_rate++;
		if (p[i].wt >= 60)
			write_rate++;
		if (p[i].mt >= 60)
			math_rate++;

	}
	
	// rate = (합격한 학생수)/(전체 학생수)*100 

	read_rate = read_rate / std_num * 100;                       
	write_rate = write_rate / std_num * 100;
	math_rate = math_rate / std_num * 100;

}
void race_pass_rate(score*p){

	//초기화
	int c_cnt = 0;
	int b_cnt = 0;
	int a_cnt = 0;
	int h_cnt = 0;
	int n_cnt = 0;
	

	// 인종별 cource pass rate 구하기
	// rate = (합격한 학생수)/(각 인종의 학생수)*100 

	for (int i = 0; i < std_num; i++)
	{
		if (p[i].race == 'c'){
			if (p[i].rd >= 60)
				c_pass[0]++;
			if (p[i].wt >= 60)
				c_pass[1]++;
			if (p[i].mt >= 60)
				c_pass[2]++;
			c_cnt++;
		}
		if (p[i].race == 'b'){
			if (p[i].rd >= 60)
				b_pass[0]++;
			if (p[i].wt >= 60)
				b_pass[1]++;
			if (p[i].mt >= 60)
				b_pass[2]++;
			b_cnt++;
		}
		if (p[i].race == 'a'){
			if (p[i].rd >= 60)
				a_pass[0]++;
			if (p[i].wt >= 60)
				a_pass[1]++;
			if (p[i].mt >= 60)
				a_pass[2]++;
			a_cnt++;
		}
		if (p[i].race == 'h'){
			if (p[i].rd >= 60)
				h_pass[0]++;
			if (p[i].wt >= 60)
				h_pass[1]++;
			if (p[i].mt >= 60)
				h_pass[2]++;
			h_cnt++;
		}
		if (p[i].race == 'n'){
			if (p[i].rd >= 60)
				n_pass[0]++;
			if (p[i].wt >= 60)
				n_pass[1]++;
			if (p[i].mt >= 60)
				n_pass[2]++;
			n_cnt++;
		}
	}

	for (int k = 0; k < 3; k++) {
		c_pass[k] = c_pass[k] / (double)c_cnt * 100;
		b_pass[k] = b_pass[k] / (double)b_cnt * 100;
		a_pass[k] = a_pass[k] / (double)a_cnt * 100;
		h_pass[k] = h_pass[k] / (double)h_cnt * 100;
		n_pass[k] = n_pass[k] / (double)n_cnt * 100;
	}
}
void print_histogram_race(int i, double race[]){

	
		if (i <= (race[0] / 10) && i <= (race[1] / 10) && i <= (race[2] / 10)) 
			printf("\t * = +");
		else if (i <= (race[0] / 10) && i <= (race[1] / 10))
			printf("\t * =  ");
		else if (i <= (race[0] / 10) && i <= (race[2] / 10))
			printf("\t *   +");
		else if (i <= (race[1] / 10) && i <= (race[2] / 10))
			printf("\t   = +");
		else if (i <= (race[0] / 10))
			printf("\t *    ");
		else if (i <= (race[1] / 10))
			printf("\t   =  ");
		else if (i <= (race[2] / 10))
			printf("\t     +");
		else
			printf("\t");

}
int std_compare_num(const void *e1, const void *e2){

	score* a = (score*)e1;
	score* b = (score*)e2;

	if (a->num > b->num)
		return 1;
	else 
		return -1;

}
int std_compare_avg(const void *e1, const void *e2){

	score* a = (score*)e1;
	score* b = (score*)e2;

	if (a->avg > b->avg)
		return -1;

	else if (a->avg < b->avg)
		return 1;

	else if (a->avg == b->avg){
		if (a->num > b->num)
			return 1;
		else
			return -1;
	}

}
void std_avg_num(score* p){

	qsort(p, std_num, sizeof(p[0]), std_compare_num);             // 학생부를 학번의 오름차순으로 정렬
	


	printf("\nNumber \t\t Average\n");
	printf("====== \t\t ======\n");
	
	for (int i = 0; i < std_num; i++)
	{
		printf("%d \t\t %.2lf", (p[i]).num, (p[i]).avg);
		printf("\n");
	}

	printf("Total avg.\t %.2lf\n", tot_avg(p));

}
void std_avg_grade(score* p){


	qsort(p, std_num, sizeof(p[0]), std_compare_avg);             // 학생부를 평균 점수에 대한 내림차순으로 정렬


	printf("\nNumber \t\t Average\n");
	printf("====== \t\t ======\n");
	for (int i = 0; i < std_num; i++)
	{
		printf("%d \t\t %.2lf", (p[i]).num, (p[i]).avg);
		printf("\n");

	}
	printf("Total avg.\t %.2lf\n", tot_avg(p));

}
void std_Pass_rate(score* p){


	printf("\nCourse Pass\n\n");
	printf("Name \t\t Rate(%%)\n");
	printf("====== \t\t ======\n");
	printf("Reading \t %.1lf\n", read_rate);
	printf("Writing \t %.1lf\n", write_rate);
	printf("Mathematics \t %.1lf\n", math_rate);
	

}
void std_avg_race(score* p){
	

	printf("\nRace \t\t Reading \t Writing \t Mathematics\n");
	printf("====== \t\t ======= \t ======= \t ===========\n");
	printf("Caucasian \t %.1lf \t\t %.1lf \t\t %.1lf\n", c_avg[0], c_avg[1], c_avg[2]);
	printf("Afro-American \t %.1lf \t\t %.1lf \t\t %.1lf\n", b_avg[0], b_avg[1], b_avg[2]);
	printf("Asian \t\t %.1lf \t\t %.1lf \t\t %.1lf\n", a_avg[0], a_avg[1], a_avg[2]);
	printf("Hispanic \t %.1lf \t\t %.1lf \t\t %.1lf\n", h_avg[0], h_avg[1], h_avg[2]);
	printf("Native \t\t %.1lf \t\t %.1lf \t\t %.1lf\n", n_avg[0], n_avg[1], n_avg[2]);
	printf("Average \t %.1lf \t\t %.1lf \t\t %.1lf\n", read_avg, write_avg, math_avg);



}
void std_pass_race(score* p){


	printf("\nRace \t\t Reading \t Writing \t Mathematics\n");
	printf("====== \t\t ======= \t ======= \t ===========\n");
	printf("Caucasian \t %.1lf \t\t %.1lf \t\t %.1lf\n", c_pass[0], c_pass[1], c_pass[2]);
	printf("Afro-American \t %.1lf \t\t %.1lf \t\t %.1lf\n", b_pass[0], b_pass[1], b_pass[2]);
	printf("Asian \t\t %.1lf \t\t %.1lf \t\t %.1lf\n", a_pass[0], a_pass[1], a_pass[2]);
	printf("Hispanic \t %.1lf \t\t %.1lf \t\t %.1lf\n", h_pass[0], h_pass[1], h_pass[2]);
	printf("Native \t\t %.1lf \t\t %.1lf \t\t %.1lf\n", n_pass[0], n_pass[1], n_pass[2]);
	printf("Average \t %.1lf \t\t %.1lf \t\t %.1lf\n", read_rate, write_rate, math_rate);


}
void Histogram(score* p) {


	printf("\n'*', '=', '+' are the pass rates of reading, writing, and math respectively.\n\n");


	for (int i = 10; i > 0; i--)
	{
		if (i % 2 == 1)
			printf("|");
		else
			printf("%d -", i * 10);


		print_histogram_race(i, c_pass);   // Caucasian

		printf("\t");
		print_histogram_race(i, b_pass);   // Afro-American
	
		printf("\t\t");
		print_histogram_race(i, a_pass);   // Asian

		printf("\t");
		print_histogram_race(i, h_pass);   // Hispanic

		printf("\t");
		print_histogram_race(i, n_pass);   // Native

		printf("\n");

	}

	printf("0 + =============================================================================================\n");
	printf("\tCaucasian\tAfro-American\t\tAsian\t\tHispanic\tNative\n");

}
