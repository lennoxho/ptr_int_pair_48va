#pragma once

#include "immutable_string.h"

struct string_compare_loose {
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    lt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() < rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) < 0);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    gt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() > rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) > 0);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    eq(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        return lhs.c_str() == rhs.c_str() || (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0);
    }
};

struct string_compare_weak {
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    lt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    gt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    eq(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        return lhs.c_str() == rhs.c_str() || (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0);
    }
};

struct string_compare_safe {
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    lt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    gt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    eq(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return true;
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::strncmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
};

struct string_compare_pendatic {
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    lt(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    gt(const Lhs &lhs,
        const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return false;
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Lhs, typename Rhs>
    static inline std::enable_if_t<is_comparable_as_immutable_strings<Lhs, Rhs>::value, bool>
    eq(const Lhs &lhs,
       const Rhs &rhs) noexcept
    {
        if (lhs.c_str() == rhs.c_str()) return true;
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::memcmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
};
