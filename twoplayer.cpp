#include <bits/stdc++.h> 
#include <unistd.h>
#include <ncurses.h>
using namespace std; 

const int MR = 22, MC = 30, MB = 7, MP = 2, hei = 30, wid = 80, offi = 1, offj = 1;
int frame, pt;
bool mb[MR][MC], paused;
char screen[hei][wid];
// list of rotation of pieces
vector<vector<vector<int>>> bks[MB];
class Player;
bool collide(int ci, int cj, int cb, int cr);
vector<Player> ps;
bool bd(int i, int j) {
	return 0 <= i && i < MR && 0 <= j && j < MC;
}
void setup() {
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
class Player {
	public:
	int ci, cj, cb, cr, next, dropi = 0, dropj = 3, drawi, drawj;
	char bleft, bright, bdown, brotl, brotr, bdrop;
	Player() {}
	Player(int dropi, int dropj, int bleft, int bright, int bdown, int brotr, int brotl, int bdrop, int drawi, int drawj) {
		this->dropi = dropi, this->dropj = dropj;
		this->bleft = bleft, this->bright = bright, this->bdown = bdown;
		this->brotl = brotl, this->brotr = brotr, this->bdrop = bdrop;
		this->drawi = drawi, this->drawj = drawj;
		ci = dropi, cj = dropj, cb = rand() % MB, cr = 0;
		next = rand() % MB;
	}
	void draw() {
		for (int i = 0; i < 4; i ++) {
			for (int j = 0; j < 4; j ++) {
				if (bks[cb][cr][i][j]) {
//					assert(bd(ci + i, cj + j));
					screen[offi + ci + i][offj + cj * 2 + j * 2] = '#';
				}
			}
		}
		char ss[50];
		memset(ss, 0, sizeof(ss));
		sprintf(ss, "next: ");
		strcpy(screen[drawi] + drawj, ss);
		for (int i = 0; i < 4; i ++) {
			for (int j = 0; j < 4; j ++) {
				if (bks[next][0][i][j]) {
					screen[i + drawi + offi - 1][j * 2 + drawj + offj] = '#';
				}
			}
		}
	}
	void act(char inp) {

		if (inp == bleft && !collide(ci, cj - 1, cb, cr)) {
			cj --;
		}
		else if (inp == bright && !collide(ci, cj + 1, cb, cr)) {
			cj ++;
		}
		else if (inp == bdown && !collide(ci + 1, cj, cb, cr)) {
			ci ++;
		}
		else if (inp == brotr) {
			int ncr = (cr + 1) % bks[cb].size();
			if(!collide(ci, cj, cb, ncr)) {
				cr = ncr;
			}
		}
		else if (inp == brotl) {
			auto mod = [&] (int a, int b) {
				int r = a % b;
				return r < 0 ? r + b : r;
			};
			int ncr = mod(cr - 1, bks[cb].size());
			if(!collide(ci, cj, cb, ncr)) {
				cr = ncr;
			}

		}
		else if (inp == bdrop) {
			while (!collide(ci + 1, cj, cb, cr)) {
				ci ++;
			}
			frame = 500;
		}
	}
	void down() {
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
	}
};

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
int main() {

	srand(time(0));
	setup();
	frame = 0;
	pt = 0;
	paused = false;
	ps = vector<Player>(MP);
	ps[0] = Player(0, 8, 'k', ';', 'l', 's', 'a', 'd', 23, 18);
	ps[1] = Player(0, 20, ',', '/', '.', 'x', 'z', ' ', 23, 40);
	puts("Instructions:");
	int pc = 1;
	for (Player p : ps) {
		printf("player %d:\n"
				"'%c' to go left, '%c' to go right\n"
				"'%c' to rotate clockwise, '%c' to rotate counterclockwise\n"
				"'%c' to soft drop, '%c' to hard drop\n\n",
				pc, p.bleft, p.bright, p.brotr, p.brotl, p.bdown, p.bdrop);
		pc ++;
	}
	puts("Press enter to continue...");
	char hihi;
	scanf("%c", &hihi);

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
			
	while (true) {
		usleep(1000);
		memset(screen, ' ', sizeof(screen));
		for (Player &p : ps) {
			p.draw();
		}
		for (int i = 0; i < MR; i ++) {
			for (int j = 0; j < MC; j ++) {
				if (mb[i][j]) screen[offi + i][offj + j * 2] = '#';
			}
		}
		// drawing border
		for (int i = 0; i < MR; i ++) {
			screen[i][0] = screen[i][MC * 2] = '.';
		}
		for (int j = 0; j < MC; j ++) {
			screen[0][j * 2] = screen[MR][j * 2] = '.';
		}
		char ss[50];
		sprintf(ss, "points: %d", pt);
		strcpy(screen[16] + 65, ss);

		// loading drawing to ncurses
		for (int i = 0; i < hei; i ++) {
			for (int j = 0; j < wid; j ++) {
				if (screen[i][j] != 0) mvaddch(i, j, screen[i][j]);
			}
		}

		char inp = getch();
		if (inp == 'p') paused = !paused;
		if (paused) continue;
		for (Player &p : ps) {
			p.act(inp);
			p.down();
		}
		frame ++;
	}
	return 0;
}

