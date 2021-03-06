#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct game {
	int apple;
	int snake;
};

game map[101][101];
int n;

int d_x[4] = { 0,1, 0,-1 }; //오른쪽,아래, 왼쪽 위
int d_y[4] = { 1,0,-1,0 };


int main()
{
	int k;
	cin >> n >> k;

	queue < pair<int, int> > snake; //back이 머리 좌표, front가 꼬리
	snake.push(make_pair(1, 1));
	map[1][1].snake = 1;//head 랑 tail다 여기 위치
	int row, col; //x가 열 y가 행
	for (int i = 0; i < k; i++)
	{
		cin >> row; //행  y
		cin >> col;// 열  x
		map[row][col].apple = 1;
	}

	int L; //방향 전환 횟수
	int data;
	char dir;
	cin >> L;
	queue <pair<int, char> > move;
	for (int i = 0; i < L; i++)
	{
		cin >> data;
		cin >> dir;
		move.push(make_pair(data, dir)); //front가 다음 방향 전환
	}

	int answer = 0;
	int dir_now = 0; //시작은 오른쪽

	while (true)
	{
		answer++;
		if ((snake.back().first + d_x[dir_now] > n) || (snake.back().first + d_x[dir_now] < 1) || (map[snake.back().first + d_x[dir_now]][snake.back().second + d_y[dir_now]].snake == 1) ||
			(snake.back().second + d_y[dir_now] > n) || (snake.back().second + d_y[dir_now] < 1)) //머리가 가는장소가 맵 바깥이거나 이미 뱀이 있다면!
		{
			break; //게임 종료
		}


		if (map[snake.back().first + d_x[dir_now]][snake.back().second + d_y[dir_now]].apple == 1)//머리가 간 장소에 사과가 있다면!
		{
			map[snake.back().first + d_x[dir_now]][snake.back().second + d_y[dir_now]].apple = 0;//사과 먹어버리고

			snake.push(make_pair(snake.back().first + d_x[dir_now], snake.back().second + d_y[dir_now])); // 머리 추가!
			map[snake.back().first][snake.back().second].snake = 1; //뱀도 있다 표시!
		}
		else
		{
			snake.push(make_pair(snake.back().first + d_x[dir_now], snake.back().second + d_y[dir_now])); // 머리 추가!
			map[snake.back().first][snake.back().second].snake = 1; //뱀도 있다 표시!
			map[snake.front().first][snake.front().second].snake = 0;
			snake.pop(); //꼬리 치워버리기!
		}

		if (answer == move.front().first)
		{
			if (move.front().second == 'D')
			{
				dir_now++;
				if (dir_now == 4)
					dir_now = 0;
			}
			else
			{
				dir_now--;
				if (dir_now < 0)
					dir_now = 3;
			}
			move.pop();
			if (move.size() == 0)
				move.push(make_pair(0, 'A'));
		}
	}

	cout << answer;
	return 0;
}