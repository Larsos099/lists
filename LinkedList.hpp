#pragma once // linkedlist.hpp
#include <memory>
#include <iostream>
#include <cstdlib>
#include "node.hpp"

namespace lists
{
    class LinkedList
    {
    private:
        std::unique_ptr<Node> rootPtr = nullptr;

        template <typename T>
        std::unique_ptr<Node> create_node(const T &val)
        {
            using decayedTemplate = std::decay_t<T>;
            return std::make_unique<Node>(decayedTemplate(val));
        }
        void push_front(std::unique_ptr<Node> &&_node)
        {
            if (!rootPtr)
            {
                rootPtr = std::move(_node);
                return;
            }

            _node->next = std::move(rootPtr);
            rootPtr = std::move(_node);
        }

        void push_back(std::unique_ptr<Node> &&_node)
        {
            if (!rootPtr)
            {
                rootPtr = std::move(_node);
                return;
            }
            auto temp = rootPtr.get();
            while (temp->next)
            {
                temp = temp->next.get();
            }

            temp->next = std::move(_node);
        }

    public:
        LinkedList() = default;
        ~LinkedList() = default;

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

            auto current = rootPtr.get();
            int i = 0;

            while (current->next && i < idx)
            {
                current = current->next.get();
                i++;
            }

            if (i != idx) throw std::out_of_range("Index out of range.");

            return current->get_data<T>();
        }
        template <typename T>
        void remove_by_value(const T &val)
        {

            while (rootPtr && rootPtr->get_data_ptr<T>() && *rootPtr->get_data_ptr<T>() == val)
            {
                rootPtr = std::move(rootPtr->next);
            }

            auto current = rootPtr.get();
            while (current && current->next)
            {
                auto ptr = current->next->get_data_ptr();
                if (ptr && *ptr == val)
                {
                    current->next = std::move(current->next->next);
                }
                else
                {
                    current = current->next.get();
                }
            }
        }

        void remove_by_index(const int idx)
        {
            if (!rootPtr)
                return;

            if (idx == 0)
            {
                rootPtr = std::move(rootPtr->next);
                return;
            }

            auto current = rootPtr.get();
            int i = 0;

            while (current->next && i < idx - 1)
            {
                current = current->next.get();
                i++;
            }

            if (!current->next)
            {
                throw std::out_of_range("Index out of range.");
            }

            current->next = std::move(current->next->next);
        }
        template <typename T>
        bool contains(const T &val)
        {
            auto current = rootPtr.get();
            while (current)
            {
                if (current->get_data_ptr<T>() && *current->get_data_ptr<T>() == val)
                {
                    return true;
                }
                current = current->next.get();
            }
            return false;
        }
    };
}