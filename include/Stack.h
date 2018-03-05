#ifndef STACK_H_
#define STACK_H_


#include "linked_list.h"

template <typename T>
class Stack
{
    public:
        Stack():list_size(0)
        {}
        Stack(Stack&& other): list(std::move(other.list)), list_size(other.list_size)
        {
            std::cout << "Stack move cnstr" << std::endl;
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
