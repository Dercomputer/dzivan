#include <iostream>
#include <fstream>

struct drug {
    int id;                     // идентификатор
    char name[100];             // Название лекарства
    char active_ingredient[100]; // Действующее вещество
    char manufacturer[80];      // Производитель лекарства
    char dosage_form[50];       // Форма выпуска
    double strength;            // Дозировка/концентрация
    char strength_unit[10];     // Единица измерения дозировки
    int quantity_in_pack;       // Количество в упаковке
    double price;               // Цена за упаковку
    char expiry_date[11];       // Срок годности
    char prescription_required[5]; // Требуется ли рецепт 
    double price_history[5];    // Последние 5 измениний цен
}
