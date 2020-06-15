#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>

const int BOARD_DIMENSION = 8;
const int SIMPLE_GUARDS = 3;
const int SCOUTS = 0;
const int KNIGHTS = 2;
const int DEFENDERS = 2;
const int HERALDS = 2;
const char DIRECTIONS[] = { 'w', 'a', 's', 'd' };

int currentTurn = 0;



void initializeMatrix(char (&m)[BOARD_DIMENSION][BOARD_DIMENSION]) {
	for (int i = 0; i != BOARD_DIMENSION; i++) {
		for (int j = 0; j != BOARD_DIMENSION; j++) {
			m[i][j] = ' ';
		}
	}
}

void printMatrix(char(&m)[BOARD_DIMENSION][BOARD_DIMENSION]) {
	for (int i = 0; i != BOARD_DIMENSION; i++) {
		std::cout << "|";
		for (int j = 0; j != BOARD_DIMENSION; j++) {
			std::cout<<m[i][j] << "|";
		}
		std::cout << std::endl;
	}
}


class Character {
public:
	int x, y, slowedTurns;
	char letter;
	Character() {
		x = slowedTurns = 0;
		y = BOARD_DIMENSION - 1;
		letter = 'P';
	}
	void onMove(char input) {
		if (slowedTurns == 0) {
			switch (input)
			{
			case 'w':
				if (y > 0)
					y--;
				break;
			case 's':
				if (y < BOARD_DIMENSION - 1)
					y++;
				break;
			case 'a':
				if (x > 0)
					x--;
				break;
			case 'd':
				if (x < BOARD_DIMENSION - 1)
					x++;
				break;
			default:
				break;
			}
		}
		else {
			std::cout << "\nPlayer is slowed!\n";
			slowedTurns--;
		}
	}

	void placeMine(char board[][BOARD_DIMENSION]) {
		board[this->y][this->x] = 'T';
		x++;
	}
};


class Guard {
public:
	int x, y;
	char letter;

	Guard(int x, int y, char letter) {
		this->x = x;
		this->y = y;
		this->letter = letter;
	}
	virtual void onMove(char(&m)[BOARD_DIMENSION][BOARD_DIMENSION], Character& p) {}
};

class SimpleGuard : public Guard {
public:
	SimpleGuard(int x, int y, char letter) : Guard(x, y, letter) {
	}

	void onMove(char(&m)[BOARD_DIMENSION][BOARD_DIMENSION], Character& p)override {
		bool ok = false;
		while (!ok) {
			ok = true;
			char dir = DIRECTIONS[rand() % 4];
			switch (dir)
			{
			case 'w':
				if (y > 0 && m[x][y - 1] == ' ')
					y--;
				else if (y > 0)
					ok = false;
				else if (m[x][y - 1] != 'P') {
					//Apply guard effects
					p.slowedTurns++;
					std::cout << "\nPlayer got slowed\n";
					system("pause");
				}
				else {
					//Collision with another guard
				}
				break;
			case 's':
				if (y < BOARD_DIMENSION - 1 && m[x][y + 1] == ' ')
					y++;
				else if (y < BOARD_DIMENSION - 1)
					ok = false;
				else if (m[x][y + 1] != 'P') {
					//Apply guard effects
					p.slowedTurns++;
					std::cout << "\nPlayer got slowed\n";
					system("pause");
				}
				else {
					//Collision with another guard
				}
				break;
			case 'a':
				if (x > 0 && m[x - 1][y])
					x--;
				else if (x > 0)
					ok = false;
				else if (m[x - 1][y] != 'P') {
					//Apply guard effects
					p.slowedTurns++;
					std::cout << "\nPlayer got slowed\n";
					system("pause");
				}
				else {
					//Collision with another guard
				}
				break;
			case 'd':
				if (x < BOARD_DIMENSION - 1 && m[x + 1][y] == ' ')
					x++;
				else if (x < BOARD_DIMENSION - 1)
					ok = false;
				else if (m[x + 1][y] != 'P') {
					//Apply guard effects
					p.slowedTurns++;
					std::cout << "\nPlayer got slowed\n";
					system("pause");
				}
				else {
					//Collision with another guard
				}
				break;
			default:
				break;
			}
		}
	}
};



class Scout : public Guard {
public:
	Scout(int x, int y, char letter) : Guard(x, y, letter) {
	}

	void onMove(char(&m)[BOARD_DIMENSION][BOARD_DIMENSION], Character& p)override {
		bool ok = false;
		while (!ok) {
			ok = true;
			char dir = DIRECTIONS[rand() % 4];
			switch (dir)
			{
			case 'w':
				if (y > 0)
					y -= 2;
				else
					ok = false;
				break;
			case 's':
				if (y < BOARD_DIMENSION - 1)
					y += 2;
				else
					ok = false;
				break;
			case 'a':
				if (x > 0)
					x -= 2;
				else
					ok = false;
				break;
			case 'd':
				if (x < BOARD_DIMENSION - 1)
					x += 2;
				else
					ok = false;
				break;
			default:
				break;
			}
		}
	}
};
/*
class Cavaliere : public Guard {
public:
	Cavaliere(int x, int y) {
		super(x, y);
	}

	void onMove()override {
		char dir = random tra w, a, s, d;
		Check che non vada fuori
			switch (dir)
			{
			case 'w':
				y--;
				break;
			case 'a':
				y++;
				break;
			case 's':
				x--;
				break;
			case 'd':
				x++;
				break;
			default:
				break;
			}
	}
};
class Difensore : public Guard {
public:
	int turnoUltimoMovimento = -2;
	Difensore(int x, int y) {
		super(x, y);
	}

	void onMove(int turnoAttuale)override {
		if (turnoAttuale - turnoUltimoMovimento > 1) {
			turnoUltimoMovimento = turnoAttuale;
			char dir = random tra w, a, s, d;
			Check che non vada fuori
				switch (dir)
				{
				case 'w':
					y--;
					break;
				case 'a':
					y++;
					break;
				case 's':
					x--;
					break;
				case 'd':
					x++;
					break;
				default:
					break;
				}
		}
	}
};
class Araldo : public Guard {
public:
	Araldo(int x, int y) {
		super(x, y);
	}

	void onMove()override {
		int spostamentoX = random - 1 o 1;
		int spostamentoY = random - 1 o 1;

		x += spostamentoX;
		y += spostamentoY;
	}
};

*/

using namespace std;



int main() {
	bool prisoned = false;
	bool won = false;
	char m[BOARD_DIMENSION][BOARD_DIMENSION];

	Character* player;
	vector<Guard*> guards;
	vector<Guard*>::iterator it;

	srand(time(NULL));

	initializeMatrix(m);

	player = new Character();

	//use functors?
	for (int i = 0; i != SIMPLE_GUARDS; i++) {
		int tempX = rand() % 7;
		int tempY = rand() % 7;
		if (m[tempY][tempX] == ' ')
			guards.push_back(new SimpleGuard(tempX, tempY, 'G'));
		else
			i--;
	}

	for (int i = 0; i != SCOUTS; i++) {
		int tempX = rand() % 7;
		int tempY = rand() % 7;
		if (m[tempY][tempX] == ' ')
			guards.push_back(new Scout(tempX, tempY, 'S'));
		else
			i--;
	}

	//Game loop
	while (!prisoned && !won) {
		currentTurn++;
		system("CLS");

		m[player->y][player->x] = 'P';
		
		vector<Guard*>::iterator end = guards.end();
		for (vector<Guard*>::iterator it = guards.begin(); it != end; it++) {
			m[(*it)->y][(*it)->x] = (*it)->letter;
		}

		printMatrix(m);
		char input;
		cin >> input;


		m[player->y][player->x] = ' ';
			for (it = guards.begin(); it != end; it++) {
			m[(*it)->y][(*it)->x] = ' ';
		}


		if (input == 't')
			player->placeMine(m);
		else
			player->onMove(input);
		it = guards.begin();

		for (vector<Guard*>::iterator it = guards.begin(); it != end; it++) {
			(*it)->onMove(m, *player);
		}

		if (player->x == BOARD_DIMENSION-1 && player->y == 0)
			won = true;
	}
	if (won) {
		system("CLS");
		cout << "You won!";
	}
	else
		cout << "You lost!";
	cout << endl << endl << endl << endl << endl;
	delete player;
		/*

		if (personaggio.posizione = posizione arrivo)
			won = true;
		else {
			//muovi le guardie e fai i vari controlli
		}

	}*/
}