#include "../Banking/CardPayment.hpp"
#include "../Banking/CashPayment.hpp"
#include "Cashier.hpp"
#include <limits>
#include <sstream>
/**
 * @file Cashier.cpp
 * @brief Реализация класса `Cashier`.
 * @details
 * Этот файл содержит реализацию методов класса `Cashier`,
 * который моделирует работу кассира.
 * @author
 * Ekatsune
 */
std::string Cashier::CashReportText() const {
    std::ostringstream oss;
    oss << "\n===== КАССОВЫЙ ОТЧЁТ =====\n";
    oss << "Кассир: " << GetName() << " " << GetSurname() << "\n\n";
    const std::vector<Receipt>& receipts = cash_register.GetReceipts();
    if (receipts.empty()) {
        oss << "За смену не было чеков.\n";
    } else {
        BYN total(0);
        oss << "Количество чеков: " << receipts.size() << "\n\n";
        for (const auto& current_receipt : receipts) {
            oss << "Чек №" << current_receipt.GetId()
                << " — сумма: " << current_receipt.GetTotal().GetRubles() << " BYN\n";
            total += current_receipt.GetTotal();
        }
        oss << "\nИТОГО ЗА СМЕНУ: " << total.GetRubles() << " BYN\n";
    }
    oss << "\nДЕНЕГ В КАССЕ: "
        << cash_register.GetTotalCash().GetRubles() << " BYN\n";
    oss << "==========================\n\n";
    return oss.str();
}

void Cashier::CashReport() {
    if (!cash_register.IsShiftOpen()) cash_register.OpenShift(GetID());
    std::cout << CashReportText();
    cash_register.CloseShift();
}

Receipt Cashier::CreatingReceipt(const Cart& cart) {
    Receipt receipt = cash_register.CreateReceipt(cart);
    return receipt;
}

PaymentMethod *Cashier::AskPaymentMethod() {
    std::cout << "Как вы будете оплачивать?\n"
            << "1 — банковской картой\n"
            << "2 — наличными\n";
    int methodChoice;
    std::cin >> methodChoice;
    switch (methodChoice) {
        case 1:
            return AskCardInfo();
        case 2: {
            double amount;
            std::cout << "Введите сумму полученную от клиента: ";
            std::cin >> amount;
            return new CashPayment(BYN(amount));
        }
        default:
            std::cout << "Неверный выбор. По умолчанию — наличные.\n";
            return new CashPayment(BYN(0));
    }
}

PaymentMethod* Cashier::AskCardInfo() {
    std::string number, holder;
    int day, month, year;
    std::cout << "Введите номер карты: ";
    std::cin >> number;
    std::cin.ignore();
    std::cout << "Имя держателя: ";
    std::getline(std::cin, holder);
    std::cout << "Срок действия карты (дд мм гггг): ";
    std::cin >> day >> month >> year;

    return new CardPayment(number, holder, Date(day, month, year));
}

bool Cashier::CashPaymentMethod(BYN total,CashPayment& method){
    BYN given = method.GetGiven();

    if (given < total) {
        std::cout << "Недостаточно наличных!\n";
        return false;
    }

    if (!method.Pay(total)) {
        std::cout << "Ошибка оплаты наличными!\n";
        return false;
    }

    cash_register.AddCash(total);

    std::cout << "Оплата наличными успешна. Сдача: "
              << method.GetChange().GetRubles() << "\n";

    return true;
}

bool Cashier::CardPaymentMethod(BYN total,CardPayment& method){
    CardPayment& cardMethod = static_cast<CardPayment&>(method);

    if (!cardMethod.ValidateCard()) {
        std::cout << "Ошибка: карта просрочена или недействительна!\n";
        return false;
    }

    if (!cardMethod.Pay(total)) {
        std::cout << "Ошибка оплаты картой!\n";
        return false;
    }

    cash_register.AddCash(total); // фиксируем поступление
    std::cout << "Оплата картой успешна.\n";
    return true;
}

bool Cashier::ProcessPayment(Receipt& receipt, PaymentMethod& method) {
    BYN total = receipt.GetTotal();
    std::cout << "Сумма к оплате: " << total.GetRubles() << " BYN\n";
    std::cout << "Метод оплаты: " << method.GetName() << "\n";
    if (method.GetName() == "Cash") {
        if (auto* cash = dynamic_cast<CashPayment*>(&method)) {
            return CashPaymentMethod(total, *cash);
        } else {
            std::cout << "Ошибка: объект метода оплаты не CashPayment!\n";
            return false;
        }
    }
    else if (method.GetName() == "Card") {
        if (auto* card = dynamic_cast<CardPayment*>(&method)) {
            return CardPaymentMethod(total, *card);
        } else { std::cout << "Ошибка: объект метода оплаты не CardPayment!\n";
            return false;
        }
    }
    else { std::cout << "Неизвестный метод оплаты!\n";
        return false;
    }
}



void Cashier::CustomerService(Cart &cart) {
    if (!cash_register.IsShiftOpen()) cash_register.OpenShift(GetID());
    int choice;
    std::cout << "Здравствуйте! Пакетик нужен?\n"
    << "Введите: 1 - да, 0 - нет\n";
    std::cin >> choice;
    if (choice == 1) std::cout << "Держите! *протягивает пакет*\n";
    Receipt current_receipt = CreatingReceipt(cart);
    std::cout << "Сумма к оплате: "
              << current_receipt.GetTotal().GetRubles() << " BYN\n";

    PaymentMethod* method = AskPaymentMethod();
    bool success = ProcessPayment(current_receipt, *method);
    if (!success) {
        std::cout << "Оплата не прошла!\n";
    }
    delete method;
    std::cout << "До свидания! Приходите к нам ещё)\n";
}

void Cashier::CancellationOfProduct(Receipt &receipt) {
    std::cout << "Какой товар убрать?\n";
    std::string name_of_item;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name_of_item);
    std::cout << "Кассир " << GetName()
              << " удаляет товар из чека.\n";
    receipt.DeleteItem(name_of_item);
}

void Cashier::OpenShift() {
    cash_register.OpenShift(GetID());
}

CashRegister Cashier::GetCashRegister() {
    return cash_register;
}
