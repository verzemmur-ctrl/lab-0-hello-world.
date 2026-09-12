#include <stdio.h>
#include <stdlib.h>

#define INVENTORY_SIZE 10
#define EMPTY_SLOT 0
#define TREE_ID 1
#define STONE_ID 2
#define SEEDS_ID 3
#define IRON_ID 4
#define GOLD_ID 5
#define DIAMOND_ID 6
#define CLOTH_ID 7
#define WOOD_PLANK_ID 8
#define METAL_INGOT_ID 9
#define GEM_ID 10

/* Предварительные объявления функций */
const char* get_item_name(int id);
int safe_scan_int(const char* prompt);

const char* get_item_name(int id) {
    switch (id) {
        case TREE_ID:         return "Дерево";
        case STONE_ID:        return "Камень";
        case SEEDS_ID:        return "Семена";
        case IRON_ID:         return "Железо";
        case GOLD_ID:         return "Золото";
        case DIAMOND_ID:      return "Алмаз";
        case CLOTH_ID:        return "Ткань";
        case WOOD_PLANK_ID:   return "Доска";
        case METAL_INGOT_ID:  return "Слиток";
        case GEM_ID:          return "Самоцвет";
        default:              return "";
    }
}

int safe_scan_int(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            return value;
        } else {
            printf("Ошибка ввода! Введите целое число.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

int main() {
    int current_day = 1;
    int current_hour = 8;
    int inventory[INVENTORY_SIZE] = {0};

    inventory[0] = TREE_ID;
    inventory[1] = STONE_ID;
    inventory[2] = SEEDS_ID;
    inventory[3] = TREE_ID;
    inventory[4] = IRON_ID;
    inventory[5] = GOLD_ID;
    inventory[6] = EMPTY_SLOT;
    inventory[7] = DIAMOND_ID;
    inventory[8] = CLOTH_ID;
    inventory[9] = TREE_ID;

    int choice;

    while (1) {
        printf("\n=== МЕНЮ ФЕРМЕРА ===\n");
        printf("[0] Выход\n");
        printf("[1] Посмотреть на часы\n");
        printf("[2] Промотать время (Поработать)\n");
        printf("[3] Посмотреть инвентарь\n");
        printf("[4] Положить предмет в слот\n");
        printf("[5] Выбросить предмет\n");
        printf("[6] Ревизия ресурсов (вариант 1)\n");
        printf("Выберите пункт: ");

        choice = safe_scan_int("");

        switch (choice) {
            case 0:
                printf("До свидания, фермер!\n");
                return 0;

            case 1:
                printf("Текущее время: День %d, %02d:00\n", current_day, current_hour);
                break;

            case 2: {
                int work_hours = safe_scan_int("Сколько часов вы хотите поработать? ");
                if (work_hours < 0) {
                    printf("Количество часов не может быть отрицательным.\n");
                    break;
                }
                current_hour += work_hours;
                while (current_hour >= 24) {
                    current_hour -= 24;
                    current_day++;
                }
                printf("Вы поработали %d часов. Теперь: День %d, %02d:00\n",
                       work_hours, current_day, current_hour);
                break;
            }

            case 3:
                printf("Инвентарь:\n");
                for (int i = 0; i < INVENTORY_SIZE; i++) {
                    printf("Слот %d: [%d] (%s)\n", i, inventory[i], get_item_name(inventory[i]));
                }
                break;

            case 4: {
                int slot_index = safe_scan_int("Введите индекс слота (0-9): ");
                if (slot_index < 0 || slot_index >= INVENTORY_SIZE) {
                    printf("Ошибка: индекс слота должен быть от 0 до %d.\n", INVENTORY_SIZE - 1);
                    break;
                }
                int item_id = safe_scan_int("Введите ID предмета (0-10): ");
                if (item_id < EMPTY_SLOT || item_id > GEM_ID) {
                    printf("Ошибка: ID предмета должен быть от %d до %d.\n", EMPTY_SLOT, GEM_ID);
                    break;
                }
                inventory[slot_index] = item_id;
                printf("Предмет ID %d помещён в слот %d.\n", item_id, slot_index);
                break;
            }

            case 5: {
                int slot_index = safe_scan_int("Введите индекс слота для очистки (0-9): ");
                if (slot_index < 0 || slot_index >= INVENTORY_SIZE) {
                    printf("Ошибка: индекс слота должен быть от 0 до %d.\n", INVENTORY_SIZE - 1);
                    break;
                }
                inventory[slot_index] = EMPTY_SLOT;
                printf("Слот %d очищен.\n", slot_index);
                break;
            }

            case 6: {
                int search_id = safe_scan_int("Введите ID предмета для ревизии (0-10): ");
                if (search_id < EMPTY_SLOT || search_id > GEM_ID) {
                    printf("Ошибка: ID предмета должен быть от %d до %d.\n", EMPTY_SLOT, GEM_ID);
                    break;
                }

                int count = 0;
                int positions[INVENTORY_SIZE];
                int pos_count = 0;

                for (int i = 0; i < INVENTORY_SIZE; i++) {
                    if (inventory[i] == search_id) {
                        count++;
                        positions[pos_count++] = i;
                    }
                }

                if (count == 0) {
                    printf("Предмет с ID %d не найден в инвентаре.\n", search_id);
                } else {
                    printf("Предмет: %s (ID %d)\n", get_item_name(search_id), search_id);
                    printf("Количество в инвентаре: %d\n", count);
                    printf("Позиции слотов: ");
                    for (int i = 0; i < pos_count; i++) {
                        printf("%d", positions[i]);
                        if (i < pos_count - 1) printf(", ");
                    }
                    printf("\n");
                }
                break;
            }

            default:
                printf("Неверный пункт меню. Попробуйте снова.\n");
                break;
        }
    }

    return 0;
}
