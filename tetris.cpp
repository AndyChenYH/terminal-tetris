#include <bits/stdc++.h> 
#include <unistd.h>
#include <ncurses.h>
using namespace std; 

const int MR = 22, MC = 10, MB = 7, dropi = 0, dropj = 3;
bool mb[MR][MC], screen[MR][MC + 20];
// list of rotation of pieces
vector<vector<vector<int>>> bks[MB];
bool bd(int i, int j) {
	return 0 <= i && i < MR && 0 <= j && j < MC;
}
bool collide(int ci, int cj, int cb, int cr) {
	for (int i = 0; i < 4; i ++) {
		for (int j = 0; j < 4; j ++) {
			if (bks[cb][cr][i][j]) {
				if (!bd(ci + i, cj + j)) {
					return true;
				}
				else if (mb[ci + i][cj + j]) {
					return true;
				}
			}
		}
	}
	return false;
}
void setup() {
	mb[MR - 2][0] = mb[MR - 1][0] = mb[MR - 1][1] = true;

	bks[0] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
		}
	};
	bks[1] = {
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
		}
	};
	bks[2] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
		}
	};

	bks[3] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
		},
	};
	bks[4] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		}
	};
	bks[5] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 0, 0},
		}
	};
	bks[6] = {
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
		},
	};
}
void clear(int li) {
	for (int i = li; 1 <= i; i --) {
		for (int j = 0; j < MC; j ++) {
			mb[i][j] = mb[i - 1][j];
			mb[i - 1][j] = 0;
		}
	}
}
int main() {
	// ncurses stuff
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	setup();
	srand(time(0));
	int ci = dropi, cj = dropj, cb = rand() % MB, cr = 0;
	int frame = 0;
	int next = rand() % MB;
	int pt = 0;
	bool pause = false;
	int offi = 1, offj = 1;
	while (true) {
		usleep(1000);
		clear();
		memset(screen, false, sizeof(screen));
		for (int i = 0; i < 4; i ++) {
			for (int j = 0; j < 4; j ++) {
				if (bd(ci + i, cj + j)) {
					screen[ci + i][cj + j] |= bks[cb][cr][i][j];
				}
			}
		}
		for (int i = 0; i < MR; i ++) {
			for (int j = 0; j < MC; j ++) {
				char cc;
				if (mb[i][j] || screen[i][j]) cc = '#';
				else cc = ' ';
				mvaddch(i + offi, j * 2 + offj, cc);
			}
		}
		mvaddstr(5, 22, "next: ");
		for (int i = 0; i < 4; i ++) {
			for (int j = 0; j < 4; j ++) {
				if (bks[next][0][i][j]) {
					mvaddch(i + 5 + offi, j * 2 + 22 + offj, '#');
				}
			}
		}
		// drawing border
		for (int i = 0; i < MR; i ++) {
			mvaddch(i, 0, '.');
			mvaddch(i, MC * 2, '.');
		}
		for (int j = 0; j < MC; j ++) {
			mvaddch(0, j * 2, '.');
			mvaddch(MR, j * 2, '.');
		}


		char ss[50];
		sprintf(ss, "points: %d", pt);
		mvaddstr(12, 22, ss);

		char inp = getch();
		if (inp == 'p') pause = !pause;
		if (pause) continue;

		if (inp == ',' && !collide(ci, cj - 1, cb, cr)) {
			cj --;
		}
		else if (inp == '/' && !collide(ci, cj + 1, cb, cr)) {
			cj ++;
		}
		else if (inp == '.' && !collide(ci + 1, cj, cb, cr)) {
			ci ++;
		}
		else if (inp == 'x') {
			int ncr = (cr + 1) % bks[cb].size();
			if(!collide(ci, cj, cb, ncr)) {
				cr = ncr;
			}
		}
		else if (inp == 'z') {
			auto mod = [&] (int a, int b) {
				int r = a % b;
				return r < 0 ? r + b : r;
			};
			int ncr = mod(cr - 1, bks[cb].size());
			if(!collide(ci, cj, cb, ncr)) {
				cr = ncr;
			}

		}
		else if (inp == ' ') {
			while (!collide(ci + 1, cj, cb, cr)) {
				ci ++;
			}
			frame = 500;
		}

		if (frame % 500 == 0) {
			if (collide(ci + 1, cj, cb, cr)) {
				for (int i = 0; i < 4; i ++) {
					for (int j = 0; j < 4; j ++) {
						if (bks[cb][cr][i][j]) mb[ci + i][cj + j] = true;
					}
				}
				int ct = 0;
				for (int i = MR - 1; 0 <= i; i --) {
					for (int j = 0; j < MC; j ++) {
						if (!mb[i][j]) {
							goto L1;
						}
					}
					clear(i);
					ct ++;
					i ++;
L1:;
				}
				pt += ct * ct;
				ci = dropi, cj = dropj;
				cb = next;
				next = rand() % MB;
				cr = 0;
				if (collide(ci, cj, cb, cr)) {
					endwin();
					puts("you lose!");
					printf("final score: %d\n", pt);
					exit(0);
				}
			}
			else ci ++;
			frame = 0;
		}
		frame ++;
	}
	return 0;
}
