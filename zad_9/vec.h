// Konrad Kotlicki (310958)
#pragma once

template <typename T>
class vec
{
    T *pfirst, *pend, *plast;

public:
    static const int growSizeBy = 8;

    explicit vec(unsigned int s = 0)
    {
        pfirst = new T[s];
        pend =  plast = pfirst + s;
    }

    vec(const vec& other)
    {
        pfirst = new T[other.size()];
        pend = plast = pfirst + other.size();
        std::copy(other.pfirst, other.pend, pfirst);
    }

    vec(std::initializer_list<T> lst)
    {
        pfirst = new T[lst.size()];
        pend = plast = pfirst + lst.size();
        std::copy(lst.begin(), lst.end(), pfirst);
    }

    ~vec()
    {
        delete[] pfirst;
    }

    vec& operator= (const vec& rhs) {
        if (this == &rhs) return *this;
        if (capacity() < rhs.size()) {
            delete[] pfirst;
            pfirst = new T[rhs.size()];
        }
        pend = plast = pfirst + rhs.size();
        std::copy(rhs.pfirst, rhs.pend, pfirst);
        return *this;
    }

    unsigned int size() const
    {
        return pend - pfirst;
    }

    unsigned int capacity() const
    {
        return plast - pfirst;
    }

    T& operator[](unsigned int idx)
    {
        if(idx >= size()) throw std::out_of_range("Index out of range");
        return *(pfirst + idx);
    }

    const T& operator[](unsigned int idx) const
    {
        if (idx >= size()) throw std::out_of_range("Index out of range");
        return *(pfirst + idx);
    }

    void push_back(const T& val)
    {
        if (pend == plast)
        {
            unsigned int sz = size() + growSizeBy;
            T* ptab = new T[sz];
            std::copy(pfirst, pend, ptab);
            pend = ptab + size();
            plast = ptab + sz;
            delete[] pfirst;
            pfirst = ptab;
        }
        *pend = val;
        ++pend;
    }

    T pop_back()
    {
        if(pfirst == pend)
            throw std::out_of_range("Index out of range");
        --pend;
        return *pend;
    }
};
