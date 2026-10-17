#include <stdio.h>

#define INVENTORY_SIZE 10

int current_day = 1;
int current_hour = 8;
int inventory[INVENTORY_SIZE] = {0};

const char* item_names[] = {
    "Пусто",
    "Дерево",
    "Камень",
    "Семена",
    "Ягода",
    "Палка",
    "Гриб",
    "Яблоко",
    "Яйцо",
    "Ткань"
};

void see_time();
void work_hours();
void view_inventory();
void put_item();
void remove_item();
void clear_trash();
void compress_inventory();  // новая функция

int main() {
    int choice;
    while (1) {
        printf("\nМеню:\n");
        printf("[0] Выход\n");
        printf("[1] Посмотреть на часы\n");
        printf("[2] Промотать время (Поработать)\n");
        printf("[3] Посмотреть инвентарь\n");
        printf("[4] Положить предмет в слот\n");
        printf("[5] Выбросить предмет\n");
        printf("[6] Очистка от мусора\n");
        printf("[7] Сжать инвентарь (сортировка рюкзака)\n");  // новый пункт
        printf("Выберите пункт: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Выход из программы.\n");
                return 0;
            case 1:
                see_time();
                break;
            case 2:
                work_hours();
                break;
            case 3:
                view_inventory();
                break;
            case 4:
                put_item();
                break;
            case 5:
                remove_item();
                break;
            case 6:
                clear_trash();
                break;
            case 7:
                compress_inventory();
                break;
            default:
                printf("Некорректный выбор.\n");
        }
    }
    return 0;
}

void see_time() {
    printf("Текущее время: День %d, %02d:00\n", current_day, current_hour);
}

void work_hours() {
    int hours;
    printf("Введите количество часов для работы: ");
    scanf("%d", &hours);
    if (hours < 0) {
        printf("Некорректное значение часов.\n");
        return;
    }
    current_hour += hours;
    while (current_hour >= 24) {
        current_hour -= 24;
        current_day++;
    }
}

void view_inventory() {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        printf("Слот %d: [%d]", i, inventory[i]);
        if (inventory[i] >= 1 && inventory[i] <= 9) {
            printf(" (%s)", item_names[inventory[i]]);
        }
        printf("\n");
    }
}

void put_item() {
    int index, item_id;
    printf("Введите индекс слота (0-%d): ", INVENTORY_SIZE - 1);
    scanf("%d", &index);
    if (index < 0 || index >= INVENTORY_SIZE) {
        printf("Некорректный индекс.\n");
        return;
    }
    printf("Введите ID предмета (0-9): ");
    scanf("%d", &item_id);
    if (item_id < 0 || item_id > 9) {
        printf("Некорректный ID предмета.\n");
        return;
    }
    inventory[index] = item_id;
    printf("Предмет %s добавлен в слот %d.\n", item_names[item_id], index);
}

void remove_item() {
    int index;
    printf("Введите индекс слота (0-%d): ", INVENTORY_SIZE - 1);
    scanf("%d", &index);
    if (index < 0 || index >= INVENTORY_SIZE) {
        printf("Некорректный индекс.\n");
        return;
    }
    inventory[index] = 0;
    printf("Предмет удалён из слота %d.\n", index);
}

void clear_trash() {
    int item_id, count = 0;
    printf("Введите ID предмета для удаления: ");
    scanf("%d", &item_id);
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inventory[i] == item_id) {
            inventory[i] = 0;
            count++;
        }
    }
    printf("Удалено %d предметов.\n", count);
}

// Новая функция: сжатие инвентаря
void compress_inventory() {
    printf("Инвентарь ДО сжатия:\n");
    view_inventory();

    int write = 0;  // позиция для записи ненулевых элементов
    // Проходим по массиву и сдвигаем все ненулевые элементы в начало
    for (int read = 0; read < INVENTORY_SIZE; read++) {
        if (inventory[read] != 0) {
            inventory[write] = inventory[read];
            write++;
        }
    }
    // Заполняем оставшиеся слоты нулями
    while (write < INVENTORY_SIZE) {
        inventory[write] = 0;
        write++;
    }

    printf("Инвентарь ПОСЛЕ сжатия:\n");
}