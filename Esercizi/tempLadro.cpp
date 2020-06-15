
class Personaggio {
	int x, y;
	void onMove(char input) {
		Check che non vada fuori
		switch (input)
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

	void piazzaMina(char[][] scacchiera) {
		scacchiera[x][y] = 't';
		x++;
	}
};

class Guardia {
public:
	int x, y;
	Guardia(int x, int y) {
		this->x = x;
		this->y = y;
	}
	virtual void onMove() {}
};

class GuardiaSemplice : public Guardia {
public:
	GuardiaSemplice(int x, int y) {
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

class Vedetta : public Guardia {
public:
	Vedetta(int x, int y) {
		super(x, y);
	}

	void onMove()override {
		char dir = random tra w, a, s, d;
		Check che non vada fuori
			switch (dir)
			{
			case 'w':
				y-=2;
				break;
			case 'a':
				y+=2;
				break;
			case 's':
				x-=2;
				break;
			case 'd':
				x+=2;
				break;
			default:
				break;
			}
	}
	}
};

class Cavaliere : public Guardia {
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
class Difensore : public Guardia {
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
class Araldo : public Guardia {
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


int main() {
	bool prisoned = false;
	bool won = false;
	char m[n][n];
	inizializzaMtuttoZero();
	inserisciGuardie();
	inserisciPersonaggio();
	while (!prisoned && !won) {
		char input;
		cin >> input;
		
		if (input == 't')
			personaggio.piazzaMina(m);
		else
			personaggio.onMove(input);

		if (personaggio.posizione = posizione arrivo)
			won = true;
		else {
			//muovi le guardie e fai i vari controlli
		}

	}
}