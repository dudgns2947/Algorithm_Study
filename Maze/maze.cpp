#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define POSSIBLE_ZEROS 100
#define EXPLAIN " *** 이 프로그램은 미로찾기 프로그램입니다.*** " 
#define NEXTMOVE "다음 위치로 이동합니다.\n\n"
#define ARRIVE "출구에 도착했습니다.\n"
#define FAILURE "길이 없어 입구로 되돌아왔습니다.\n"
#define EOF "\n****************************** 미로찾기 함수를 종료합니다. 감사합니다 ******************************"


int startexit[2];                                      // 입구와 출구의 방향설정을 저장할 변수
char maze[12][12];                                     // 12x12 미로(2차원 배열)
int S;                                                 // Flag값을 저장할 변수
int direct[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } };    // 방향 설정 ( 동쪽 - 0 , 북쪽 - 1 , 서쪽 - 2, 남쪽 - 3 )
int startX, startY, endX, endY;                        // 시작지점, 도착지점의 위치를 저장할 변수


void MAZE_INPUT_ZEROS(void);                           // 랜덤으로 경로를 만드는 함수
void Coord_XY(void);                                   // 랜덤으로 시작지점과 도착지점을 만드는 함수
void traverseMaze(char maze[12][12], const int xCoord, const int yCoord, int x, int y, int direction);              // 미로를 탐색하는 함수
void printMaze(char maze[12][12]);                     // 미로를 출력하는 함수
void Initialize_Maze(void);                             // 미로를 1's로 초기화 하는 함수


int main() {


	Initialize_Maze();                                    // 미로를 1로 초기화 하기

	puts(EXPLAIN);
	printf("--------------------------------------------------------------------------------\n");

	MAZE_INPUT_ZEROS();                                  // 랜덤으로 0's 이 삽입된 미로
	Coord_XY();                                          // 입출구 선정
	puts("랜덤으로 형성된 미로\n");
	printMaze(maze);                                     // 미로 출력

	printf("--------------------------------------------------------------------------------\n");
	puts("Start!");

	switch (S)
	{

	case 1: traverseMaze(maze, endX, endY, startX, startY, 2);     //시작이 왼쪽 모서리일 경우 미로를 탐색하는 함수 실행
		break;
	case 2: traverseMaze(maze, endX, endY, startX, startY, 0);     //시작이 오른쪽 모서리일 경우 미로를 탐색하는 함수 실행
		break;
	case 3: traverseMaze(maze, endX, endY, startX, startY, 1);     //시작이 위쪽 모서리일 경우 미로를 탐색하는 함수 실행
		break;
	case 4: traverseMaze(maze, endX, endY, startX, startY, 3);     //시작이 아래쪽 모서리일 경우 미로를 탐색하는 함수 실행
		break;

	default:
		break;

	}


	puts(EOF);

	return 0;

}

void printMaze(char maze[12][12]){                 // 미로를 출력하는 함수

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}
void traverseMaze(char maze[12][12], const int xCoord, const int yCoord, int x, int y, int direction) {                       // 미로를 탐색하는 함수


	maze[y][x] = 'X';                          // 현재위치 'X'로 표시해주기


	if (y == endY && x == endX){                // 도착했으면 종료하기
	
		system("Pause");
		printMaze(maze);
		printf(ARRIVE);
		puts(EOF);
		exit(0);
		return;

	}

	direction = (direction + 1) % 4;

	if (maze[y + direct[direction][1]][x + direct[direction][0]] == '0'               // 동쪽 방향 탐색
		&& 0 <= y + direct[direction][1] && y + direct[direction][1] <= 11
		&& 0 <= x + direct[direction][0] && x + direct[direction][0] <= 11)
	{
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
		traverseMaze(maze, endX, endY, x + direct[direction][0], y + direct[direction][1], (direction + 2) % 4);  // 재귀함수 실행
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);

	}
	direction = (direction + 1) % 4;;


	if (maze[y + direct[direction][1]][x + direct[direction][0]] == '0'                // 북쪽 방향 탐색
		&& 0 <= y + direct[direction][1] && y + direct[direction][1] <= 11
		&& 0 <= x + direct[direction][0] && x + direct[direction][0] <= 11)
	{
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
		traverseMaze(maze, endX, endY, x + direct[direction][0], y + direct[direction][1], (direction + 2) % 4);   // 재귀함수 실행
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
	}
	direction = (direction + 1) % 4;


	if (maze[y + direct[direction][1]][x + direct[direction][0]] == '0'                  // 서쪽 방향 탐색
		&& 0 <= y + direct[direction][1] && y + direct[direction][1] <= 11
		&& 0 <= x + direct[direction][0] && x + direct[direction][0] <= 11)
	{
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
		traverseMaze(maze, endX, endY, x + direct[direction][0], y + direct[direction][1], (direction + 2) % 4);   // 재귀함수 실행
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
	}
	direction = (direction + 1) % 4;


	if (maze[y + direct[direction][1]][x + direct[direction][0]] == '0'                  // 남쪽 방향 탐색
		&& 0 <= y + direct[direction][1] && y + direct[direction][1] <= 11
		&& 0 <= x + direct[direction][0] && x + direct[direction][0] <= 11)
	{
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
		traverseMaze(maze, endX, endY, x + direct[direction][0], y + direct[direction][1], (direction + 2) % 4);   // 재귀함수 실행
		system("Pause");
		printMaze(maze);
		printf(NEXTMOVE);
	}


	if (y == startY && x == startX){                 // 시작지점에 되돌아 왔으면 종료하기

		printMaze(maze);
		printf(FAILURE);
		return;

	}

}
void MAZE_INPUT_ZEROS(void) {                            //랜덤으로 경로를 만드는 함수

	int i, j;


	srand(3);                                 // seed값 설정

	for (i = 0; i < 12; i++) {                // 랜덤으로 0 삽입
		for (j = 0; j < 12; j++)
			maze[i][j] = rand() % 2 + '0';
	}

	for (int i = 0; i < 12; i++) {            // 가장자리(벽)
		maze[i][0] = '1';
		maze[i][11] = '1';
		maze[0][i] = '1';
		maze[11][i] = '1';
	}

	int num = 0;

	for (i = 0; i < 12; i++)                   // 0의 개수 검사
	{
		for (j = 0; j < 12; j++)
		{
			if (maze[i][j] == '0')
				num++;
		}
	}

	if (num > POSSIBLE_ZEROS)                  //0의 개수가 100개 이하인지 검사. 100개가 넘으면 재실행
		return MAZE_INPUT_ZEROS();


	return;
}
void Coord_XY(void) {                             // 랜덤으로 시작지점과 도착지점을 만드는 함수

	srand(2);                                     //seed값 설정

	int i[2];
	for (int k = 0; k < 2; k++) {
		i[k] = rand() % 12;
	}

	startexit[0] = i[0];
	startexit[1] = i[1];


	int flag1 = rand() % 4 + 1;
	int flag2 = rand() % 4 + 1;

	while (flag1 == flag2)                        // 서로다른 edge에서 입구와 출구 정해주기
		flag2 = rand() % 4 + 1;

	S = flag1;

	switch (flag1)                                // 시작지점 선정
	{
	case 1: maze[startexit[0]][0] = '0';
		startX = 0;
		startY = startexit[0];
		break;
	case 2: maze[startexit[0]][11] = '0';
		startX = 11;
		startY = startexit[0];
		break;
	case 3: maze[0][startexit[0]] = '0';
		startX = startexit[0];
		startY = 0;
		break;
	case 4: maze[11][startexit[0]] = '0';
		startX = startexit[0];
		startY = 11;
		break;
	default:
		break;
	}

	switch (flag2)                                // 출구지점 선정
	{
	case 1: maze[startexit[1]][0] = '0';
		endX = 0;
		endY = startexit[1];
		break;
	case 2: maze[startexit[1]][11] = '0';
		endX = 11;
		endY = startexit[1];
		break;
	case 3: maze[0][startexit[1]] = '0';
		endX = startexit[1];
		endY = 0;
		break;
	case 4: maze[11][startexit[1]] = '0';
		endX = startexit[1];
		endY = 11;
		break;
	default:
		break;
	}


	return;

}
void Initialize_Maze(void){                             // 1's 로 초기화 된 미로   

	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++)
			maze[i][j] = '1';
	}

}
