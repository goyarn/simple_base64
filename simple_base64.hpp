#ifndef SIMPLE_BASE_HPP
#define SIMPLE_BASE_HPP

#include <string>
#include <vector>

class Base64{
	public:
		static std::string encode(std::string str);
		static std::string decode(std::string code);

	private:
		void initialize(void);
		static std::string encoding_table;
		static std::vector<int> decoding_table;
};

#endif
