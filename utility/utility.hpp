#include <array>
#include <vector>
#include <string>
#include <algorithm>

/* --- Conversion --- */

std::array<uint8_t, 4> wordToByteArray(uint32_t word);
std::vector<uint8_t> wordToByteVector(uint32_t word);
uint32_t bytesToWord(const std::array<uint8_t, 4> bytes);
uint32_t bytesToWord(std::vector<uint8_t> bytes);
std::vector<uint8_t>stringToBytes(std::string str);
std::string byteToString(std::vector<uint8_t> bytes);
uint8_t byteUpperBits(const uint8_t byte);
uint8_t byteLowerBits(const uint8_t byte);


