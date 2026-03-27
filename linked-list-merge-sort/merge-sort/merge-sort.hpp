#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <initializer_list>
#include <memory>

struct ListElement 
{
    int value;
    std::unique_ptr<ListElement> next;

    ListElement(int avalue, std::unique_ptr<ListElement> &&anext = nullptr)
        : value(avalue), next(std::move(anext)) {}
};

struct List 
{
    std::unique_ptr<ListElement> head;
    List(std::initializer_list<int>);
    List() = default;

    List(List const &) = delete; // Копировать списки запрещено
    List(List &&) = default; // Но можно перемещать
    List& operator=(List const&) = delete; // Переприсваивать тоже запрещено
    List& operator=(List&&) = default; // Но можно присвоить, используя std::move
    // Деструктор для того, чтобы избежать рекурсии при удалении
    ~List() {
        auto ptr = std::move(head);
        while (ptr) {
            auto tmp = std::move(ptr->next);
            ptr = std::move(tmp);
        }
    }
};

List merge(List, List) noexcept;

void mergesort(List&) noexcept;

#endif // MERGE_SORT_HPP
