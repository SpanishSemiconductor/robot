#include <iostream>
#include <ctime>
#include <iomanip>
const unsigned int MAPA_SZER = 40;
const unsigned int MAPA_WYS = 20;
const unsigned int SEGMENT_SIZE = 5;
using namespace std;
struct vertexStruct {
	int value;
	vertexStruct* next;
};
struct queueStruct {
	vertexStruct* front;
	vertexStruct* rear;
};
bool isEmpty(queueStruct* queue) {
	if (queue->front == nullptr) return true;
	else return false;

}
void enqueue(queueStruct* queue, vertexStruct* vertex) {
	vertexStruct* temp = new vertexStruct;
	temp->value = vertex->value;
	temp->next = nullptr;
	if (isEmpty(queue)) {
		queue->front = temp;
		queue->rear = temp;
	}
	else {
		queue->rear->next = temp;
		queue->rear = temp;
	}
}
void dequeue(queueStruct* queue) {
	vertexStruct* temp = queue->front;
	queue->front = queue->front->next;
	if (queue->front == nullptr) {
		queue->rear = nullptr;
	}
	delete temp;
}
void printQueue(queueStruct* queue) {
	if (isEmpty(queue)) return;
	vertexStruct* temp = new vertexStruct;
	temp = queue->front;
	while (temp != nullptr) {
		cout << temp << " ";
		temp = temp->next;
	}
}
void wpiszDoMapy(int n, int m, int (*tablicaSegmentow[6])[SEGMENT_SIZE], int mapa[MAPA_WYS][MAPA_SZER]) {
	int losowa = rand() % 6;


	for (int i = 0; i < SEGMENT_SIZE; i++) {
		for (int j = 0; j < SEGMENT_SIZE; j++) {
			mapa[i + n][j + m] = tablicaSegmentow[losowa][i][j];
		}
	}

}
void printMapa(int mapa[MAPA_WYS][MAPA_SZER]) {
	for (int i = 0; i < MAPA_WYS; i++) {
		if (i > 9)cout << i << " ";
		else cout << i << "  ";
		for (int j = 0; j < MAPA_SZER; j++) {
			cout << setw(3) << mapa[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "   ";
	for (int j = 0; j < MAPA_SZER; j++) cout << setw(3) << j;
}
void wypiszListeSasiadow(int x, int y, vertexStruct** vertexArray) {
	vertexStruct* p;
	p = vertexArray[y * MAPA_SZER + x];
	cout << "[" << x << "," << y << "]";
	cout << " --> ";
	if (vertexArray[y * MAPA_SZER + x] == nullptr) {
		cout << "Wierzcholek nie istnieje" << endl;
	}
	else if (p->next == nullptr) {
		cout << "Brak sasiadow" << endl;

	}
	else {

		while (p->next != nullptr) {
			//cout << "[" << p->value % MAPA_SZER << "," << (p->value - ((p->value) % MAPA_SZER))/MAPA_WYS<< "] ";
			cout << "[" << p->next->value % MAPA_SZER << ";" << (p->next->value - (p->next->value % MAPA_SZER)) / MAPA_SZER << "] ";
			p = p->next;
		}
	}
}
void bfs(vertexStruct** vertexArray, queueStruct* queue, bool* visited, int liczbaWierzcholkow, int xStart, int yStart, int xEnd, int yEnd) {
	int kroki = 0;
	int licznikZakolejkowanych = 0;
	enqueue(queue, vertexArray[yStart * MAPA_SZER + xStart]);
	queue->rear->value = yStart * MAPA_SZER + xStart;
	*(visited + yStart * MAPA_SZER + xStart) = true;
	vertexStruct* p = vertexArray[yStart * MAPA_SZER + xStart];
	queue->rear->value = yStart * MAPA_SZER + xStart;
	while (!isEmpty(queue)) {
		p = vertexArray[queue->front->value];
		dequeue(queue);
		//if (*(visited + yEnd * MAPA_SZER + xEnd)) return ;
		while (p->next != nullptr) {
			if (!*(visited + p->value)) {
				enqueue(queue, vertexArray[p->value]);
				queue->rear->value = p->value;
				*(visited + p->value) = true;
				licznikZakolejkowanych++;
			}
			p = p->next;


		}
		//if (*(visited + p->value)) continue;
		kroki += 1;
	}
}
void znajdzDroge(vertexStruct** vertexArray, int* distance, bool* visited, int*parent, int xSTart, int yStart, int xEnd, int yEnd ) {
	if (visited[yEnd * MAPA_SZER + xEnd] == false) cout << "brak drogi";
	else {
		vertexStruct* droga = new vertexStruct;
		vertexStruct* poczatek = droga;
		int destination = yEnd * MAPA_SZER + xEnd;
		while (destination != -1) {
			droga->value = destination; 
			destination = parent[destination];
			droga->next = new vertexStruct;
			droga = droga->next;

		}
		droga->next = nullptr;
		while (poczatek->next != nullptr) {
			cout << poczatek->value << " "; 
			poczatek = poczatek->next;
		}
	}
}

void hbfs(vertexStruct** vertexArray, queueStruct* queue, bool* visited, int liczbaWierzcholkow, int xStart, int yStart, int xEnd, int yEnd, int* distance, int* parent) {
	enqueue(queue, vertexArray[yStart * MAPA_SZER + xStart]);
	queue->rear->value = yStart * MAPA_SZER + xStart;
	*(visited + yStart * MAPA_SZER + xStart) = true;
	vertexStruct* p = vertexArray[yStart * MAPA_SZER + xStart];
	queue->rear->value = yStart * MAPA_SZER + xStart;
	distance[yStart * MAPA_SZER + xStart] = 0;
	parent[yStart * MAPA_SZER + xStart] = -1;
	while (!isEmpty(queue)) {
		p = vertexArray[queue->front->next->value]; 
		dequeue(queue);
		//if (visited[yEnd*MAPA_SZER+xEnd]) return distance[yEnd * MAPA_SZER + xEnd];
		while (p->next != nullptr) {
			if  (!visited[p->value]) {
				visited[p->value] = true;
				enqueue(queue, vertexArray[p->value]);
				distance[p->value] = distance[queue->front->value]+1;
				parent[p->value] = parent[queue->front->value];
				queue->rear->value = p->value;

			}
			p = p->next;
		}
	}

}
int main()
{
	srand(time(0));
	int mapa[MAPA_WYS][MAPA_SZER] = {};
	int segmentA[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,0,0},
		{0,1,1,0,0},
		{1,1,0,1,1},
		{0,1,1,1,0},
		{0,0,1,0,0}
	};
	int segmentB[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,1,0},
		{1,0,0,1,0},
		{1,1,1,1,1},
		{0,1,1,1,0},
		{0,0,1,1,0}
	};
	int segmentC[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{1,1,1,1,1},
		{1,1,0,1,1},
		{1,1,0,0,1},
		{0,1,0,0,0},
		{0,1,1,1,1}
	};
	int segmentD[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,1,1},
		{0,1,1,0,1},
		{1,1,0,1,1},
		{1,0,1,1,0},
		{0,1,1,0,0}
	};
	int segmentE[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{1,1,1,0,0},
		{0,1,1,1,0},
		{1,1,0,1,1},
		{1,1,0,1,1},
		{1,1,1,1,0}
	};
	int segmentF[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,1,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}
	};
	int (*tabSegmentow[6])[SEGMENT_SIZE] = { segmentA, segmentB,segmentC, segmentD,segmentE,segmentF };
	for (int j = 0; j < MAPA_WYS - 1; j += 5) {
		for (int i = 0; i < MAPA_SZER - 1; i += 5) {
			wpiszDoMapy(j, i, tabSegmentow, mapa);
		}
	}
	int liczbaWierzcholkow = 0;
	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++)
			if (mapa[i][j] == 1) liczbaWierzcholkow++;
	}
	printMapa(mapa);
	cout << endl;

	vertexStruct** vertexArray = new vertexStruct * [MAPA_WYS*MAPA_SZER];
	bool visited[MAPA_SZER * MAPA_WYS];
	for (int i = 0; i < MAPA_WYS * MAPA_SZER; i++) {
		visited[i] = false;
	}

	//p = new vertexStruct;

			vertexStruct* front = nullptr; 
			vertexStruct* rear = nullptr;
	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++) {
			front = nullptr;
			rear = nullptr;

			if (mapa[i][j] == 0) {
				vertexArray[i * MAPA_SZER + j] = nullptr;
				continue;
			}
			
			if (j > 0&&(mapa[i][j - 1] == 1))  { //sprawdz lewo 
					vertexStruct* p = new vertexStruct;
					p->next = nullptr;
					p->value = i * MAPA_SZER + j - 1;
					if (front == nullptr) {
						front = rear = p;
					}
					else {
						rear->next = p;
						rear = rear->next;
					}
					p = nullptr; 
					delete p;
				
			}
			if (i < MAPA_WYS - 1 && (mapa[i + 1][j] == 1)) { //sprawdz dol 
					vertexStruct* p = new vertexStruct;
					p->next = nullptr;
					p->value = (i + 1) * MAPA_SZER + j;
					if (front == nullptr) {
						front = rear = p;
					}
					else {
						rear->next = p;
						rear = rear->next;
					}
					p = nullptr; 
					delete p;
					

			}
			if (j < MAPA_SZER - 1 && (mapa[i][j + 1] == 1)) {//sprawdz prawo 
					vertexStruct* p = new vertexStruct;
					p->next = nullptr;
					p->value = i * MAPA_SZER + j + 1;
					if (front == nullptr) {
						front = rear = p;
					}
					else {
						rear->next = p;
						rear = rear->next;
					}
					p = nullptr; 
					delete p;
					
				
			}
			if (i > 0 && (mapa[i - 1][j] == 1)) { //sprawdz gore 
					vertexStruct* p = new vertexStruct; 
					p->next = nullptr;
					p->value = (i - 1) * MAPA_SZER + j;
					if (front == nullptr) {
						front = rear = p;
					}
					else {
						rear->next = p;
						rear = rear->next;
					}
					
					
			}
			vertexArray[i * MAPA_SZER + j] = new vertexStruct;
			vertexArray[i * MAPA_SZER + j]->next =front;

			front = nullptr; 

			
		}
	}
	int xStart, yStart, xEnd, yEnd;
	queueStruct* kolejka = new queueStruct;
	kolejka->front = nullptr;
	kolejka->rear = nullptr;

	xStart = rand() % MAPA_SZER;
	yEnd = rand() % MAPA_WYS;
	yStart = rand() % MAPA_WYS;
	xEnd = rand() % MAPA_SZER;
	while (true) {
		xStart = rand() % MAPA_SZER;
		yEnd = rand() % MAPA_WYS;
		yStart = rand() % MAPA_WYS;
		xEnd = rand() % MAPA_SZER;
		if (mapa[yStart][xStart] == 1 && mapa[yEnd][xEnd] == 1) break;
	}


	int* distance = new int[liczbaWierzcholkow];
	int* parent = new int[liczbaWierzcholkow];
	/*while (true) {
		int x, y;
		std::cin >> x >> y;
		wypiszListeSasiadow(x, y, vertexArray);
		char stop = 'c';
		cin >> stop;
		if (stop == 'b') break;
	}*/
	/*int x, y;
	cin >> x >> y;
	enqueue(kolejka, vertexArray[y * MAPA_SZER + x]);
	cin >> x >> y;
	enqueue(kolejka, vertexArray[y * MAPA_SZER + x]);
	dequeue(kolejka);
	printQueue(kolejka);*/


	cout << "Start: [" << xStart << ";" << yStart << "]" << endl;
	cout << "Koniec: [" << xEnd << ";" << yEnd << "]" << endl;
	cout << mapa[yStart][xStart] << endl;
	wypiszListeSasiadow(xStart, yStart,  vertexArray);
	cout << endl;
	wypiszListeSasiadow(xEnd, yEnd,vertexArray);


	/*enqueue(kolejka, vertexArray[yStart * MAPA_SZER + xStart]);
	enqueue(kolejka, vertexArray[yEnd * MAPA_SZER + xEnd]);
	dequeue(kolejka);
	printQueue(kolejka);*/
	//cout << endl; 
	//for (int i = 0; i < MAPA_SZER * MAPA_WYS; i++) {
	//	cout << visited[i];
	//}
	for (int y = 0; y < MAPA_WYS; y++) {
		for (int x = 0; x < MAPA_SZER; x++) {
			wypiszListeSasiadow(x, y, vertexArray);
			cout << endl;
		}
	}
	
	
	hbfs(vertexArray, kolejka, visited, liczbaWierzcholkow, xStart, yStart, xEnd, yEnd, distance, parent);
	//cout << " kontrola";
	//cout << parent[yEnd * MAPA_SZER + xEnd];
	znajdzDroge(vertexArray, distance, visited, parent, xStart, yStart, xEnd, yEnd);
	
	//cout << bfs(vertexArray, kolejka, visited, liczbaWierzcholkow, xStart, yStart, xEnd, yEnd);

}

