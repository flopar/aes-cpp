#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <functional>

namespace math{
template<class T>
class vector{
	private:
		uint64_t mDimension;
		bool mTranspose;
		std::vector<T> mValues;

		/* --- Validity check --- */
		void checkValidity(const math::vector<T>& vec);
	public:
		vector();
		vector(const uint64_t dimension, const bool transpose = false);
		vector(const std::vector<T> values, const bool transpose = false);

		/* --- Setters and getters --- */
		void setDimension(const uint64_t dimension);
		uint64_t getDimension() const;
		void setTranspose(const bool transpose);
		bool getTranspose() const;
		void setValues(const std::vector<T> vec);
		std::vector<T> getValues() const;
		
		/* --- Element access --- */
		T& at(const size_t pos);
		
		/* --- Modifiers --- */
		void push_back(T value);
		
		/* --- Arithmetic --- */
		math::vector<T> operator+(const math::vector<T>& vec);
		uint64_t operator*(const math::vector<T>& vec);
		
		/* --- Utility --- */
		// print function should be replaced by overloading the <<-Operator
		void print();
		//friend std::ostream& operator<< (std::ostream& os, const vector<T>& vec);
		
		//template<class U> auto operator+(const math::vector<U>& vec);

};
/* IDK why is not working
template<class U>
std::ostream& operator<< (std::ostream& os, const math::vector<U>& vec);
*/
}
