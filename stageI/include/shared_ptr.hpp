#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__

#pragma once

#ifndef __TYPES_HPP__
#include <types.hpp>
#endif

namespace std
{
    template <>
    class shared_ptr<NONTERMINALTYPE>
    {
    public:
        using type = NONTERMINALTYPE;
        using type_ptr = type *;
        using type_ref = type &;

    private:
        type_ptr data = nullptr;
        unsigned long int *count = nullptr;

    public:
        shared_ptr() = default;
        shared_ptr(string);
        ~shared_ptr();

        shared_ptr(const shared_ptr &s) : data{s.data}, count{s.count}
        {
            if (count != nullptr)
                *count += 1;
        }
        shared_ptr(shared_ptr &&s) : data{move(s.data)}, count{move(s.count)}
        {
            s.data = nullptr;
            s.count = nullptr;
        }

        shared_ptr &operator=(const shared_ptr &s);

        shared_ptr &operator=(shared_ptr &&s);

        bool unique() const
        {
            return data != nullptr && count != nullptr && *count == 1;
        }

        bool operator==(const shared_ptr &x) const;

        bool operator!=(const shared_ptr &x) const
        {
            return !(*this == x);
        }

        bool operator!=(const std::nullptr_t) const
        {
            return data != nullptr;
        }
        bool operator==(const std::nullptr_t) const
        {
            return data == nullptr;
        }

        type_ref operator->() const;
        RULESTYPE &getRules() const;
        string &getName() const;

        type_ref operator*() const
        {
            return *data;
        }

        void add(const shared_ptr<RULETYPE> &r) const;

        template <typename stream>
        friend stream &operator<<(stream &o, const shared_ptr &s)
        {
            if (s.data == nullptr)
                throw NonTerminalNotSet{};
            o << *s.data;
            return o;
        }
        bool hasLeftFactoring() const;
        RULESTYPE getleftFactoring() const;


        friend class shared_ptr<RULETYPE>;
    };

    template <>
    class shared_ptr<TERMINALTYPE>
    {
    public:
        using type = TERMINALTYPE;
        using type_ptr = type *;
        using type_ref = type &;

    private:
        type_ptr data = nullptr;
        unsigned long int *count = nullptr;

    public:
        shared_ptr() = default;
        shared_ptr(string, string);
        shared_ptr(string, TerminalType, string);
        ~shared_ptr();

        shared_ptr(const shared_ptr &s) : data{s.data}, count{s.count}
        {
            if (count != nullptr)
                *count += 1;
        }
        shared_ptr(shared_ptr &&s) : data{move(s.data)}, count{move(s.count)}
        {
            s.data = nullptr;
            s.count = nullptr;
        }

        shared_ptr &operator=(const shared_ptr &s);

        shared_ptr &operator=(shared_ptr &&s);

        bool unique() const
        {
            return data != nullptr && count != nullptr && *count == 1;
        }

        bool operator==(const shared_ptr &x) const;

        bool operator!=(const shared_ptr &x) const
        {
            return !(*this == x);
        }

        bool operator!=(const std::nullptr_t) const
        {
            return data != nullptr;
        }
        bool operator==(const std::nullptr_t) const
        {
            return data == nullptr;
        }

        type_ref operator*() const
        {
            return *data;
        }

        type_ref operator->() const
        {
            return *data;
        }

        template <typename stream>
        friend stream &operator<<(stream &o, const shared_ptr &s)
        {
            if (s.data == nullptr)
                throw TerminalNotSet{};
            o << *s.data;
            return o;
        }

        const static shared_ptr<TERMINALTYPE> &EPSILON;
        const static shared_ptr<TERMINALTYPE> &DOLLAR;
    };

    template <>
    class shared_ptr<RULESTYPE>
    {
    public:
        using type = RULESTYPE;
        using type_ptr = type *;
        using type_ref = type &;

    private:
        type_ptr data = nullptr;
        unsigned long int *count = nullptr;

    public:
        shared_ptr();
        ~shared_ptr();

        shared_ptr(const shared_ptr &s) : data{s.data}, count{s.count}
        {
            if (count != nullptr)
                *count += 1;
        }

        shared_ptr(shared_ptr &&s) : data{move(s.data)}, count{move(s.count)}
        {
            s.data = nullptr;
            s.count = nullptr;
        }

        shared_ptr &operator=(const shared_ptr &s);

        shared_ptr &operator=(shared_ptr &&s);

        bool unique() const
        {
            return data != nullptr && count != nullptr && *count == 1;
        }

        bool operator==(const shared_ptr &x) const;

        bool operator!=(const shared_ptr &x) const
        {
            return !(*this == x);
        }

        bool operator!=(const std::nullptr_t) const
        {
            return data != nullptr;
        }
        bool operator==(const std::nullptr_t) const
        {
            return data == nullptr;
        }

        type_ref operator*() const
        {
            return *data;
        }

        type_ref operator->() const
        {
            return *data;
        }

        template <typename stream>
        friend stream &operator<<(stream &o, shared_ptr &s)
        {
            if (s.data == nullptr)
                throw RulesNotSet{};
            o << *s.data;
            return o;
        }
    };

    template <>
    class shared_ptr<RULETYPE>
    {
    public:
        using type = RULETYPE;
        using type_ptr = type *;
        using type_ref = type &;

    private:
        type_ptr data = nullptr;
        unsigned long int *count = nullptr;

    public:
        shared_ptr();
        shared_ptr(const shared_ptr<NONTERMINALTYPE> &);
        ~shared_ptr();

        shared_ptr(const shared_ptr &s) : data{s.data}, count{s.count}
        {
            if (count != nullptr)
                *count += 1;
        }

        shared_ptr(shared_ptr &&s) : data{move(s.data)}, count{move(s.count)}
        {
            s.data = nullptr;
            s.count = nullptr;
        }

        shared_ptr &operator=(const shared_ptr &s);

        shared_ptr &operator=(shared_ptr &&s);

        bool unique() const
        {
            return data != nullptr && count != nullptr && *count == 1;
        }

        bool operator==(const shared_ptr &x) const;

        bool operator!=(const shared_ptr &x) const
        {

            if (data == nullptr || x.data == nullptr)
                return false;
            return !(*this == x);
        }

        bool operator!=(const std::nullptr_t) const
        {
            return data != nullptr;
        }
        bool operator==(const std::nullptr_t) const
        {
            return data == nullptr;
        }

        type_ref operator*() const
        {
            return *data;
        }

        type_ptr operator->() const
        {
            return data;
        }

        template <typename stream>
        friend stream &operator<<(stream &o, const shared_ptr &s)
        {
            if (s.data == nullptr)
                throw RuleNotSet{};
            o << *s.data;
            return o;
        }

        bool isNull() const;
        bool isUnitProduction() const;

        shared_ptr<NONTERMINALTYPE> &getLeft() const;
        vector<shared_ptr<RightAssociate>> &getRight() const;
        vector<shared_ptr<RightAssociate>> getRightFrom(long unsigned int j) const;

        size_t countOccurrence(const shared_ptr<NONTERMINALTYPE> &p) const;

        shared_ptr removeFromOccurrence(const shared_ptr<NONTERMINALTYPE> &p, size_t j) const;
    };

    template <>
    class shared_ptr<RightAssociate>
    {
    public:
        using type = RightAssociate;
        using type_ptr = type *;
        using type_ref = type &;

    private:
        type_ptr data = nullptr;
        unsigned long int *count = nullptr;

    public:
        shared_ptr() = default;
        shared_ptr(RightAssociateType, variant<shared_ptr<NONTERMINALTYPE>, shared_ptr<TERMINALTYPE>>);
        ~shared_ptr();

        shared_ptr(const shared_ptr &s) : data{s.data}, count{s.count}
        {
            if (count != nullptr)
                *count += 1;
        }

        shared_ptr(shared_ptr &&s) : data{move(s.data)}, count{move(s.count)}
        {
            s.data = nullptr;
            s.count = nullptr;
        }

        shared_ptr &operator=(const shared_ptr &s);

        shared_ptr &operator=(shared_ptr &&s);

        bool unique() const
        {
            return data != nullptr && count != nullptr && *count == 1;
        }

        bool operator==(const shared_ptr &x) const
        {

            if (data == nullptr || x.data == nullptr)
                return false;
            return *data == *x.data;
        }

        bool operator!=(const shared_ptr &x) const
        {
            if (data == nullptr || x.data == nullptr)
                return false;
            return !(*this == x);
        }

        bool operator==(const shared_ptr<TERMINALTYPE> &x) const;

        bool operator!=(const shared_ptr<TERMINALTYPE> &x) const;

        bool operator==(const shared_ptr<NONTERMINALTYPE> &x) const;

        bool operator!=(const shared_ptr<NONTERMINALTYPE> &x) const;

        bool operator!=(const std::nullptr_t) const
        {
            return data != nullptr;
        }
        bool operator==(const std::nullptr_t) const
        {
            return data == nullptr;
        }

        type_ref operator*() const
        {
            return *data;
        }

        type_ref operator->() const
        {
            return *data;
        }

        template <typename stream>
        friend stream &operator<<(stream &o, shared_ptr &s)
        {
            if (s.data == nullptr)
                throw RightAssociateNotSet{};
            o << *s.data;
            return o;
        }
    };

} // namespace std

#endif // __SHARED_PTR_HPP__