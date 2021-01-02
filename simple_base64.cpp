#include "simple_base64.hpp"

void Base64::initialize(void){
	encoding_table =
		std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
		+ std::string("abcdefghijklmnopqrstuvwxyz")
		+ std::string("0123456789+/");
	decoding_table = std::vector<int>(256, -1);
	for(int i = 0; i < 64; ++i){
		int index = (int)encoding_table[i];
		decoding_table[index] = i;
	}
}

std::string Base64::encode(std::string str){
	if (str.empty()) return str;
	std::string encoded;
	int size = str.size();

	unsigned char input[3];
	unsigned char output[4];
	for(int pos = 0; pos < size; pos++){
		int mod = pos % 3;
		input[mod] = str[pos];
		// encode when input size(3) is full or last turn
		if (mod == 2 || pos == size - 1){
			output[0] = (input[0] & 0xFC) >> 2;
			output[1] = ((input[0] & 0x3) << 4) | ((input[1] & 0xF0) >> 4);
			output[2] = ((input[1] & 0xF) << 4) | ((input[2] & 0xC0) >> 4);
			output[3] = input[2] & 0x3F;

			encoded.push_back(encoding_table[output[0]]);
			encoded.push_back(encoding_table[output[1]]);
			if (mod == 0)
				encoded.push_back('=');
			else
				encoded.push_back(encoding_table[output[2]]);
			if (mod < 2)
				encoded.push_back('=');
			else
				encoded.push_back(encoding_table[output[3]]);
			input[0] = 0;
			input[1] = 0;
			input[2] = 0;
		}
	}
	return encoded;
}

std::string Base64::decode(std::string code){
	std::string decoded;
	return decoded;
}
