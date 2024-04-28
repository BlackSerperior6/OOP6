#pragma once

#include <iostream>

using namespace std;

struct Node //Структура элемента списка
{
	Node* next = nullptr; //Указатель на следующий элемент
	Node* prev = nullptr; //Указатель на предыдущий элемент
	int Data; //Данные элемента
};

class Iterator //Класс итератор
{
public:

    friend class List; //Делаем класс списка другом класса итератора

    Iterator() { Element = nullptr; } //Конструктор

    Iterator& operator=(Iterator& anotherIterator)  //Оператор присваивания
    {
        Element = anotherIterator.Element;
        return *this;
    }

    bool operator==(Iterator& anotherIterator) //Оператор сравнения
    {
        return Element == anotherIterator.Element;
    }

    bool operator!=(Iterator& anotherIterator) //Оператор неравенства
    {
        return Element != anotherIterator.Element;
    }

    Iterator& operator+=(int number) //Оператор сложения (сдвиг вперед)
    {
        for (int i = 0; i < number && Element != nullptr; i++)
            Element = Element->next;

        return *this;
    }

    Iterator& operator-=(int number) //Оператор вычитания (сдвиг назад)
    {
        for (int i = 0; i < number && Element != nullptr; i++)
            Element = Element->prev;

        return *this;
    }

    Iterator& operator++()  //Сдвиг вперед на один
    {
        if (Element != nullptr)
            Element = Element->next;

        return *this;
    }

    Iterator& operator--() //Сдвиг назад на один
    {
        if (Element != nullptr)
            Element = Element->prev;

        return *this;
    }

    //Постфиксные варианты
    Iterator operator++(int) 
    {
        Iterator tmp;

        tmp = *this;

        if (Element != nullptr)
            Element = Element->next;

        return tmp;
    }

    Iterator operator--(int)
    {
        Iterator tmp;

        tmp = *this;

        if (Element != nullptr)
            Element = Element->prev;

        return tmp;
    }

    int& operator*() { return Element->Data; } //Оператор разадресации 

private:
    Node* Element; //Элемент списка, хранящийся в итераторе
};


class List
{
public:

    //Конструктор без параметров
    List() { head = nullptr, tail = nullptr, Lenght = 0, beg.Element = head, end.Element = tail; }

    //Диструктор. При уничтожении списка очищается
    ~List() { Clear(); }

    Iterator& first() { return beg; } //Получает первый итератор

    Iterator& last() { return end; } //Получает последний итератор

    void Push_Back(int element) //Метод добавления в конец списка
    {
        Node* new_node = new Node;
        new_node->Data = element;

        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght++;
    }

    void Push_Front(int element) //Метод добавления в начало списка
    {
        Node* new_node = new Node;
        new_node->Data = element;

        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght++;
    }

    void Pop_Back() //Метод удаления последнего элемента списка
    {
        if (head == nullptr)
        {
            cout << "Список пуст. Нечего удалять!" << endl;
            return;
        }

        Node* tmp;

        if (head == tail)
        {
            tmp = head;

            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tmp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete tmp;

        beg.Element = head;
        end.Element = tail;

        Lenght--;
    }

    void Pop_Front() //Метод удаления первого элемента списка
    {
        if (head == nullptr)
        {
            cout << "Список пуст. Нечего удалять!" << endl;
            return;
        }

        if (head == tail)
        {
            Node* tmp = head;

            head = nullptr;
            tail = nullptr;
            delete tmp;
        }
        else
        {
            Node* tmp = head;
            head = head->next;
            head->prev = nullptr;
            delete tmp;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght--;
    }

    int& operator[](int index) //Оператор доступа по индексу
    {
        if (index >= Lenght|| index < 0)
        {
            cout << "Index out of range, must be non negative and less than collection's size!" << endl;
            Clear();
            exit(0);
        }

        Node* current = head;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current->Data;
    }

    List& operator=(List& anotherList) //Оператор присваивания
    {
        if (this != &anotherList)
        {
            Clear();

            Node* current = anotherList.head;

            while (current != nullptr)
            {
                Push_Back(current->Data);
                current = current->next;
            }
        }

        return *this;
    }

    int operator()() { return Lenght; } //Оператор получения размера списка

    List& operator*=(List& anotherList) //Оператор умножения элементов двух списков
    {
        int SmallerLenght = (anotherList.Lenght > Lenght) ? Lenght : anotherList.Lenght;

        for (int i = 0; i < SmallerLenght; i++)
            (*this)[i] *= anotherList[i];

        return *this;
    }

    void Clear() //Метод очистки списка
    {
        while (head != nullptr)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        tail = nullptr;

        Lenght = 0;
    }

    //Операторы потокового ввода вывода
    friend istream& operator>>(istream& stream, List& list);
    friend ostream& operator<<(ostream& stream, List& list);

private:

    //Голова и хвост списка
	Node* head;
	Node* tail;

    //Итераторы начала и конца списка
    Iterator beg;
    Iterator end;

	int Lenght; //Длина списка
};

istream& operator>>(istream& stream, List& list) //Оператор потокового ввода
{
    list.Clear();

    int Lenght;

    cout << "Введите длину списка: "; stream >> Lenght;

    for (int i = 0; i < Lenght; i++)
    {
        int data;
        cout << "Введите данные: "; stream >> data;
        list.Push_Back(data);
    }

    return stream;
}

ostream& operator<<(ostream& stream, List& list) //Оператор потокового вывода
{
    if (list.Lenght == 0)
    {
        stream << "Пустой список!";
    }
    else
    {
        Node* current = list.head;

        stream << current->Data;

        current = current->next;

        while (current != nullptr)
        {
            stream << " " << current->Data;
            current = current->next;
        }
    }

    return stream; 
}