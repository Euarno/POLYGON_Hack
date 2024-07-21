#pragma once

template <typename T>
class SingleWrapper {
protected:
    SingleWrapper() = default;
    ~SingleWrapper() = default;

    // ���ÿ�������͸�ֵ����
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
