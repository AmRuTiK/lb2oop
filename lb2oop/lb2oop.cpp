#include<iostream>
#include<conio.h>
using namespace std;

class Rectangle { //статический объект
protected:
	int x, y;
public:
	Rectangle() {
		cout << "Rectangle() запуск конструктора" << endl;
		x = 0;
		y = 0;
	}
	Rectangle(int x, int y) {
		printf("Rectangle(%d,%d) запуск конструктора с параметром\n",x,y);
		this->x = x;
		this->y = y;
	}
	Rectangle(const Rectangle& s) {
		printf("Rectangle() запуск конструктора копирования\n");
		x = s.x;
		y = s.y;
	}
	~Rectangle() {
		printf("~Rectangle(%d, %d) запуск деструктора\n", x, y);
		/*cout << x << " " << y;
		cout << " ~Rectangle() запуск деструктора" << endl;*/
	}

	void move(int dx, int dy) {//метод объекта, определяется сразу
		cout << " " << endl << endl;
		printf("move(int dx, int dy)\n");
		x = x + dx;
		y = y + dy;
	}
	int getx() {
		return x;
	}
	int gety() {
		return y;
	}

	void after();//метод объекта, определяется позже
};
void Rectangle::after() {

	printf("after()\n");
	x = 12;
	y = 8;
}

class ColoredRectangle :public Rectangle {//динамический объект(наследственный)
protected:
	int a;
public:
	ColoredRectangle() :Rectangle() {
		cout << "ColoredRectangle() запуск конструктора" << endl;
		a = 0;
	}
	ColoredRectangle(int x, int y, int a) :Rectangle(x, y) {
		printf("ColoredRectangle(%d,%d) запуск конструктора с параметром\n",x,y,a);
		this->a = a;
	}
	ColoredRectangle(const ColoredRectangle& s) {
		cout << "ColoredRectangle() запуск конструктора копирования" << endl;
		x = s.x;
		y = s.y;
		a = s.a;
	}
	~ColoredRectangle() {
		printf("~ColoredRectangle(%d, %d, %d) запуск деструктора\n", x, y, a);
		/*cout << x << " " << y << " " << a ;
		cout << " ~ColoredRectangle() запуск деструктора" << endl;*/
	}
};

class Parall {//композиция
protected:
	Rectangle s, * s2;
public:
	Parall() {
		cout << "Parall() запуск конструктора" << endl;
		s = Rectangle();
		s2 = new Rectangle();
	}
	Parall(int x, int y, int x1, int y1) {
		printf("Parall(%d,%d,%d,%d) запуск конструктора с параметром\n",x,y,x1,y1);
		s = Rectangle(x, y);
		s2 = new Rectangle(x1, y1);
	}
	Parall(const Parall& p) {
		cout << "Parall() запуск конструктора копирования" << endl;
		s = Rectangle((p.s));
		s2 = new  Rectangle(*(p.s2));
	}
	~Parall() {

		printf("~Parall(%d,%d,%d,%d) запуск деструктора\n", s.getx(), s.gety(), s2->getx(), s2->gety());
		delete s2;
		
	}
};




int main()
{
	setlocale(LC_ALL, "rus");
	{	printf("Rectangle static\n");
	Rectangle s;
	Rectangle s2(5, 9);
	Rectangle s3(s2);
	}
	cout << " " << endl << endl << endl;;
	{
		printf("Rectangle dinamic\n");
		Rectangle* s = new Rectangle;//создание динамических переменных
		Rectangle* s2 = new Rectangle(5, 9);
		Rectangle* s3 = new Rectangle(*s2);

		s->move(5, 1);//запуск методов
		s2->after();
		delete s;//работа деструктора
		delete s2;
		delete s3;
	}
	cout << " " << endl << endl << endl;
	{
		printf("ColoredRectangle dinamik\n");
		ColoredRectangle* s = new ColoredRectangle();
		ColoredRectangle* s1 = new ColoredRectangle(7, 3, 10);
		ColoredRectangle* s2 = new ColoredRectangle(*s1);

		delete s;
		delete s1;
		delete s2;
	}
	cout << " " << endl << endl << endl;;
	{
		printf("Parall dinamic\n");
		Parall* s = new Parall;
		Parall* s2 = new Parall(3, 5, 1, 1);
		Parall* s3 = new Parall(*s2);
		delete s;
		delete s2;
		delete s3;
	}

	_getch();
	return 0;
}