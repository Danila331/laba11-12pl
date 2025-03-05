#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

void showInventory(const std::list<std::string>& inventory) {
    std::cout << "Текущий инвентарь: ";
    for (const auto& item : inventory) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    std::list<std::string> inventory;
    std::string command, item;

    while (true) {
        std::cout << "Введите команду (add, remove, show, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::cout << "Введите название предмета: ";
            std::cin >> item;
            std::back_insert_iterator<std::list<std::string>> inserter(inventory);
            *inserter = item;
        } else if (command == "remove") {
            std::cout << "Введите название предмета для удаления: ";
            std::cin >> item;
            auto it = std::find(inventory.begin(), inventory.end(), item);
            if (it != inventory.end()) {
                inventory.erase(it);
            } else {
                std::cout << "Предмет не найден.\n";
            }
        } else if (command == "show") {
            showInventory(inventory);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Неизвестная команда! Попробуйте снова.\n";
        }
    }
    return 0;
}
