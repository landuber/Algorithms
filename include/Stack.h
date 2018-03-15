#ifndef STACK_H_
#define STACK_H_


#include "linked_list.h"

template <typename T>
class Stack
{
    public:
        Stack():list_size(0)
        {}
        Stack(const Stack & other): list(other.list), list_size(other.list_size)
        {
            std::cout << "Stack cpy cnstr" << std::endl;
        }
        Stack(Stack&& other): list(std::move(other.list)), list_size(other.list_size)
        {
            std::cout << "Stack move cnstr" << std::endl;
        } 
        Stack& operator=(const Stack & other)
        {
            std::cout << "Stack cpy assigmt" << std::endl;
            list = other.list;
            list_size = other.list_size;
        }
        Stack& operator=(Stack&& other)
        {
            std::cout << "Stack move assigmt" << std::endl;
            list = std::move(other.list);
            list_size = other.list_size;
        }

        void push(const T& x)
        {
            list.prepend(x);
            ++list_size;
        }
        T pop()
        {
            auto top = *(list.begin());
            list.remove_first();
            --list_size;
            return top;
        }
        int size()
        {
            return list_size;
        }

        auto begin() { return list.begin(); }
        auto end() { return list.end(); }
    private:
        List<T> list;
        int list_size = 0;
};


template <typename T>
class Queue
{
   public:
        Queue():list_size(0)
        {}
        Queue(const Queue & other): list(other.list), list_size(other.list_size)
        {
            std::cout << "Queue cpy cnstr" << std::endl;
        }
        Queue(Queue&& other): list(std::move(other.list)), list_size(other.list_size)
        {
            std::cout << "Queue move cnstr" << std::endl;
        } 
        Queue& operator=(const Queue & other)
        {
            std::cout << "Queue cpy assigmt" << std::endl;
            list = other.list;
            list_size = other.list_size;
        }
        Queue& operator=(Queue&& other)
        {
            std::cout << "Queue move assigmt" << std::endl;
            list = std::move(other.list);
            list_size = other.list_size;
        }
       void enqueue(const T& x) 
       {
           list.append(x);
           ++list_size;
       }

       T dequeue()
       {
           auto bottom = *(list.begin());
           list.remove_first();
           --list_size;
           return bottom;
       }

       int size()
       {
           return list_size;
       }

       auto begin() { return list.begin(); }
       auto end() { return list.end(); }
   private:
       List<T> list;
       int list_size = 0;
};

template <typename T>
class Bag
{
    public:
        void add(const T& x)
        {
            list.append(x);
        }
       auto begin() { return list.begin(); }
       auto end() { return list.end(); }
    private:
        List<T> list;
};

#endif
