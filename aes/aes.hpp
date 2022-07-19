#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include "lookup.hpp"

class AES{
	private:
		//Members
		std::string mKey = "";
		std::string mMessage = "";
		size_t mMessageSize = 0;
		size_t mKeySize = 0;
		uint8_t Nb = 0, Nk = 0, Nr = 0;	
		
		// Functions
		/* --- Key expansion --- */
		int expandKey(std::vector<unsigned int>& wordList);
		void rotateWord(unsigned int& word);
		void substituteWord(unsigned int& word);
		void substituteByte(uint8_t& byte);

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

