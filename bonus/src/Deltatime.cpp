/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Deltatime
*/

#include "Deltatime.hpp"

double Deltatime::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return millis.count();
}