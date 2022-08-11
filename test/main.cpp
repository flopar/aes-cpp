#include <aes.hpp>
#include <iostream>
#include <vector.hpp>
#include <matrix.hpp>

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

	math::matrix<uint8_t>mat;
	mat.print();
	math::matrix<uint8_t>mat1(2,2);
	mat1.print();
	std::vector<uint8_t> t{3,3};
	mat1.addRow(t);
	mat1.print();














	return 0;


	// INFO: AES(key, message)
	/*AES t = AES("SuperSecretKey3!","SuperSecretMessg");
	t.encrypt();
	*/

/*
	math::vector<uint8_t>test1;
	std::vector<uint8_t> h = {2,2,2};
	math::vector<uint8_t>test(h);
	uint8_t var = 2;
	test1.push_back(var);
	test1.push_back(var);
	test1.push_back(var);
	


	math::vector<uint8_t> check;
	(test + test1).print();
	


	check.print();
	check.setTranspose(true);
	check.print();
	std::cout << test*test1;
	std::cout << "\ncheck at 2:" << test.at(1);
*/	
}
