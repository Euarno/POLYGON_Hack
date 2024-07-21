#pragma once
#include <iostream>
#include <format>
#include <mutex>
#include <Windows.h>
#include "../DesignPattern/SingleWrapper.h"

enum class ConsoleColor {
    Black = 0,
    DarkBlue = 1,
    DarkGreen = 2,
    DarkCyan = 3,
    DarkRed = 4,
    DarkMagenta = 5,
    DarkYellow = 6,
    Gray = 7,
    DarkGray = 8,
    Blue = 9,
    Green = 10,
    Cyan = 11,
    Red = 12,
    Magenta = 13,
    Yellow = 14,
    White = 15,

    BackgroundBlack = 0x00,
    BackgroundDarkBlue = 0x10,
    BackgroundDarkGreen = 0x20,
    BackgroundDarkCyan = 0x30,
    BackgroundDarkRed = 0x40,
    BackgroundDarkMagenta = 0x50,
    BackgroundDarkYellow = 0x60,
    BackgroundGray = 0x70,
    BackgroundDarkGray = 0x80,
    BackgroundBlue = 0x90,
    BackgroundGreen = 0xA0,
    BackgroundCyan = 0xB0,
    BackgroundRed = 0xC0,
    BackgroundMagenta = 0xD0,
    BackgroundYellow = 0xE0,
    BackgroundWhite = 0xF0
};

class ConsoleContext : public SingleWrapper<ConsoleContext> {
private:
    void SetToDefault() {
        SetTextColor(m_DefaultColor);
        //SetBackgroundColor(m_DefaultBackgroundColor);
    }
public:
    ConsoleContext() noexcept = default;

    ~ConsoleContext() noexcept = default;

    bool Alloc() noexcept {
        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        return m_ConsoleHandle != nullptr;
    }

    void SetTextColor(ConsoleColor color) noexcept {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(color));
    }

    //void SetBackgroundColor(ConsoleColor color) noexcept {
    //    CONSOLE_SCREEN_BUFFER_INFO info;
    //    GetConsoleScreenBufferInfo(m_ConsoleHandle, &info);
    //    WORD currentAttributes = info.wAttributes;
    //    WORD newAttributes = (currentAttributes & 0x0F) | static_cast<WORD>(color);
    //    SetConsoleTextAttribute(m_ConsoleHandle, newAttributes);
    //}

    bool Free() noexcept {
        return FreeConsole();
    }

    template<typename... Args>
    void Output(ConsoleColor color, const std::string& format, Args&&... args) noexcept {
        std::lock_guard<std::mutex> lock(m_Mutex);
        SetTextColor(color);
        std::cout << std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
 
    }

    template<typename... Args>
    void Output(const std::string& format, Args&&... args) noexcept {
        std::lock_guard<std::mutex> lock(m_Mutex);
        SetToDefault();
        std::cout << std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
    }
private:
    HANDLE m_ConsoleHandle = nullptr;
    ConsoleColor m_DefaultColor = ConsoleColor::White;  // Default color to reset to
    ConsoleColor m_DefaultBackgroundColor = ConsoleColor::BackgroundBlack;  // Default color to reset to
    std::mutex m_Mutex;  // Mutex for synchronizing access
};
