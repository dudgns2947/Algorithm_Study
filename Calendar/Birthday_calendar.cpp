#include<stdio.h>
#include<math.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define SHOW "* This program will show you displaying the day of the week or the birthday year calenda from caculate with Korean age *\n\n"
#define PROMPT "Please enter a person's birth date (yyyy mm dd).\nValid input range for the year entry is 0000 ~ 2020: \tex)2020 01 31.\n"
#define OP "\n\nPlease enter your option (1~4)\n\n"
#define A "Please enter a desired age. The valid range for the age is 0~120:\n"
#define E1 "*********************************************************************************\n"
#define E2 "*                                                                               *\n"
#define ERROR "Wrong input, please try again.\n"
#define PNS "\nPlease enter '-1' for previous month, '1' for next month and '0' for stop\ndisplaying: "
#define S1 "*\t1. Display the day of the week when the person was born\t\t\t*\n"
#define S2 "*\t2. Display the day of the week on person's nnth birthday\t\t*\n"
#define S3 "*\t3. Display the birth month calendar the birth year\t\t\t*\n"
#define S4 "*\t4. Display the birth month calendar of the person's nnth birthday\t*\n"
#define DI "\t\t\t This program was made by 김영훈\n\n"

void printcal(int y, int m, int ly, int sum);
void printm(int m);
int sumofday(int y, int m, int d);

int main() {
	printf(DI);
	printf(SHOW);
	printf(PROMPT);
	int y, m, d;
	int age = 0;
	int num;
	int ly;

	do {
		scanf("%4d %2d %2d", &y, &m, &d);
		if (!((0 <= y && y <= 2020) && (0 < m && m <= 12) && (0 < d && d <= 31))) {
			printf(ERROR);
		}
		else
		{
			break;
		}
	} while (1);

	printf(E1);
	printf("\n%d/%d, %d has been entered.\n", m,d,y);

	printf(OP);
	printf(E1);
	printf(E2);
	printf(S1);
	printf(S2);
	printf(S3);
	printf(S4);
	printf(E2);
	printf(E1);

	int day_of_ly = ((y - 1) * 365 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400)) % 7;
	int i;

	do {
		scanf("%d", &num);
		if (!(1 <= num && num <= 4)) {
			printf(ERROR);
		}
		else
		{
			break;
		}
	} while (1);

	int k;

	switch (num)
	{
	case 1:
		k = sumofday(y, m, d) % 7;
		switch (k)
		{
		case 0: printf("This person was born on Sunday.\n");
			break;
		case 1: printf("This person was born on Monday.\n");
			break;
		case 2: printf("This person was born on Tuesday.\n");
			break;
		case 3: printf("This person was born on Wendnedsday.\n");
			break;
		case 4: printf("This person was born on Thursday.\n");
			break;
		case 5: printf("This person was born on Friday.\n");
			break;
		case 6: printf("This person was born on Saturday.\n");
			break;
		default:
			break;
		}
		break;


	case 2:
		printf(E1);
		printf(A);
		scanf("%d", &age);
		printf("When you were %d years old, the result was...\n\n", age);
		k = sumofday(y + age - 1, m, d);
		ly = ((y + age - 2) * 365 + ((y + age - 2) / 4) - ((y + age - 2) / 100) + ((y + age - 2) / 400)) % 7;
		k = (k + ly) % 7;
		switch (k)
		{
		case 0: printf("%d years old birthday is Sunday.\n", age);
			break;
		case 1: printf("%d years old birthday is Monday.\n", age);
			break;
		case 2: printf("%d years old birthday is Tuesday.\n", age);
			break;
		case 3: printf("%d years old birthday is Wendnedsday.\n", age);
			break;
		case 4: printf("%d years old birthday is Thursday.\n", age);
			break;
		case 5: printf("%d years old birthday is Friday.\n", age);
			break;
		case 6: printf("%d years old birthday is Saturday.\n", age);
			break;
		default:
			break;
		}
		break;

	case 3:
		printf(S3);
		printcal(y, m, day_of_ly, sumofday(y, m, d));
		printf(PNS);
		while (1)
		{
			scanf("%d", &i);
			if (i == 0) {
				printf("Program was Eixt\n");
				break;
			}
			else if (i == -1 || i == 1) {
				m += i;
				if (m == 13) {
					m = 1; y++;
					day_of_ly = ((y - 1) * 365 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400)) % 7;
				}
				else if (m == 0) {
					m = 12; y--;
					day_of_ly = ((y - 1) * 365 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400)) % 7;
				}
				printcal(y, m, day_of_ly, sumofday(y, m, d));
				printf(PNS);
				continue;
			}
			else
				printf(ERROR);
			break;
		}

		break;

	case 4:
		printf(E1);
		printf(S4);
		printf(A);
		scanf("%d", &age);
		printf("When you were %d years old, the result was...\n\n", age);
		y += age - 1;
		day_of_ly = ((y - 1) * 365 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400)) % 7;
		printcal(y, m, day_of_ly, sumofday(y, m, d));
		printf(PNS);
		while (1)
		{
			scanf("%d", &i);
			if (i == 0) {
				printf("Program was Eixt\n");
				break;
			}
			else if (i == -1 || i == 1) {
				m += i;
				if (m == 13) {
					m = 1; y++;
				}
				else if (m == 0) {
					m = 12; y--;
				}
				printcal(y, m, day_of_ly, sumofday(y, m, d));
				printf(PNS);
				continue;
			}
			else
				printf(ERROR);
			break;
		}
		break;

	}
	printf("Thanks!\n");
	return 0;

}

int sumofday(int y, int m, int d) {
	int rs = 0;
	switch (m) {         //m-1월까지의 요일 합
	case 12: rs += 30;
	case 11: rs += 31;
	case 10: rs += 30;
	case 9: rs += 31;
	case 8: rs += 31;
	case 7: rs += 30;
	case 6: rs += 31;
	case 5: rs += 30;
	case 4: rs += 31;
	case 3: rs += 28;
	case 2: rs += 31;
	case 1:break;
	default: break;
	}
	if (m > 2) {
		if (y % 4 == 0) {
			if (y % 100 == 0) {
				if (y % 400 == 0)
					rs++;
			}
			else
				rs++;
		}
	}
	rs += d;
	return rs;
}  // 
void printm(int m) {
	switch (m) {
	case 1:printf("January\n");
		break;
	case 2:printf("February\n");
		break;
	case 3:printf("March\n");
		break;
	case 4:printf("April\n");
		break;
	case 5:printf("May\n");
		break;
	case 6:printf("June\n");
		break;
	case 7:printf("July\n");
		break;
	case 8:printf("August\n");
		break;
	case 9:printf("September\n");
		break;
	case 10:printf("October\n");
		break;
	case 11:printf("November\n");
		break;
	case 12:printf("December\n");
		break;
	default:break;
	}
}
void printcal(int y, int m, int ly, int sum) {
	int tmp = sumofday(y, m, 1) % 7 + ly;                                 //해당하는 월의 1일이 시작되는 날짜 세기용
	int flag = 0;            //1이면 윤년, 0이면 일반
	if (y % 4 == 0) {
		if (y % 100 == 0) {
			if (y % 400 == 0)
				flag = 1;
		}
		else
			flag = 1;
	}
	tmp = tmp % 7;
	printf("Year: %d\nMonth: ", y);
	printm(m);
	printf("SUN MON TUE WED THU FRI SAT\n");
	if (tmp < 7)
		for (int i = 0; i < tmp; i++)
			printf("    ");
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)   //31일인 달 출력
		for (int i = 1; i < 32; i++) {
			printf("%4d", i);
			if ((i + tmp) % 7 == 0)
				printf("\n");
		}
	else if (m == 4 || m == 6 || m == 9 || m == 11)                        //30일인 달 출력
		for (int i = 1; i < 31; i++) {
			printf("%4d", i);
			if ((i + tmp) % 7 == 0)
				printf("\n");
		}
	else if (m == 2 && flag == 0)                                    //28일인 달 출력
		for (int i = 1; i < 29; i++) {
			printf("%4d", i);
			if ((i + tmp) % 7 == 0)
				printf("\n");
		}
	else
		for (int i = 1; i < 30; i++) {                                 //29일인 달 출력
			printf("%4d", i);
			if ((i + tmp) % 7 == 0)
				printf("\n");
		}
}
