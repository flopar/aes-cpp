#include "utility.hpp"
#include <iostream>


std::array<uint8_t, 4> wordToByteArray(uint32_t word){
	std::array<uint8_t, 4> arr;
	for(uint8_t i=0; i<4; i++){
		arr[i] = ((word & (0xFF<<(8*i)))>>(8*i));
	}
	return arr;
}

std::vector<uint8_t> wordToByteVector(uint32_t word){
	std::vector<uint8_t> vec;
	for(uint8_t i=0; i<4; i++){
		vec.emplace_back((word & (0xFF<<(8*i)))>>(8*i));
	}
	return vec;
}

uint32_t bytesToWord(const std::array<uint8_t, 4> bytes){
	uint32_t word=0;
	for(uint8_t i=0; i<4; i++){
		word |= (bytes[i] << (i*8));
	}
	return word;
}



