/**
 * HexStreamer
 * Author: Erno Pakarinen
 * Date: September 5th, 2021
 * 
 * This is a simple class which converts between ASCII hex string and integer 
 * type of any size.
 * 
 * Provides 3 predefined conversion types, 8, 16 and 32 bit integers.
 * 
 * See main() for an example how to use.
 * 
 * But the basic usage is:
 * 
 *      char src[] = "0102030405060708090a0b0c0d0e0f";
 *      HexInt8 b1;
 *      HexInt16 w1;
 *      HexInt32 l1;
 *
 *      std::string hexStr("0f01310a123141);
 *      std::istringstream input(hexStr);
 *
 *      input >> b1 >> w1 >> l1;
 *      cout << b1 >> w1 << l1;
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cassert>

/**
 * Template class which converts between ASCII hex string and integer
 * Not for concrete use, use type defines provided below HexIntClass
 * 
 *      typedef HexIntClass<uint8_t, 2> HexInt8;
 *      typedef HexIntClass<uint16_t, 4> HexInt16;
 *      typedef HexIntClass<uint32_t, 8> HexInt32;
 *
 * Templated to get the concrete integer type and size of the type
 */
template<typename T, size_t S>
class HexIntClass
{
public:
    HexIntClass() : m_data(0) {};
    ~HexIntClass() {};

    /**
     * Write as ASCII to given stream as hex string (without 0x) allowing
     * conversion back from integer to string format
     */
    friend std::ostream& operator<<(std::ostream& os, HexIntClass& D) {
        std::ios_base::fmtflags f(os.flags());  // save flags state
        os.setf(std::ios_base::hex, std::ios_base::basefield);
        os.setf(std::ios_base::uppercase);
        os << std::setw(S) << std::setfill('0') << (int)D.data();
        os.flags(f);  // restore flags state
        return os;
    }

    /**
     * Read from stream and convert to integer
     */
    friend std::istream& operator>>(std::istream& is, HexIntClass& D) {
        char hexbyte[S + 1];
        if (is.read(hexbyte, S)) {
            hexbyte[S] = 0;
            D.m_data = (T)strtol(hexbyte, NULL, 16);
        }
        return is;
    }

    bool operator==(const T& other) const {
        return other == data();
    }

    bool operator==(const HexIntClass& other) const {
        return other.data() == data();
    }

    T operator()() {
        return m_data;
    }

    T data() const {
        return m_data;
    }
private:
    T m_data;
};

typedef HexIntClass<uint8_t, 2> HexInt8;
typedef HexIntClass<uint16_t, 4> HexInt16;
typedef HexIntClass<uint32_t, 8> HexInt32;

int main(void) {
    HexInt8 b1, b2;
    HexInt16 w1, w2;
    HexInt32 l1, l2;

    std::string hexStr("0102030405060708090a0b0c0d0e0f");
    std::istringstream input(hexStr);

    std::cout << "Source string: " << hexStr << std::endl;
    std::cout << "Converting from hex string to integers:\n";
    // should produce:
    // b1 = 0x01, b2 = 0x02;
    // w1 = 0x0304, w2 = 0x0506
    // l1 = 0x0708090a, l2 = 0x0b0c0d0e
    input >> b1 >> b2 >> w1 >> w2 >> l1 >> l2;

    // verify results with blunt assers in this demo
    assert(b1.data() == 0x01);
    assert(b2.data() == 0x02);
    assert(w1.data() == 0x0304);
    assert(w2.data() == 0x0506);
    assert(l1.data() == 0x0708090a);
    assert(l2.data() == 0x0b0c0d0e);

    std::cout << "Byte1: " << b1 << " - Byte2: " << b2 << std::endl;
    std::cout << "Word1: " << w1 << " - Word2: " << w2 << std::endl;
    std::cout << "Long1: " << l1 << " - Long2: " << l2 << std::endl;

    std::cout << "\nAnd converting back to ASCII from integers:\n";
    std::cout << "Byte1: " << b1 << " Byte2: " << b2 << std::endl;
    std::cout << "Word1: " << w1 << " Word2: " << w2 << std::endl;
    std::cout << "Long1: " << l1 << " Long2: " << l2 << std::endl;
    std::cout << "Finito!\n";
    return 0;
}
