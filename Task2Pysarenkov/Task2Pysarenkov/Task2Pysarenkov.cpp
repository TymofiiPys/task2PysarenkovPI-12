#include <iostream>
#include <fstream>
#include <string>

struct mazenode {
	int x;
	int y;
	bool junc;
	mazenode* next;
	mazenode(int x, int y, bool junc) {
		this->x = x;
		this->y = y;
		this->junc = junc;
		this->next = nullptr;
	};
};

struct coords {
	int x;
	int y;
	coords* next;
	coords(int x, int y) {
		this->x = x;
		this->y = y;
	}
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

	mazenode* MTop = new mazenode(0, 0, 0);
	mazenode* MBottom = new mazenode(0, 0, 0);
	mazenode* iter;
	i = 0;
	j = 0;
	bool exitfound = false;
	int dir = 0; //0 - вправо, 1 - вниз, 2 - вліво, 3 - вгору
	int c = 0; //якщо цей показник більше 0, то з даної клітинки можна пройти більше, ніж однією дорогою,
	//і поле junc для клітинки стає true
	while (!exitfound) {
		c = 0;
		for (int k = 0; k < 4; k++) {
			switch (k)
			{
			case 0:
				if (j < n - 1)
					if (maze[i][j + 1] == 1)
						c++;
				break;
			case 1:
				if (i < m - 1)
					if (maze[i + 1][j] == 1)
						c++;
				break;
			case 2:
				if (j > 0)
					if (maze[i][j - 1] == 1)
						c++;
				break;
			case 3:
				if (i > 0)
					if (maze[i - 1][j] == 1)
						c++;
				break;
			}
		}
		if (c > 1)
			MTop->junc = true;
		else if (c == 0) {
			iter = MTop;
			while (iter) {
				if (iter->junc)
				{
					MTop = iter;
					i = MTop->x;
					j = MTop->y;
					break;
				}
				iter = iter->next;
			}
		}
		if (c > 0)
			switch (dir) {
			case 0:
				if (j < n - 1)
				{
					if (maze[i][j + 1] == 1)
					{
						mazenode* Node = new mazenode(i, j + 1, 0);
						maze[i][j] = 0;//позначаємо дану клітинку як закриту для унеможливлення повернення на неї (якщо поле junc для
						//клітинки false)
						Node->next = MTop;
						MTop = Node;
						j++;
						dir = 0;
					}
					else
						dir++;
				}
				else
					dir++;
				break;
			case 1:
				if (i < m - 1) {
					if (maze[i + 1][j] == 1)
					{
						mazenode* Node = new mazenode(i + 1, j, 0);
						maze[i][j] = 0;
						Node->next = MTop;
						MTop = Node;
						i++;
						dir = 0;
					}
					else
						dir++;
				}
				else
					dir++;
				break;
			case 2:
				if (j > 0) {
					if (maze[i][j - 1] == 1)
					{
						mazenode* Node = new mazenode(i, j - 1, 0);
						maze[i][j] = 0;
						Node->next = MTop;
						MTop = Node;
						j--;
						dir = 0;
					}
					else
						dir++;
				}
				else
					dir++;
				break;
			case 3:
				if (i > 0) {
					if (maze[i - 1][j] == 1)
					{
						mazenode* Node = new mazenode(i - 1, j, 0);
						maze[i][j] = 0;
						Node->next = MTop;
						MTop = Node;
						i--;
						dir = 0;
					}
					else
						dir++;
				}
				else
					dir++;
				break;
				/*case 4:
					iter = MTop;
					while (iter) {
						if (iter->junc)
						{
							MTop = iter;
							i = MTop->x;
							j = MTop->y;
							break;
						}
						iter = iter->next;
					}
					break;*/
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

	//std::string* result = new std::string[k];
	//coords* co = new coords[k];
	//int *xx = new int[k];
	//int *yy = new int[k];
	coords* head = nullptr;
	coords* tail = nullptr;
	iter = MTop;
	for (i = 0; i < k; i++) {
		coords* Node = new coords(iter->y, iter->x);
		if (!tail)
		{
			head = Node;
			tail = Node;
		}
		else {
			Node->next = head;
			head = Node;
		}
		/*xx[i] = iter->x;
		yy[i] = iter->y;*/
		//result[i] = "(" + std::to_string(iter->x) + ", " + std::to_string(iter->y) + ")";
		iter = iter->next;
	}
	coords *citer = head;
	for (i = 0; i < k; i++) {
		std::cout << "(" + std::to_string(citer->x) + ", " + std::to_string(citer->y) + ")" << std::endl;
		citer = citer->next;
	}
	//while (MSt) {

	//}
	delete MTop;
	return 0;
}