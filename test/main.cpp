include <aes.hpp>
#include <iostream>

void testSUG(AES test){
	std::cout << "object's current key: " << test.getKey() << std::endl << "object's current message: " << test.getMessage() << std::endl;
	std::string key = "SuperKey";
	std::string message = "SuperMessage";
	std::cout << "Setting new message and key...\n";
	test.setKey(key);
	test.setMessage(message);
	std::cout << "object's current key: " << test.getKey() << std::endl << "object's current message: " << test.getMessage() << std::endl;
}


int main(){
	// AES(key, message)
	AES t = AES("SuperSecretKey3!","SuperSecretMessg");
	t.encrypt();
	return 0;
}
