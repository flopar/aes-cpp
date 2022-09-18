#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
#include <array>
#include <algorithm>

#include <bitset>

#include "lookup.hpp"
#include <utility.hpp>
#include <matrix.hpp>
class AES{
	private:
		//Members
		std::string mKey;
		std::string mMessage;
		size_t mMessageSize = 0;
		size_t mKeySize = 0;
		/* Nb = Number of columns (32-bit) comprising(=consists of) the State. 
		 * For this standard, Nb = 4
		 * Nk = Number of 32-bit words comprising the Cypher Key. 
		 * For the AES standard Nk = 4, 6 or 8
		 * Nr = Number of rounds, which is a function of Nk and Nb(which is fixed).
		 * For this standard, Nr = 10, 12 or 14 */
		uint8_t Nb = 0, Nk = 0, Nr = 0;	
		
		// Functions
		/* --- Key expansion --- */
		void expandKey(std::vector<unsigned int>& wordList);
		void rotateWord(unsigned int& word);
		void substituteWord(unsigned int& word);
		void substituteByte(uint8_t& byte);
		
		std::vector<std::vector<uint8_t>> createStateMatrix();
		void addRoundKey(const uint8_t round, const std::vector<unsigned int>& keyList, const math::matrix<uint8_t>& stateMatrix);
	
		/* --- Utility --- */
		void printMatrix(const std::vector<std::vector<uint8_t>>& matrix);
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

