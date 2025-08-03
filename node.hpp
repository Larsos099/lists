#pragma once // node.hpp
#include <iostream>
#include <cstring>
#include <cstddef>
#include <memory> 
#include <any>  
#include <typeinfo>
#include <typeindex>
namespace lists {
    class Node {
        std::shared_ptr<void> data;
        std::type_index dataType = typeid(void);
    public:
        Node() = default;
        std::unique_ptr<Node> next = nullptr;
        std::shared_ptr<Node> sharedNext = nullptr; // later for circular linked lists
        template<typename T>
        Node(const T& _data) {
            std::shared_ptr<std::decay_t<T>> dataPtr = std::make_shared<std::decay_t<T>>(_data);
            data = std::static_pointer_cast<void>(dataPtr);
            dataType = std::type_index(typeid(std::decay_t<T>));

        }
        template<typename T>
        T* get_data_ptr() {
            if(std::type_index(typeid(std::decay_t<T>)) != dataType) return nullptr;
            return std::static_pointer_cast<std::decay_t<T>>(data).get();
        }

        template<typename T>
        T get_data() {
            if(std::type_index(typeid(std::decay_t<T>)) != dataType) throw std::bad_cast();
            return *std::static_pointer_cast<std::decay_t<T>>(data);
        }
        template<typename T>
        T get_data_unsafe() {
            return *std::static_pointer_cast<std::decay_t<T>>(data);
        }
        ~Node() = default;
    };
}
