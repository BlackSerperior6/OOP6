#include "List.h"

int main()
{

	system("chcp 1251");

	List list;

	cin >> list;

	cout << endl;

	cout << list << endl;

	cout << "На какое число вы хотите увеличить все элементы списка?" << endl;

	int number;

	cin >> number;

	for (int i = 0; i < list(); i++)
		list[i] += number;

	cout << endl << list << endl;

	list.Pop_Front();
	list.Pop_Back();

	cout  << endl << "Список после удаления первого и последнего элементов:" << endl << list << endl;

	cout << "Введите число, которое хотите добавить в начало списка: "; cin >> number;

	list.Push_Front(number);

	cout << endl << list << endl << endl;

	cout << "Возводим список в квадрат:";
	list *= list;
	cout << endl << list << endl << endl;

	Iterator current = list.first();

	cout << "Первый элемент списка: " << *current << endl << endl;

	current += (list() - 1);

	cout << "Последний элемент списка: " << *current << endl;

	if (list.first() != list.last())
	{
		cout <<  endl << "Печатаем список с лево направо: " << endl;

		current = list.first();

		cout << *current;

		current++;

		for (; current != list.last(); current++)
			cout << " " << *current;

		cout << " " << *list.last();

		cout << endl << endl << "Печатаем список с права налево:" << endl;

		current = list.last();

		cout << *current;

		current--;

		for (; current != list.first(); current--)
			cout << " " << *current;

		cout << " " << *list.first() << endl;
	}
}
