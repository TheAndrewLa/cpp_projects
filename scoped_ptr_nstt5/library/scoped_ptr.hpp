#pragma once
#include <type_traits>

template <typename t>
class ScopedPtrMove {
    public:
    ScopedPtrMove() = delete;

    explicit ScopedPtrMove(t* raw_ptr) : raw_(raw_ptr) {}

    ScopedPtrMove(const ScopedPtrMove& ptr) = delete;

    ScopedPtrMove(ScopedPtrMove&& ptr) : raw_(ptr.raw_) {
        ptr.raw_ = nullptr;
    }

    ~ScopedPtrMove() {
        delete raw_;
    }

    ScopedPtrMove& operator=(ScopedPtrMove&& other) {
        delete this->raw_;

        this->raw_ = other.raw_;
        other.raw_ = nullptr;

        return *this;
    }

    t* operator->() {
        return this->raw_;
    }

    t& operator*() {
        return *this->raw_;
    }

    private:
    t* raw_ {nullptr};
};

template <typename t>
class ScopedPtrCopy {
    public:
    ScopedPtrCopy() = delete;

    explicit ScopedPtrCopy(t* raw_ptr) : raw_(raw_ptr) {
        static_assert(std::is_copy_constructible<t>(), "Type should has copy ctor");
    }

    ScopedPtrCopy(const ScopedPtrCopy& ptr) {
        static_assert(std::is_copy_constructible<t>(), "Type should has copy ctor");
        this->raw_ = new t(*ptr.raw_);
    }

    ScopedPtrCopy(ScopedPtrCopy&& ptr) {
        static_assert(std::is_copy_constructible<t>(), "Type should has copy ctor");
        this->raw_ = new t(*ptr.raw_);
        ptr.raw_ = nullptr;
    }

    ~ScopedPtrCopy() {
        delete raw_;
    }

    ScopedPtrCopy& operator=(const ScopedPtrCopy& other) {
        static_assert(std::is_copy_constructible<t>(), "Type should has copy ctor");

        delete this->raw_;
        this->raw_ = new t(*other.raw_);

        return *this;
    }

    t* operator->() {
        return this->raw_;
    }

    t& operator*() {
        return *this->raw_;
    }

    private:
    t* raw_;
};
