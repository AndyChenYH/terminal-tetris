#include <bits/stdc++.h>
#include <ncurses.h>
using namespace std;

int main() {
	initscr();
	cbreak();
	noecho();
	char a[50] = "hello";
	char b[50] = "xyz";
	strcpy(a + 2, b);
	for (int i = 0; i < 50; i ++) {
		mvaddch(0, i, a[i]);
	}
	getch();
	endwin();
	return 0;
}
