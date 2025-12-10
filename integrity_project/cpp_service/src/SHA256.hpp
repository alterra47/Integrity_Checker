#pragma once
#include <string>
#include <vector>
#include <cstdint> //allows use of uint32_t, uint64_t, uint8_t
class SHA256{
    public:
    SHA256();
    void update(const std::vector<uint8_t>& data);
    std::string final();
    private:
    uint64_t state[8]; //8 hash values ; h0 to h7
    uint64_t bit_len; //total length of data processed
    std::vector<uint8_t> buffer; //Buffer for leftover data

    void transform(const uint8_t* data); // core compression function
};