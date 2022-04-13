#include <iostream>
#include <fstream>
#include <string>

struct mazenode {
	int x;
	int y;
	bool junc;
	int dir;
	mazenode* next;
	mazenode(int x, int y, bool junc, int dir);
};

int main()
{
	std::ifstream mfile("maze.txt");
	std::string ns, row;
	std::getline(mfile, ns);
	int m = 1, n = (ns.length() + 1) / 2, i, j;
	while (!mfile.eof())
	{
		std::getline(mfile, ns);
		m++;
	}
	mfile.seekg(0, std::ios::beg);
	int** maze = new int*[m];
	for (i = 0; i < m; i++)
		maze[i] = new int[n];
	i = 0;
	while (!mfile.eof()) {
		j = 0;
		std::getline(mfile, row);
		while (j < n) {
			std::string el = "";
			maze[i][j] = std::stoi(el += row[2 * j]);
			j++;
		}
		i++;
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			std::cout << maze[i][j] << " ";
		}
		std::cout << std::endl;
	}

	mazenode* MTop = new mazenode(0, 0, 0, 0);
	mazenode* MBottom = new mazenode(0, 0, 0,0);
	mazenode* iter;
	i = 0;
	j = 0;
	bool exitfound = false;
	int dir = 0; //0 - вправо, 1 - вниз, 2 - вліво, 3 - вгору
	int c = 0; //якщо цей показник більше 0, то з даної клітинки можна пройти більше, ніж однією дорогою,
	//і поле junc для клітинки стає true
	while (!exitfound) {
		for (int k = 0; k < 3; k++) {
			if (!k && maze[i][j + 1])
				c++;
			else if (k == 1 && maze[i + 1][j])
				c++;
			else if (k == 2 && maze[i][j - 1])
				c++;
			else if (k == 3 && maze[i -1][j])
				c++;
		}
		if (c)
			MTop->junc = true;
		switch (dir) {
		case 0:
			if (maze[i][j + 1])
			{
				if (MTop->junc && MTop->dir > 0) {
					dir++;
				}
				else {
					mazenode* Node = new mazenode(i, j + 1, 0, 0);
					Node->next = MTop;
					MTop = Node;
					j++;
					dir = 0;
				}
			}
			else
				dir++;
			break;
		case 1:
			if (maze[i+1][j])
			{
				if (MTop->junc && MTop->dir > 1) {
					dir++;
				}
				else {
					mazenode* Node = new mazenode(i + 1, j, 0, 0);
					Node->next = MTop;
					MTop = Node;
					i++;
					dir = 0;
				}
			}
			else
				dir++;
			break;
		case 2:
			if (maze[i][j-1])
			{
				if (MTop->junc && MTop->dir > 2) {
					dir++;
				}
				else {
					mazenode* Node = new mazenode(i, j - 1, 0, 0);
					Node->next = MTop;
					MTop = Node;
					j--;
					dir = 0;
				}
			}
			else
				dir++;
			break;
		case 3:
			if (maze[i-1][j])
			{
				mazenode* Node = new mazenode(i-1, j, 0, 0);
				Node->next = MTop;
				MTop = Node;
				i--;
				dir = 0;
			}
			else
				dir++;
			break;
		case 4:
			iter = MTop;
			while (iter) {
				if (iter->junc)
				{
					MTop = iter;
					i = MTop->x;
					j = MTop->y;
					MTop->dir++;
					break;
				}
				iter = iter->next;
			}
			break;
		}
		if (i == m - 1 && j == n - 1)
			exitfound = true;
	}
	iter = MTop;
	int k = 0;
	while (iter) {
		k++;
		iter = iter->next;
	}
	std::string* result = new std::string[k];
	iter = MTop;
	for (i = 0; i < k; i++) { 
		result[i] = '(' + iter->x +',' + ' ' + iter->y + ')';
		iter = iter->next;
	}
	for (i = 0; i < k; k++) {
		std::cout << result[k - i - 1] << std::endl;
	}
	//while (MSt) {

	//}
	return 0;
}