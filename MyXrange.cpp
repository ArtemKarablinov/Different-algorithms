#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>

using namespace std;

template <typename T>
class TRange {
    using TDiff = decltype(T() - T());
public:
    TRange(T start, T finish)
        : Start(start) // список инициализации
        , Finish(finish)
    {
        if (finish < start) {
            throw std::runtime_error("Finish < Start");
        }
    }

    class TIterator {
    public:
        using value_type = T;
        using difference_type = TDiff;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using iterator_tag_type = forward_iterator_tag;

        TIterator(T value)
            : Value(value)
        {}

        T operator * () { // переопределение оператора разыменования(взять значение на которое указываем)
            return Value;
        }

        TIterator& operator ++ () { // переопредение оператора сдвига вправо
            ++Value;
            return *this;
        }

        bool operator == (const TIterator& other) {
            return Value == other.Value;
        }

        bool operator != (const TIterator& other) {
            return Value != other.Value;
        }
    private:
        T Value;
    };

    using iterator = TIterator;
    using const_iterator = TIterator;

    TIterator begin() {
        return TIterator(Start);
    }

    TIterator end() {
        return TIterator(Finish);
    }

    T size() {
        return Finish - Start;
    }
private:
    T Start;
    T Finish;
};

template <typename T>
TRange<T> xrange(T start, T finish) {
    return TRange<T>(start, finish);
}

template <typename T>
TRange<T> xrange(T finish) {
    return TRange<T>(0, finish);
}

int main()
{
    for (auto i : xrange(5)) {
        cout << i << endl;
    }
    return 0;
}
