#pragma once

#include <iostream>

using namespace std;

struct Node 
{
	Node* next = nullptr;
	Node* prev = nullptr;
	int Data;
};

class Iterator
{
public:

    friend class List;

    Iterator() { Element = nullptr; }

    Iterator& operator=(Iterator& anotherIterator) 
    {
        Element = anotherIterator.Element;
        return *this;
    }

    bool operator==(Iterator& anotherIterator)
    {
        return Element == anotherIterator.Element;
    }

    bool operator!=(Iterator& anotherIterator)
    {
        return Element != anotherIterator.Element;
    }

    Iterator& operator+=(int number)
    {
        for (int i = 0; i < number && Element != nullptr; i++)
            Element = Element->next;

        return *this;
    }

    Iterator& operator-=(int number)
    {
        for (int i = 0; i < number && Element != nullptr; i++)
            Element = Element->prev;

        return *this;
    }

    Iterator& operator++() 
    {
        if (Element != nullptr)
            Element = Element->next;

        return *this;
    }

    Iterator& operator--()
    {
        if (Element != nullptr)
            Element = Element->prev;

        return *this;
    }

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

    int& operator*() { return Element->Data; }

private:
    Node* Element;
};


class List
{
public:

    List() { head = nullptr, tail = nullptr, Lenght = 0, beg.Element = head, end.Element = tail; }

    ~List() { Clear(); }

    Iterator& first() { return beg; }

    Iterator& last() { return end; }

    void Push_Back(int element)
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

    void Push_Front(int element)
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

    void Pop_Back() 
    {
        if (head == nullptr)
        {
            cout << "������ ����. ������ �������!" << endl;
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

    void Pop_Front()
    {
        if (head == nullptr)
        {
            cout << "������ ����. ������ �������!" << endl;
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

    int& operator[](int index)
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

    List& operator=(List& anotherList)
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

    int operator()() { return Lenght; }

    List operator*(List& anotherList)
    {
        int SmallerLenght = (anotherList.Lenght > Lenght) ? Lenght : anotherList.Lenght;

        List temp;

        for (int i = 0; i < SmallerLenght; i++)
            temp[i] = (*this)[i] * anotherList[i];

        return temp;
    }

    void Clear()
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

    friend istream& operator>>(istream& stream, List& list);

    friend ostream& operator<<(ostream& stream, List& list);

private:

	Node* head;
	Node* tail;

    Iterator beg;
    Iterator end;

	int Lenght;
};

istream& operator>>(istream& stream, List& list) 
{
    list.Clear();

    int Lenght;

    cout << "������� ����� ������: "; stream >> Lenght;

    for (int i = 0; i < Lenght; i++)
    {
        int data;
        cout << "������� ������: "; stream >> data;
        list.Push_Back(data);
    }

    return stream;
}

ostream& operator<<(ostream& stream, List& list)
{
    if (list.Lenght == 0)
    {
        stream << "������ ������!";
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

