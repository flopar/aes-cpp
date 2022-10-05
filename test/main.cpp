#include <aes.hpp>
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
/*
	math::matrix<uint8_t>mat;
	mat.print();
	math::matrix<uint8_t>mat1(2,2);
	mat1.print();
	std::vector<uint8_t> t{3,3};
	mat1.addColumn(t);
	mat1.print();
	std::vector<uint8_t> h = {2,2};
	math::vector<uint8_t>test(h, true);
	mat1.addColumn(test);
	mat1.print();
	std::vector<uint8_t> g = {0,0,0,0};
	math::vector<uint8_t>gtest(g);

	mat1.replaceRow(gtest, 1);
	mat1.print();
	std::vector<uint8_t>c0{5,5};
	math::vector<uint8_t>cTest(c0, true);
	math::matrix<uint8_t> mat2 = mat1;	
	mat2.replaceColumn(cTest, 3);
	mat2.print();
	mat1.print();
	math::matrix<uint8_t> mat3 = mat1^mat2;
	mat3.print();
	
	std::vector<uint8_t> vec1 = {1,2};
	std::vector<uint8_t> vec2 = {3,4};
	math::vector<uint8_t> vt1(vec1);
	math::vector<uint8_t> vt2(vec2);
	vt1.print();
	vt2.print();
	//math::vector<uint8_t> vt3 = vt1^vt2;
	//vt3.print();
	vt1^=vt2;
	vt1.print();*/
	// INFO: AES(key, message)
	std::vector<uint8_t> test = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	std::vector<uint8_t> test1 = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	std::string message = "", key ="";
	for(uint8_t i=0; i<test.size(); i++){
		message += (char)test[i];
		key += (char)test1[i];
	}
	//AES t = AES("SuperSecretKey3!","SuperSecretMessg");
	//t.encrypt();
	AES t = AES(key, message);
	t.encrypt();
	std::cout << t.getMessage();
	return 0;



/*
	math::vector<uint8_t>test1;
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
