#pragma once
#include "Exception.h"
#include "Option.h"

template <typename T>
class Linked_List {
    private:
    //структура узла
        struct Node {
            T value; //данные хранящиеся в узле
            Node* prev; //* на предыдущей узел
            Node* next; //; на следующий узел
            //конструктор узла
            Node(const T& val, Node* p = nullptr, Node* n = nullptr)
            : value(val), prev(p), next(n) {}
        };
        Node* head; //* на первый узел
        Node* tail; //* на последний узел
        int length; //кол-во узлов в списке
        //возвращает указателььна узел по индексу
        Node* getNode(int index) const {
            if (index < 0 ||  index >= length) {
                throw IndexOutOfRangeException();
            }
            Node* cur;
            if (index < length/2) {
                cur = head;
                for (int i = 0; i < index; ++i) {
                    cur = cur->next;
                }
            } else {
                cur = tail;
                for (int i = length - 1; i > index; --i) {
                    cur = cur->prev;
                    }
                }
                return cur;
            }
    public:
    //класс итератора
    class Iterator {
        private:
            Node* current;
        public:
            //принимает * на узел и сохр
            Iterator(Node* node) : current(node) {}
            //возвращает ссылку на значение текущего узла
            T& operator*() {
                return current->value;
            }
            //то же самое для константных
            const T& operator*() const {
                return current->value;
            }
            //сдвигает вперед и возвращает новую позицию
            Iterator& operator++() {
                current = current->next;
                return *this;
            }
            //сдвигает вперед и возвращает старую позицию
            Iterator operator++(int) {
                Iterator temp = *this;
                current = current->next;
                return temp;
            }
            //сравнение:указывают ли на один узел
            bool operator==(const Iterator& other) const {
                return current == other.current;
            }
            //сравнение:не указывают ли на один узел
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }
    };
    //методы Begin() и End()
        Iterator Begin() { return Iterator(head);}
        Iterator End() {return Iterator(nullptr);}
    //базовые операции
        //добавление в конец
        void Append(const T& item) {
            Node* newNode = new Node(item, tail, nullptr);
            if (tail) {
                tail->next = newNode;
            } else {
                head = newNode;
            }
            tail = newNode;
            ++length;
        }
    //добавление в начало
        void Prepend(const T& item) {
            Node* newNode = new Node(item, nullptr, head);
            if (head) {
                head->prev = newNode;
            } else {
                tail = newNode;
            }
            head = newNode;
            ++length;
        }
    //конструкторы
        //по умолчанию
        Linked_List() : head(nullptr), tail(nullptr), length(0) {}
        //из массива в список
        Linked_List(T* items, int count) : head(nullptr), tail(nullptr), length(0) {
            if (count <0 ) throw InvalidArgumentException();
            for (int i=0; i < count; ++i) {
                Append(items[i]);
            }
        }
        //копирующий
        Linked_List(const Linked_List<T>& other) : head(nullptr), tail(nullptr), length(0) {
            Node* cur = other.head;
            while (cur) {
                Append(cur->value);
                cur = cur->next;
            }
        }
        //деструктор
        ~Linked_List() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        //оператор присваивания
        Linked_List<T>& operator=(const Linked_List<T>& other) {
            if (this != &other) {
                while (head) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                head = tail = nullptr;
                length = 0;
                Node* cur = other.head;
                while (cur) {
                    Append(cur->value);
                    cur = cur->next;
                }
            }
            return *this;
        }
        //получение элемента по index
        T& operator[](int index) {
            return  getNode(index)->value;
        }
        //та же самая конст версия
        const T& operator[](int index) const {
            return getNode(index)->value;
        }
    //методы доступа
        //ссылка на знач первого узла
        T& GetFirst() {
            if (!head) throw EmptyStructerException();
            return head->value;
        }
        //ссылка на знач первого узла конст
        const T& GetFirst() const {
            if (!head) throw EmptyStructerException();
            return head->value;
        }
        //ссылка на знач последнего узла
        T& GetLast() {
            if (!tail) throw EmptyStructerException();
            return tail->value;
        }
        //ссылка на знач последнего узла конст
        const T& GetLast() const {
            if (!tail) throw EmptyStructerException();
            return tail->value;
        }
        //обертка над operator[]
        T& Get(int index) {
            return (*this)[index];
        }
        //обертка над operator[] конст
        const T& Get(int index) const {
            return (*this)[index];
        }
        // Try-семантика: возвращает Option<T> вместо исключения
        Option<T> TryGet(int index) const {
                if (index < 0 || index >= length) {
                    return Option<T>();
                }
                return Option<T>(Get(index));
            }
        //просто возвращает Length
        int GetLength() const {
            return length;
        }
    //более сложные операции
        //возвращает новый список
        Linked_List<T> GetSubList(int startIndex, int endIndex) const {
            if ( startIndex < 0 || endIndex >=length || startIndex > endIndex) {
                throw IndexOutOfRangeException();
            }
            Linked_List<T> sub;
            for (int i = startIndex; i <= endIndex; ++i) {
                sub.Append(Get(i));
            }
            return sub;
        }
        //вставка на позицию index (от 0 до length)
        void InsertAt(const T& item, int index) {
            if (index < 0 || index > length) {
                throw IndexOutOfRangeException();
            }
            if (index == 0) {
                Prepend(item);
            } else if (index == length) {
                Append(item);
            } else {
                Node* after = getNode(index); //узел сейчас на позиции index
                Node* before = after->prev; //узел перед ним
                Node* newNode = new Node(item, before, after); //новый узел между ними
                before->next = newNode;
                after-> prev =newNode;
                ++length;
            }
        }
        //удаление эл по индексу
        void RemoveAt(int index) {
            if (index < 0 || index >=length) {
                throw IndexOutOfRangeException();
            }

            Node* toDelete = getNode(index);
            Node* before = toDelete->prev;
            Node* after = toDelete->next;

            if (before) {
                before->next = after;
            } else {
                head = after;
            }

            if (after) {
                after->prev = before;
            } else {
                tail = before;
            }

            delete toDelete;
            --length;
        }
        //сцепление двух списков. возвращает указатель на новый список
        Linked_List<T>* Concat(Linked_List<T>* other) const {
            Linked_List<T>* result = new Linked_List<T>(*this); //создаем копию текущего списка в дин памяти
            //добавляем все эл из other в конец result
            Node* cur = other->head;
            while (cur) {
                result->Append(cur->value);
                cur = cur->next;
            }
            return result; //ссылка на сцепленный список
        }
};