#pragma once
#include <memory>
#include <iostream>
#include <cstdlib>
#include "node.hpp"

namespace lists
{
    class CircularLinkedList
    {
    private:
        std::shared_ptr<Node> rootPtr = nullptr;

        template <typename T>
        std::shared_ptr<Node> create_node(const T &val)
        {
            using decayedTemplate = std::decay_t<T>;
            return std::make_shared<Node>(decayedTemplate(val));
        }

        void push_front(std::shared_ptr<Node> &&_node)
        {
            if (!rootPtr)
            {
                rootPtr = _node;
                rootPtr->sharedNext = rootPtr;
                return;
            }

            auto last = rootPtr;
            while (last->sharedNext != rootPtr)
            {
                last = last->sharedNext;
            }

            _node->sharedNext = rootPtr;
            last->sharedNext = _node;
            rootPtr = _node;
        }

        void push_back(std::shared_ptr<Node> &&_node)
        {
            if (!rootPtr)
            {
                rootPtr = _node;
                rootPtr->sharedNext = rootPtr;
                return;
            }

            auto last = rootPtr;
            while (last->sharedNext != rootPtr)
            {
                last = last->sharedNext;
            }

            last->sharedNext = _node;
            _node->sharedNext = rootPtr;
        }

    public:
        CircularLinkedList() = default;
        ~CircularLinkedList() = default;

        template <typename T>
        void push_front(const T &val)
        {
            push_front(std::move(create_node(val)));
        }

        template <typename T>
        void push_back(const T &val)
        {
            push_back(std::move(create_node(val)));
        }

        template <typename T>
        T get_by_index(const int idx)
        {
            auto current = rootPtr;
            int i = 0;

            while (current && i < idx)
            {
                current = current->sharedNext;
                if (current == rootPtr)
                    throw std::out_of_range("Index out of range.");
                i++;
            }

            return current->get_data<T>();
        }

        template <typename T>
        void remove_by_value(const T &val)
        {
            if (!rootPtr)
                return;

            while (rootPtr &&
                   rootPtr->get_data_ptr<T>() &&
                   *rootPtr->get_data_ptr<T>() == val)
            {
                if (rootPtr->sharedNext == rootPtr)
                {
                    rootPtr = nullptr;
                    return;
                }

                auto last = rootPtr;
                while (last->sharedNext != rootPtr)
                    last = last->sharedNext;

                rootPtr = rootPtr->sharedNext;
                last->sharedNext = rootPtr;
            }

            auto current = rootPtr;
            while (current && current->sharedNext != rootPtr)
            {
                auto nextNode = current->sharedNext;
                auto ptr = nextNode->get_data_ptr<T>();
                if (ptr && *ptr == val)
                {
                    current->sharedNext = nextNode->sharedNext;
                }
                else
                {
                    current = current->sharedNext;
                }
            }
        }

        void remove_by_index(const int idx)
        {
            if (idx == 0)
            {
                if (rootPtr->sharedNext == rootPtr)
                {
                    rootPtr = nullptr;
                    return;
                }

                auto last = rootPtr;
                while (last->sharedNext != rootPtr)
                    last = last->sharedNext;

                rootPtr = rootPtr->sharedNext;
                last->sharedNext = rootPtr;
                return;
            }

            auto current = rootPtr;
            int i = 0;

            while (current->sharedNext != rootPtr && i < idx - 1)
            {
                current = current->sharedNext;
                i++;
            }

            if (current->sharedNext == rootPtr)
                throw std::out_of_range("Index out of range.");

            current->sharedNext = current->sharedNext->sharedNext;
        }

        template <typename T>
        bool contains(const T &val)
        {
            if (!rootPtr)
                return false;

            auto current = rootPtr;
            while (true)
            {
                auto ptr = current->get_data_ptr<T>();
                if (ptr && *ptr == val)
                    return true;

                current = current->sharedNext;
                if (current == rootPtr)
                    break;
            }

            return false;
        }

        size_t size() const {
            auto current = rootPtr.get();
            size_t size = 1;
            while(current->sharedNext.get() != rootPtr.get()) {
                size++;
                current = current->sharedNext.get();
            }
            return size;
        }
    }; 
}
