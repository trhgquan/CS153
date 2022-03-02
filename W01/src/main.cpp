#include<cassert>
#include<iostream>
#include<string>
#include<sstream>

class BigInt {
private:
    std::string _num;
    bool _negative;
private:
    /**
     * @brief Convert a char to int.
     * 
     * @param c char
     * @return int 
     */
    int _charIntToInt(char c) const {   
        return c - '0';
    }

    /**
     * @brief Reverse a string.
     * 
     * @param str const std::string&
     * @return std::string 
     */
    std::string _reverse(const std::string& str) const {
        return std::string(str.rbegin(), str.rend());
    }

    /**
     * @brief Remove leading zeros (00123 => 123)
     * 
     * @param  num const std::string&
     * @return std::string 
     */
    std::string _removeLeadingZeros(const std::string& num) const {
        std::stringstream ss;
        bool valid = false;
    
        for (int i = 0; i < (int)num.length(); ++i) {
            if (num[i] == '0' && !valid) {
                continue;
            }
            else {
                valid = true;
                ss << num[i];
            }
        }
    
        if (ss.str().length() == 0) {
            ss << 0;
        }

        return ss.str();
    }

    /**
     * @brief Add leading zeros (123, zeros = 4 => 0000123)
     * 
     * @param num std::string&
     * @param totalZeros int
     */
    void _addLeadingZeros(std::string& num, int totalZeros) const {
        std::stringstream ss;

        for (int i = 1; i <= totalZeros; ++i) {
            ss << 0;
        }
        ss << num;
        
        num = ss.str();
    }

    /**
     * @brief Add trailing zeros (123, zeros = 4 => 1230000)
     * 
     * @param num std::string&
     * @param totalZeros int
     */
    void _addTrailingZeros(std::string& num, int totalZeros) const {
        std::stringstream ss;

        ss << num;
        for (int i = 1; i <= totalZeros; ++i) {
            ss << 0;
        }

        num = ss.str();
    }

    /**
     * @brief Check if a number is valid (i.e only digits and minus mark)
     * 
     * @param num const std::string&
     * @return true if valid
     * @return false otherwise
     */
    bool _validate(const std::string& num) {
        for (int i = 0; i < (int)num.length(); ++i) {
            if (i == 0 && num[i] == '-') continue;
            else if (num[i] >= '0' && num[i] <= '9') continue;
            else return false;
        }
        return true;
    }

    /**
     * @brief Check if a number is negative (aka num[0] == '-')
     * 
     * @param num const std::string&
     * @return true if that number is a negative number
     * @return false otherwise
     */
    bool _isNegative(const std::string& num) {
        return num[0] == '-';
    }

    /**
     * @brief Absolute value of a negative number (aka str.substr(1, str.length() - 1))
     * 
     * @param num const std::string&
     * @return std::string 
     */
    std::string _absolute(const std::string& num) {
        return num.substr(1, num.length() - 1);
    }
public:
    BigInt() {
        // Do nothing
        _negative = false;
        _num = "0";
    }

    BigInt(const std::string& num) {
        if (!_validate(num)) {
            throw std::runtime_error("Invalid integer format");
        }

        _negative = _isNegative(num);

        _num = (_negative) ? _removeLeadingZeros(_absolute(num)) : _removeLeadingZeros(num);
    }

    BigInt(const std::string& num, bool negative) {
        _num = _removeLeadingZeros(num);
        _negative = negative;
    }

    BigInt(const BigInt& num) {
        _num = num._num;
        _negative = num._negative;
    }

    void operator=(const BigInt& num) {
        _num = num._num;
        _negative = num._negative;
    }
    
    ~BigInt() {
        // Do nothing
    }
public:
    bool isNegative() const {
        return _negative;
    }
public:
    char& operator[](const int index) {
        if (index < 0 || index > (int)_num.length()) {
            throw std::runtime_error("Index out of bound");
        }
        return _num[index];
    }

    bool operator<(const BigInt& num) const {
        // 2 số khác dấu => số nhỏ hơn chắc chắn là số âm
        if (num.isNegative() != isNegative()) {
            return isNegative();
        }

        // 2 số có độ dài khác nhau => tùy vào dấu mà đưa ra số nhỏ hơn.
        if (_num.length() != num._num.length()) {
            return (isNegative()) ? (_num.length() > num._num.length())
                                  : (_num.length() < num._num.length());
        }

        return isNegative() ? (_num > num._num) : (_num < num._num);
    }

    bool operator<(const std::string& num) const {
        return *this < BigInt(num);
    }

    bool operator>(const BigInt& num) const {
        return !(*this <= num);
    }

    bool operator>(const std::string& num) const {
        return *this > BigInt(num);
    }

    bool operator==(const BigInt& num) const {
        return (_num == num._num) && (_negative == num._negative);
    }
    
    bool operator==(const std::string& num) const {
        return *this == BigInt(num);
    }

    bool operator!=(const BigInt& num) const {
        return !(*this == num);
    }

    bool operator!=(const std::string& num) const {
        return *this != BigInt(num);
    }

    bool operator<=(const BigInt& num) const {
        return (*this == num || *this < num);
    }

    bool operator<=(const std::string& num) const {
        return *this <= BigInt(num);
    }

    bool operator>=(const BigInt& num) const {
        return (*this == num || *this > num);
    }

    bool operator>=(const std::string& num) const {
        return *this >= num;
    }

    BigInt operator+(const BigInt& num) const {
        // Xét dấu phép cộng.
        std::stringstream ss;

        std::string firstNum = _num;
        std::string secondNum = num._num;

        // Thêm số 0 vào trước để 2 string bằng nhau => tránh index out of bound.
        if ((int)_num.length() > (int)secondNum.length()) {
            _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
        }
        else if ((int)_num.length() < (int)secondNum.length()) {
            _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
        }

        // Cộng như hồi tiểu học (từ phải sang trái)
        int carry = 0;
        for (int i = (int)firstNum.length() - 1; i >= 0; --i) {
            int currentSum = _charIntToInt(firstNum[i]) + _charIntToInt(secondNum[i]) + carry;

            ss << currentSum % 10;
            carry = currentSum / 10;
        }

        if (carry > 0) {
            while (carry > 0) {
                ss << carry % 10;
                carry /= 10;
            }
        }

        return BigInt(_reverse(ss.str()));
    }

    BigInt operator+(const std::string& num) const {
        return *this + BigInt(num);
    }

    void operator+=(const BigInt& num) {
        // Goes brrr
        *this = *this + num;
    }

    void operator+=(const std::string& num) {
        *this += BigInt(num);
    }

    BigInt operator-(const BigInt& num) const {
        std::stringstream ss;

        std::string firstNum = _num;
        std::string secondNum = num._num;

        // Thêm số 0 vào trước để 2 string bằng nhau => tránh index out of bound.
        if ((int)_num.length() > (int)secondNum.length()) {
            _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
        }
        else if ((int)_num.length() < (int)secondNum.length()) {
            _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
        }
        
        // Swap order if firstNum < secondNum
        if (*this < num) {
            std::swap(firstNum, secondNum);
        }

        // Reverse both of strings
        firstNum = _reverse(firstNum);
        secondNum = _reverse(secondNum);

        int carry = 0;

        for (int i = 0; i < (int) firstNum.length(); i++) {
            int sub = _charIntToInt(firstNum[i]) - _charIntToInt(secondNum[i]) - carry;
            if (sub < 0) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;  
            }
            ss << sub;
        }

        return BigInt(_reverse(ss.str()));
    }

    BigInt operator-(const std::string& num) const {
        return *this - BigInt(num);
    }
 
    void operator-=(const BigInt& num) {
        *this = *this - num;
    }

    void operator-=(const std::string& num) {
        *this -= BigInt(num);
    }

    BigInt operator*(const BigInt& num) const {
        std::stringstream ss;

        std::string firstNum = _num;
        std::string secondNum = num._num;

        BigInt result;

        int carry = 0;
        for (int i = secondNum.length() - 1; i >= 0; --i) {
            if (secondNum[i] == '0') continue;
            for (int j = firstNum.length() - 1; j >= 0; --j) {
                int current_prod = _charIntToInt(firstNum[j]) * _charIntToInt(secondNum[i]) + carry;

                ss << current_prod % 10;
                carry = current_prod / 10;
            }

            while (carry > 0) {
                ss << carry % 10;
                carry /= 10;
            }

            std::string lineResult = _reverse(ss.str());
            _addTrailingZeros(lineResult, secondNum.length() - i - 1);

            result += BigInt(lineResult); ss.str("");
        }

        return result;
    }

    BigInt operator*(const std::string& num) const {
        return *this * BigInt(num);
    }

    void operator*=(const BigInt& num) {
        // Goes brrr
        *this = *this * num;
    }

    void operator*=(const std::string& num) {
        *this *= BigInt(num);
    }

    BigInt operator%(const BigInt& base) const {
        // Goes brrr
        if (base == "0") {
            throw std::runtime_error("Zero division encountered");
        }

        BigInt zero("0"), one("1"), ten("10");

        if (base == "1" || base == *this) {
            return zero;
        }

        if (base == "2") {
            int lastDigit = _charIntToInt(*prev(_num.end()));
            return !(lastDigit & 1) ? zero : one;
        }

        if (*this < base) {
            return *this;
        }

        // Modulo operator goes here
        BigInt currentNum = *this;

        while (currentNum > base) {
            BigInt currentBase = base;
            
            while (1) {
                BigInt tempBase = currentBase * ten;
                if (currentNum < tempBase) break;

                currentBase = tempBase;
            }
            
            currentNum -= currentBase;
        };

        return currentNum;
    }

    BigInt operator%(const std::string& base) const {
        return *this % BigInt(base);
    }

    void operator%=(const BigInt& num) {
        // Goes brrr
        *this = *this % num;
    }
public:
    static BigInt max(const BigInt& a, const BigInt& b) {
        return (a > b) ? a : b;
    }
    static BigInt modularAddition(const BigInt& a, const BigInt& b, const BigInt& m) {
        BigInt zero("0");
        assert(m > zero);
        BigInt first = (a >= zero) ? a : (m - a);
        BigInt second = (b >= zero) ? b : (m - b);
        return ((first % m) + (second % m)) % m;
    }
    static BigInt modularMultiplication(const BigInt& a, const BigInt& b, const BigInt& m) {
        BigInt zero("0");
        assert(m > zero);
        BigInt first = (a >= zero) ? a : m - a;
        BigInt second = (b >= zero) ? b : m - b;
        return ((first % m) * (second % m)) % m;
    }
public:
    friend std::istream& operator>>(std::istream& in, BigInt& num) {
        std::string s; in >> s; 
        num = BigInt(s);
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& num) {
        if (num.isNegative()) {
            out << '-';
        }
        out << num._num;
        return out;
    }
};

int main() {
    try {
        BigInt m; std::cout << "Moi thay nhap m = "; std::cin >> m;
        BigInt a; std::cout << "Moi thay nhap a = "; std::cin >> a;
        BigInt b; std::cout << "Moi thay nhap b = "; std::cin >> b;

        std::cout << "(a + b) % m = " << BigInt::modularAddition(a, b, m) << '\n';
        std::cout << "(a * b) % m = " << BigInt::modularMultiplication(a, b, m) << '\n';
    }
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}