HexStreamer

Author: Erno Pakarinen (aka codesmith_fi)
Date: September 5th, 2021
MIT License, see LICENSE file

This is simple class which converts between ASCII hex string and integer type
of any size.

Provides 3 predefined conversion types, 8, 16 and 32 bit integers.

See main() for an example how to use.

But the basic usage is:

     char src[] = "0102030405060708090a0b0c0d0e0f";
     HexInt8 b1;
     HexInt16 w1;
     HexInt32 l1;

     std::string hexStr("0f01310a123141);
     std::istringstream input(hexStr);

     input >> b1 >> w1 >> l1;
     cout << b1 >> w1 << l1;

Feel free to use in any way you want if you find this useful.
