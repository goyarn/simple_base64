#ifndef SIMPLE_BASE_HPP
#define SIMPLE_BASE_HPP

#include <string>
#include <vector>

class Base64{
	public:
		static std::string encode(std::string str);
		static std::string decode(std::string code);

		static std::string get_encoding_table(void);
		static std::vector<int> get_decoding_table(void);
	private:
};

#endif
