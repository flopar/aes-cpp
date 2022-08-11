#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
#include <array>
#include "lookup.hpp"

class AES{
	private:
		//Members
		std::string mKey;
		std::string mMessage;
		size_t mMessageSize = 0;
		size_t mKeySize = 0;
		uint8_t Nb = 0, Nk = 0, Nr = 0;	
		
		// Functions
		/* --- Key expansion --- */
		int expandKey(std::vector<unsigned int>& wordList);
		void rotateWord(unsigned int& word);
		void substituteWord(unsigned int& word);
		void substituteByte(uint8_t& byte);
		
		std::vector<std::vector<uint8_t>> createStateMatrix();
		void addRoundKey(const uint8_t round, const std::vector<unsigned int>& keyList, std::vector<std::vector<uint8_t>>& stateMatrix);
	
		/* --- Utility --- */
		void printMatrix(const std::vector<std::vector<uint8_t>>& matrix);
		std::array<uint8_t, 4> wordToBytes(uint32_t word);
		uint32_t bytesToWord(std::array<uint8_t, 4> bytes);
	public:
		AES(const std::string key, std::string message);
		AES() noexcept;
		
		/* --- Setters & Getters -- */
		void setMessage(const std::string message);
		std::string getMessage() const;

		void setKey(const std::string key);
		std::string getKey() const;

		std::string encrypt();

};

