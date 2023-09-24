#include <iostream>
#include <string>
#include <stdexcept>

class ElectricityBill {
private:
    double costPerKilowattHour;
    std::string date;
    double paidAmount;

public:
    ElectricityBill(double cost, const std::string& billDate, double amount)
        : costPerKilowattHour(cost), date(billDate), paidAmount(amount) {}

    // Перевантажена унарна операція інкременту (++), збільшує значення показників на 1
    ElectricityBill& operator++() {
        costPerKilowattHour += 1.0;
        paidAmount += 1.0;
        return *this;
    }

    // Перевантажена операція (-=), зменшує значення показників на задану величину
    ElectricityBill& operator-=(double amount) {
        if (amount > paidAmount) {
            throw std::invalid_argument("Спроба віднімання суми, більшої за сплачену суму");
        }

        costPerKilowattHour -= amount;
        paidAmount -= amount;
        return *this;
    }

    // Метод для пошуку показників за датою
    bool findByDate(const std::string& searchDate) const {
        return date == searchDate;
    }

    // Метод для виводу інформації про рахунок
    void display() const {
        std::cout << "Дата: " << date << std::endl;
        std::cout << "Вартість за кВт-год: " << costPerKilowattHour << std::endl;
        std::cout << "Сплачена сума: " << paidAmount << std::endl;
    }
};

int main() {
    try {
        ElectricityBill bill(0.15, "2023-09-23", 100.0);

        std::cout << "Початковий рахунок:" << std::endl;
        bill.display();

        ++bill;  // Виклик перевантаженого ++
        std::cout << "Після інкременту:" << std::endl;
        bill.display();

        bill -= 20.0;  // Виклик перевантаженого -=
        std::cout << "Після зменшення на 20.0:" << std::endl;
        bill.display();

        // Пошук за датою
        std::string searchDate = "2023-09-23";
        if (bill.findByDate(searchDate)) {
            std::cout << "Знайдено рахунок за датою " << searchDate << std::endl;
        }
        else {
            std::cout << "Рахунок за датою " << searchDate << " не знайдено" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}
