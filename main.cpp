#include <iostream>
#include <fstream>
#include <ios>
#include <limits>

using namespace std;

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
};

void menu();
void create_list(drug *list, int &count);
void add_drug(drug *list, int rasmer, int &count);
void remote_drug(drug *list, int count);
void del_drug(drug *list, int &count);

void show_drug(drug *list, int count);
void sort_price(drug *list, int count, int rasmer);
void price_increase(drug *list, int count);
void price_reduction(drug *list, int count);
void min_price(drug *list, int count);
void max_price(drug *list, int count);
void date_more(drug *list, int count);
void max_min_all_price(drug *list, int count);

void bubble_sort(drug *list, int count);
void update_file(drug *list, int count);

int main(){
    menu();
    return 0;
}

void menu(){
    const int rasmer = 1500;
    int count = 0;
    drug list[rasmer];
    while (true){
        cout << "Сколько лекарств хранится в таблице: " << count << endl;
        cout << "0: завершение программы" << endl;
        cout << "1: для инициализации базы данных" << endl;
        cout << "2: добавить лекарство в базу" << endl;
        cout << "3: для изменени лекарство по его id" << endl;
        cout << "4: для удаления лекарства по его id" << endl;
        cout << "5: показать информацию о лекарстве по его id " << endl;
        cout << "6: поиск лекартсв,что подорожали в последнее время" << endl;
        cout << "7: поиск лекартсв,что подешевели в последнее время" << endl;
        cout << "8: поиск лекарств с максимальной стоимостью" << endl;
        cout << "9: поиск лекарств с минимальной стоимостью" << endl;
        cout << "10: поиск всех лекарств, срок годности которых заканчивается после введенного года" << endl;
        cout << "11: поиск минимальной и максимальной цены на каждое лекарство" << endl;
        cout << "12: Сортировка лекарств по стоимости" << endl;
        cout << endl;
        cout << "Введите ваш выбор: ";
        int choise;
        cin >> choise;
        switch (choise){
            case 0:
                cout << "Завершение программы" << endl;
                return;
            case 1:
                create_list(list, count);
                break;
            case 2:
                add_drug(list, rasmer, count);
                break;
            case 3:
                remote_drug(list, count);
                break;
            case 4:
                del_drug(list, count);
                break;
            case 5:
                show_drug(list, count);
                break;
            case 6:
                price_increase(list, count);
                break;
            case 7:
                price_reduction(list, count);
                break;
            case 8:
                max_price(list, count);
                break;
            case 9:
                min_price(list, count);
                break;
            case 10:
                date_more(list, count);
                break;
            case 11:
                max_min_all_price(list, count);
                break;
            case 12:
                sort_price(list, count, rasmer);
                break;
            default:
                cout << "Введите одно из предложенных чисел" << endl;
        }
    }
}

void create_list(drug *list, int &count){
    ifstream f;
    f.open("input.txt");
    drug trial;
    while (f.peek() != EOF){
        f >> trial.id;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        f.getline(trial.name, 100);
        f.getline(trial.active_ingredient, 100);
        f.getline(trial.manufacturer, 80);
        f.getline(trial.dosage_form, 50);
        f >> trial.strength;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        f.getline(trial.strength_unit, 10);
        f >> trial.quantity_in_pack;
        f >> trial.price;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        f.getline(trial.expiry_date, 11);
        f >> trial.prescription_required;
        for(int i = 0; i < 5; i++) f >> trial.price_history[i];
        list[count] = trial;
        count++;
    }
    f.close();
}

void add_drug(drug *list, int rasmer, int &count){
    if (count == rasmer){
        cout << "Вся база заполнена" << endl;
        return;
    }
    drug new_drug;
    new_drug.id= list[count-1].id + 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Название: "; cin.getline(new_drug.name, 100);
    cout << "Действующее вещество: "; cin.getline(new_drug.active_ingredient, 100);
    cout << "Производитель: "; cin.getline(new_drug.manufacturer, 80);
    cout << "Форма выпуска: "; cin.getline(new_drug.dosage_form, 50);
    cout << "Дозировка: "; cin >> new_drug.strength;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Единица измерения: "; cin.getline(new_drug.strength_unit, 10);
    cout << "Количество в упаковке: "; cin >> new_drug.quantity_in_pack;
    cout << "Цена: "; cin >> new_drug.price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Срок годности: "; cin.getline(new_drug.expiry_date, 11);
    cout << "Необходим ли рецепт: "; cin >> new_drug.prescription_required;
    cout << "Последние 5 цен на лекартсво: ";
    for (int i = 0; i < 5; i++) cin >> new_drug.price_history[i];
    list[count] = new_drug;
    count++;
    update_file(list, count);
    cout << "Лекарство добавлено в базу" << endl;
    cout << endl;
}

void remote_drug(drug *list, int count){
    cout << "Введите id лекарства, которого надо изменить: ";
    int r_drug; cin >> r_drug;
    for (int i = 0; i < count; i++){
        if (list[i].id == r_drug){
            drug new_drug;
            new_drug.id = list[i].id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Название: "; cin.getline(new_drug.name, 100);
            cout << "Действующее вещество: "; cin.getline(new_drug.active_ingredient, 100);
            cout << "Производитель: "; cin.getline(new_drug.manufacturer, 80);
            cout << "Форма выпуска: "; cin.getline(new_drug.dosage_form, 50);
            cout << "Дозировка: "; cin >> new_drug.strength;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Единица измерения: "; cin.getline(new_drug.strength_unit, 10);
            cout << "Количество в упаковке: "; cin >> new_drug.quantity_in_pack;
            cout << "Цена: "; cin >> new_drug.price;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Срок годности: "; cin.getline(new_drug.expiry_date, 11);
            cout << "Необходим ли рецепт: "; cin >> new_drug.prescription_required;
            cout << "Последние 5 цен на лекартсво: ";
            for (int i = 0; i < 5; i++) cin >> new_drug.price_history[i];
            list[i] = new_drug;
            update_file(list, count);
            cout << "Лекарство обновлено" << endl;
            return;
        }
    }
    cout << "Лекарства с таким id нет" << endl;
    cout << endl;
}

void del_drug(drug *list, int &count){
    cout << "Введите id лекарства, которое надо удалить: ";
    int d_drug; cin >> d_drug;
    bool drug_in_list = false;
    int d_del;
    for (int i = 0; i < count; i++){
        if (d_drug == list[i].id){
            d_del = i;
            drug_in_list = true;
        }
    }
    if (drug_in_list){
        for (int i = d_del; i < count - 1; i++) list[i] = list[i+1];
        count--;
        update_file(list, count);
        cout << "Лекарство удалено" << endl;
    }else{
        cout << "Нет лекарства в базе" << endl;
    }
}

void show_drug(drug *list, int count){
    cout << "Введите id лекарства для вывода информации о нём: ";
    int drug_id;
    cin >> drug_id;
    for (int i = 0; i < count; i++){
        if (list[i].id == drug_id){
            ofstream f_out;
            f_out.open("show.txt");
            f_out << "ID: " << list[i].id << endl;
            f_out << "Название: " << list[i].name << endl;
            f_out << "Действующее вещество: " << list[i].active_ingredient << endl;
            f_out << "Производитель: " << list[i].manufacturer << endl;
            f_out << "Форма: " << list[i].dosage_form << endl;
            f_out << "Дозировка: " << list[i].strength << endl;
            f_out << "Единица измерения дозировки: " << list[i].strength_unit << endl;
            f_out << "Количество в упаковке: " << list[i].quantity_in_pack << endl;
            f_out << "Цена: " << list[i].price << endl;
            f_out << "Срок годности: " << list[i].expiry_date << endl;
            f_out << "Необходимость рецепта: " << list[i].prescription_required << endl;
            f_out << "Последние 5 стоимостей: ";
            for (int k = 0; k < 5; k++) {
                f_out << list[i].price_history[k] << " ";
            }
            f_out << endl;
            f_out.close();
            cout << "записано в файл show.txt" << endl;
            cout << endl;
            return;
        }
    }
    cout << "Нет лекарства с таким id" << endl;
}

void sort_price(drug *list, int count, int rasmer){
    ofstream f_out;
    f_out.open("output_sort.txt");
    drug lst[rasmer];
    for (int i = 0; i < rasmer; i++) lst[i] = list[i];
    bubble_sort(lst, count);
    for (int i = 0; i < count; i++){
        f_out << lst[i].id << endl;
        f_out << lst[i].name << endl;
        f_out << lst[i].active_ingredient << endl;
        f_out << lst[i].manufacturer << endl;
        f_out << lst[i].dosage_form << endl;
        f_out << lst[i].strength << endl;
        f_out << lst[i].strength_unit << endl;
        f_out << lst[i].quantity_in_pack << endl;
        f_out << lst[i].price << endl;
        f_out << lst[i].expiry_date << endl;
        f_out << lst[i].prescription_required << endl;
        for (int j = 0; j < 5; j++){
            if (i == count - 1 && j == 4){
                f_out << lst[i].price_history[j];
            }else{
                f_out << lst[i].price_history[j] << endl;
            }
        }
    }
}

void price_increase(drug *list, int count){
    ifstream f;

}

void price_reduction(drug *list, int count){

}

void min_price(drug *list, int count){

}

void max_price(drug *list, int count){

}

void date_more(drug *list, int count){

}

void max_min_all_price(drug *list, int count){

}

void bubble_sort(drug *list, int count){
    bool end;
    do {
        end = false;
        for (int i = 0; i < count - 1; i++){
            if (list[i].price > list[i+1].price){
                double temp = list[i].price;
                list[i].price = list[i+1].price;
                list[i+1].price = temp;
                end = true;
            }
        }
    } while (end);
}

void update_file(drug *list, int count){
    ofstream f_out;
    f_out.open("input.txt");
    for (int i = 0; i < count; i++){
        f_out << list[i].id << endl;
        f_out << list[i].name << endl;
        f_out << list[i].active_ingredient << endl;
        f_out << list[i].manufacturer << endl;
        f_out << list[i].dosage_form << endl;
        f_out << list[i].strength << endl;
        f_out << list[i].strength_unit << endl;
        f_out << list[i].quantity_in_pack << endl;
        f_out << list[i].price << endl;
        f_out << list[i].expiry_date << endl;
        f_out << list[i].prescription_required << endl;
        for (int j = 0; j < 5; j++){
            if (i == count - 1 && j == 4){
                f_out << list[i].price_history[j];
            }else{
                f_out << list[i].price_history[j] << endl;
            }
        }
    }
}