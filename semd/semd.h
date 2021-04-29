#pragma once
#if !defined(_SEMD_H_)
#define _SEMD_H_

#include <initializer_list>
#include <memory>
#include <sse_math_x86_lib.h>
#include <vector>

template <typename fp_type> class semd
{
  public:
    semd(std::initializer_list<fp_type> const &l);
    explicit semd(std::vector<fp_type> const &vec);
    explicit semd(std::size_t const &size);
    explicit semd(std::size_t const &size, fp_type const &val);

    ~semd()
    {
        sse_utility::aligned_free<fp_type>(raw_data_);
    }

    semd(semd<fp_type> const &cpy);
    semd(semd<fp_type> &&other) noexcept;
    semd &operator=(semd<fp_type> const &cpy);
    semd &operator=(semd<fp_type> &&other) noexcept;

    inline fp_type *data() const
    {
        return raw_data_;
    }

    inline const std::size_t size() const
    {
        return size_;
    }

    inline const fp_type operator[](std::size_t idx) const
    {
        return raw_data_[idx];
    }

  private:
    std::size_t size_;
    fp_type *raw_data_{nullptr};
};

template <typename fp_type> semd<fp_type>::semd(std::initializer_list<fp_type> const &l)
{
    size_ = l.size();
    raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
    std::copy(l.begin(), l.end(), raw_data_);
}

template <typename fp_type> semd<fp_type>::semd(std::vector<fp_type> const &vec)
{
    size_ = vec.size();
    raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
    std::copy(vec.begin(), vec.end(), raw_data_);
}

template <typename fp_type> semd<fp_type>::semd(std::size_t const &size)
{
    size_ = size;
    raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
}

template <typename fp_type> semd<fp_type>::semd(std::size_t const &size, fp_type const &val)
{
    size_ = size;
    raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
    std::fill(raw_data_, raw_data_ + size_, val);
}

template <typename fp_type> semd<fp_type>::semd(semd<fp_type> const &cpy)
{
    size_ = cpy.size_;
    raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
    std::copy(cpy.raw_data_, cpy.raw_data_ + size_, raw_data_);
}

template <typename fp_type> semd<fp_type>::semd(semd<fp_type> &&other) noexcept
{
    size_ = std::move(other.size_);
    raw_data_ = std::move(other.raw_data_);
    other.raw_data_ = nullptr;
}

template <typename fp_type> semd<fp_type> &semd<fp_type>::operator=(semd<fp_type> const &cpy)
{
    if (this != &cpy)
    {
        if (raw_data_)
            sse_utility::aligned_free<fp_type>(raw_data_);
        size_ = cpy.size_;
        raw_data_ = sse_utility::aligned_alloc<fp_type>(size_, 16);
        std::copy(cpy.raw_data_, cpy.raw_data_ + size_, raw_data_);
    }
    return *this;
}

template <typename fp_type> semd<fp_type> &semd<fp_type>::operator=(semd<fp_type> &&other) noexcept
{
    if (this != &other)
    {
        if (raw_data_)
            sse_utility::aligned_free<fp_type>(raw_data_);
        size_ = std::move(other.size_);
        raw_data_ = std::move(other.raw_data_);
        other.raw_data_ = nullptr;
    }
    return *this;
}

#endif ///_SEMD_H_
