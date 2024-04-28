#include "List.h"

int main()
{
	system("chcp 1251");

	List list; //Список

	cin >> list; //Ввод данных в список

	cout << endl;

	cout << list << endl; //Вывод элементов списка

	cout << "На какое число вы хотите увеличить все элементы списка?" << endl;

	int number;

	cin >> number; //Получаем число

	for (int i = 0; i < list(); i++)
		list[i] += number; //Увеличиваем все элементы списка на число

	cout << endl << list << endl; //Выводим список

	//Удаляем первый и последний элемент
	list.Pop_Front();
	list.Pop_Back();

	//Выводим список после изменений
	cout  << endl << "Список после удаления первого и последнего элементов:" << endl << list << endl;

	cout << "Введите число, которое хотите добавить в начало списка: "; cin >> number;

	//Добавляем число в начало и конец списка
	list.Push_Front(number);

	//Выводим список
	cout << endl << list << endl << endl;

	cout << "Возводим список в квадрат:";
	list *= list; //Возводим список в квадрат и выводим
	cout << endl << list << endl << endl;

	Iterator current = list.first(); //Получаем первый элемент списка через итератор

	cout << "Первый элемент списка: " << *current << endl << endl;

	current += (list() - 1); //Получаем последний элемент списка через итератор

	cout << "Последний элемент списка: " << *current << endl;

	if (list.first() != list.last()) //Печатаем список через итераторы, если есть, что печатать
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
