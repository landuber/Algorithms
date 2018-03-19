#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <utility>
#include <iostream>

template <typename T>
struct Node
{
    Node(const T& value): value(value), next(nullptr) {}
    T value;
    Node* next;
};

template <typename T>
struct list_iterator
{
    list_iterator(Node<T> *entry): entry(entry) {}

    T& operator*() { return entry->value; }
    const T& operator*() const { return entry->value; }
    list_iterator<T> operator++() { entry = entry->next; return *this; }
    bool operator!=(const list_iterator<T>& other) { return entry != other.entry; }
    Node<T> *entry;

};

template <typename T>
class List
{
    public:
        List(){}
        // copy constructor
        List(const List& other)
        {
            for(auto it = other.begin(); it != other.end(); ++it)
            {
                append(*it);
            }
            /*
            for(auto& e : other)
            {
                append(e);
            }
            */
        }
        // copy assignment 
        List& operator=(const List& other)
        {
            if(&other != this)
            {
                while(first)
                {
                    auto tmp = first->next;
                    delete first;
                    first = tmp;
                }
            }
            for(auto it = other.begin(); it != other.end(); ++it)
            {
                append(*it);
            }
            return *this;
        }

        // move constructor
        List(List&& other): first(other.first), last(other.last)
        {
            std::cout << "List move cnstr" << std::endl;
            other.first = nullptr;
            other.last = nullptr;
        }
        // move assignment
        List& operator=(List&& other)
        {
            std::cout << "List move assigmt" << std::endl;
            std::swap(first, other.first);
            std::swap(last, other.last);
        }

        ~List()
        {
            while(first)
            {
                auto tmp = first->next;
                delete first;
                first = tmp;
            }
        }

        void prepend(const T& x)
        {
            auto oldfirst = first;
            first = new Node<T>(x);
            first->next = oldfirst;
        }
        void append(const T& x)
        {
            last = (first ? last->next : first) = new Node<T>(x);
        }

        void remove_first()
        {
            auto tmp = first;
            first = first->next;
            delete tmp;
        }

        list_iterator<T> begin() const { return list_iterator<T>(first); }
        list_iterator<T> end() const { return  list_iterator<T>(nullptr); }

    private:
        Node<T> *first = nullptr, *last = nullptr;
};



#endif
