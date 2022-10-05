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
		std::rotate(vec.rbegin(), vec.rbegin()+1, vec.rend());
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

uint32_t bytesToWord(const std::vector<uint8_t> bytes){
	if(bytes.size() != 4){
		throw std::length_error("bytesToWord(): passed vector's size does not equal to 4");
	}
	uint32_t word=0;
	for(uint8_t i=0; i<4;i++){
		word |= (bytes[i] << (i*8));
	}
	return word;
}

uint8_t byteUpperBits(const uint8_t byte){
	return ((byte & 0xF0) >> 4);
}

uint8_t byteLowerBits(const uint8_t byte){
	return (byte & 0x0F);
}
