#ifndef MINIMARKET_CONTACTINFORMATION_HPP
#define MINIMARKET_CONTACTINFORMATION_HPP

#include <string>

/**
 * @class ContactInformation
 * @brief Класс контактной информации
 * Содержит телефон, email и адрес, а также методы для их получения и изменения.
 */
class ContactInformation {
private:
    std::string phone;   /**< Телефон */
    std::string email;   /**< Электронная почта */
    std::string address; /**< Адрес */

public:
    /** @brief Конструктор по умолчанию */
    ContactInformation() = default;

    /**
     * @brief Конструктор с инициализацией всех полей
     * @param phone Телефон
     * @param email Электронная почта
     * @param address Адрес
     */
    ContactInformation(const std::string& phone,
                       const std::string& email,
                       const std::string& address)
            : phone(phone), email(email), address(address) {}

    /**
     * @brief Установить телефон
     * @param phone Новый телефон
     */
    void SetPhone(const std::string& phone);

    /**
     * @brief Установить email
     * @param email Новый email
     */
    void SetEmail(const std::string& email);

    /**
     * @brief Установить адрес
     * @param address Новый адрес
     */
    void SetAddress(const std::string& address);

    /**
     * @brief Получить телефон
     * @return std::string Телефон
     */
    std::string GetPhone() const;

    /**
     * @brief Получить email
     * @return std::string Электронная почта
     */
    std::string GetEmail() const;

    /**
     * @brief Получить адрес
     * @return std::string Адрес
     */
    std::string GetAddress() const;
};

#endif //MINIMARKET_CONTACTINFORMATION_HPP
