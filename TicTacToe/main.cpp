/**
 * @file main.cpp
 * @brief Запуск "Крестики-нолики".
 * @details
 * Этот файл содержит функцию `main()`, которая реализует главное меню
 * консольного приложения. Пользователь может начать новую игру или выйти из программы.
 * При выборе "New game" создаётся объект класса `Play`, который управляет игровым процессом:
 * отрисовкой поля, логикой ходов и проверкой конца игры.
 *
 * @author Ekatsune
 * @see Play
 */

#include "Play.h"
#include <iostream>
/**
 * @brief Точка входа в программу.
 * @details
 * Запускает консольное меню, позволяющее пользователю начать новую игру
 * или завершить выполнение программы.
 * При старте новой игры запрашивает размер игрового поля, создаёт объект `Play`
 * и управляет игровым циклом до завершения партии.
 *
 * @return Целое число — код завершения программы (0 при успешном завершении).
 * @see Play::Draw(), Play::Logic(), Play::GetGameOver()
 */

int main() {
    int choice;
    do {
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. New game\n";
        std::cout << "2. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int size;
            std::cout << "Enter field size: ";
            std::cin >> size;

            Play game(size);

            std::cout << "\n=== Tic Tac Toe ===\n";
            std::cout << "Player 1: X, Player 2: O\n";

            while (!game.GetGameOver()) {
                game.Draw();
                game.Logic();
            }

            std::cout << "\nThe play is end!\n";
        }

    } while (choice != 2);

    std::cout << "Have a good day!\n";
    return 0;
}
