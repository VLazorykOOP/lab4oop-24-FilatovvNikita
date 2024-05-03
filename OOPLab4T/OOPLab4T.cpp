
/*
* //Task1
#include <iostream>
class VectorDouble {
private:
    double* ptr;
    int size;
    int codeError;

public:
    // Конструктор без параметрів
    VectorDouble() : ptr(new double[1]), size(1), codeError(0) {
        *ptr = 0.0;
    }
    // Конструктор з одним параметром
    VectorDouble(int s) : ptr(new double[s]), size(s), codeError(0) {
        for (int i = 0; i < size; ++i) {
            ptr[i] = 0.0;
        }
    }
    // Конструктор із двома параметрами
    VectorDouble(int s, double val) : ptr(new double[s]), size(s), codeError(0) {
        for (int i = 0; i < size; ++i) {
            ptr[i] = val;
        }
    }
    // Деструктор
    ~VectorDouble() {
        delete[] ptr;
    }
    // Операції присвоєння
    VectorDouble& operator=(const VectorDouble& other) {
        if (this != &other) {
            delete[] ptr;
            size = other.size;
            ptr = new double[size];
            for (int i = 0; i < size; ++i) {
                ptr[i] = other.ptr[i];
            }
        }
        return *this;
    }
    // Операція []  (індексація по типу як в масиві)
    double& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = -1; // Помилка: невірний індекс
            return ptr[size - 1];
        }
        codeError = 0;
        return ptr[index];
    }
    // Операції збільшення та зменшення на 1(++)
    VectorDouble& operator++() {
        for (int i = 0; i < size; ++i) {
            ++ptr[i];
        }
        return *this;
    }
    VectorDouble operator++(int) {
        VectorDouble temp(*this);
        operator++();
        return temp;
    }
    VectorDouble& operator--() {
        for (int i = 0; i < size; ++i) {
            --ptr[i];
        }
        return *this;
    }
    VectorDouble operator--(int) {
        VectorDouble temp(*this);
        operator--();
        return temp;
    }
    // Операція заперечення
    bool operator!() const {
        return size != 0;
    }
    // Операція зміни знаку
    VectorDouble operator-() const {
        VectorDouble result(size);
        for (int i = 0; i < size; ++i) {
            result.ptr[i] = -ptr[i];
        }
        return result;
    }
    // Операції додавання, віднімання, множення та ділення
    VectorDouble& operator+=(const VectorDouble& other) {
        for (int i = 0; i < size; ++i) {
            ptr[i] += other.ptr[i];
        }
        return *this;
    }
    VectorDouble& operator-=(const VectorDouble& other) {
        for (int i = 0; i < size; ++i) {
            ptr[i] -= other.ptr[i];
        }
        return *this;
    }
    VectorDouble& operator*=(double scalar) {
        for (int i = 0; i < size; ++i) {
            ptr[i] *= scalar;
        }
        return *this;
    }
    VectorDouble& operator/=(double scalar) {
        if (scalar != 0) {
            for (int i = 0; i < size; ++i) {
                ptr[i] /= scalar;
            }
        }
        else {
            codeError = -2; // Помилка: ділення на нуль
        }
        return *this;
    }
    // Операції порівняння
    bool operator==(const VectorDouble& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            if (ptr[i] != other.ptr[i]) return false;
        }
        return true;
    }
    bool operator!=(const VectorDouble& other) const {
        return !(*this == other);
    }
    // Функція для отримання коду помилки
    int getErrorCode() const {
        return codeError;
    }
    // Функція для виведення вектора у потік
    friend std::ostream& operator<<(std::ostream& out, const VectorDouble& vec);
};
std::ostream& operator<<(std::ostream& out, const VectorDouble& vec) {
    for (int i = 0; i < vec.size; ++i) {
        out << vec.ptr[i] << " ";
    }
    return out;
}
int main() {
    using namespace std;
    setlocale(LC_CTYPE, "Ukr");
    // Приклад використання
    VectorDouble v1(3, 2.0);
    VectorDouble v2(3, 3.0);
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    v1 += v2;
    cout << "v1 після: v1 += v2: " << v1 << endl;
    return 0;
}

*/
//Task2
#include <iostream>
#include <map>
#include <string>
using namespace std;
class CountryCapitalMap {
private:
    map<string, string> data;
    int CodeError; // Код помилки: 0 - норма, 1 - сутність не знайдена
public:
    CountryCapitalMap() : CodeError(0) {}
    // Додавання асоціативної пари "Назва країни - Столиця"
    void add(const string& country, const string& capital) {
        data[country] = capital;
    }
    // Перевантаження оператора індексації []
    string& operator[](const string& country) {
        if (data.find(country) != data.end()) {
            CodeError = 0; // Сутність знайдена, код помилки - 0
            return data[country];
        }
        else {
            CodeError = 1; // Сутність не знайдена, код помилки - 1
            // Повернути столицю за замовчуванням або порожній рядок
            static string default_capital;
            return default_capital;
        }
    }
    // Повертає код помилки
    int getErrorCode() const {
        return CodeError;
    }
    // Перевантаження оператора виклику функції ()
    string& operator()(const string& country) {
        return (*this)[country];
    }
    // Перевантаження дружньої операції виведення <<
    friend ostream& operator<<(ostream& out, const CountryCapitalMap& map) {
        for (const auto& pair : map.data) {
            out << pair.first << " - " << pair.second << endl;
        }
        return out;
    }
    // Перевантаження дружньої операції введення >>
    friend istream& operator>>(istream& in, CountryCapitalMap& map) {
        string country, capital;
        while (in >> country >> capital) {
            map.add(country, capital);
        }
        return in;
    }
};

int main() {
    CountryCapitalMap capitals;
    setlocale(LC_CTYPE, "UKR");
    // Додавання асоціативних пар
    capitals.add("Україна", "Київ");
    capitals.add("Польща", "Варшава");
    capitals.add("Франція", "Париж");
    // Виведення асоціативних пар
    cout << "Асоціативний масив країн та столиць:" << endl;
    cout << capitals << endl;
    // Використання оператора []
    cout << "Столиця Польщі: " << capitals["Польща"] << endl;
    cout << "Столиця Білорусії: " << capitals["Білорусія"] << endl;
    // Використання оператора ()
    capitals("Україна") = "Львів"; // Змінюємо столицю України з Києва на Львів
    // Виведення асоціативних пар після змін
    cout << "Асоціативний масив після змін:" << endl;
    cout << capitals << endl;

    return 0;
}