#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) 
{
    // Задание №1: сделать список из list
    ListElement * tail = nullptr;
    for (int number : list) {
        // TODO: Добавить в создаваемый односвязный список
        if (tail == nullptr) {

            head = std::make_unique<ListElement>(number);
            tail = head.get();
        } else {
            // TODO: Создать элемент списка в tail->next
            tail->next = std::make_unique<ListElement>(number);
            tail = tail->next.get();
        }
    }
}


void head_moving(List &origin, List &result, ListElement *&tail)
{
    if (!result.head)
    {
        result.head = std::move(origin.head);
        tail = result.head.get();
    } 
    else
    {
        tail->next = std::move(origin.head);
        tail = tail->next.get();
    }
    origin.head = std::move(tail->next);
}


List merge(List a, List b) noexcept
{
    // Слияние двух упорядоченных списков
    List result;
    ListElement *tail = nullptr; // должен указывать на последний элемент списка result
    // Выбираем меньший из a.head.value и b.head.value
    // и переносим a.head или b.head в конец result,
    // после чего переносим tail->next обратно
    // в a.head или b.head
    while (a.head && b.head)
    {
        if (a.head->value <= b.head->value)
        {
            head_moving(a, result, tail);
        }
        else
        {
            head_moving(b, result, tail);
        }
    }
    // переносим оставшийся список в конец result
    if (!result.head)
    {
        result.head = std::move(a.head ? a.head : b.head);
    }
    else
    {
        tail->next = std::move(a.head ? a.head : b.head);
    }
    return result;
}



void mergesort(List &list) noexcept 
{
    // Сортировка слиянием
    // 1. Определяем середину списка (разбирали на лекциях)
    if (!list.head || !list.head->next)
    {
        return;
    }
    ListElement *middle = list.head.get();
    ListElement *middle_dop = list.head->next.get();
    while (middle_dop)
    {
        middle_dop = middle_dop->next.get();
        if (middle_dop)
        {
            middle = middle->next.get();
            middle_dop = middle_dop->next.get();
        }
    }
    // 2. Переносим вторую половину в новый список
    List second;
    second.head = std::move(middle->next);
    // second.head = std::move(middle->next);
    // 3. Для каждой половины запускаем mergesort
    mergesort(list);
    mergesort(second);
    // 4. Делаем merge от результатов,
    // не забыв std::move в аргументах,
    // присваивая результат в list
    list.head = std::move(merge(std::move(list), std::move(second)).head);
}