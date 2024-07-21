#pragma once

template <typename T>
class SingleWrapper {
protected:
    SingleWrapper() = default;
    ~SingleWrapper() = default;

    // 禁用拷贝构造和赋值操作
    SingleWrapper(const SingleWrapper&) = delete;
    SingleWrapper& operator=(const SingleWrapper&) = delete;
    SingleWrapper(SingleWrapper&&) = delete;
    SingleWrapper& operator=(SingleWrapper&&) = delete;

public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
};
