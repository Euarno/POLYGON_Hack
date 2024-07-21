#pragma once
#include <vector>
#include <algorithm>
#include <memory>

// 观察者基类
template <typename T>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const T& message_from_subject) = 0;
};

// 被观察者基类
template <typename T>
class Subject {
public:
    void Attach(std::shared_ptr<Observer<T>> observer) noexcept {
        observers_.emplace_back(std::move(observer));
    }

    void Detach(const std::shared_ptr<Observer<T>>& observer) noexcept {
        std::erase(observers_, observer);
    }

    void Notify(const T& message) const noexcept {
        for (const auto& observer : observers_) {
            observer->Update(message);
        }
    }

private:
    std::vector<std::shared_ptr<Observer<T>>> observers_;
};
