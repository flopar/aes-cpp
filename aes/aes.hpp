#include <string>
#include "utility.hpp"
#include <vector>

class AES{
	private:
		std::string mKey = "";
		std::string mMessage = "";
		size_t mMessageLength = 0;
		size_t mKeyLength = 0;
		

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
