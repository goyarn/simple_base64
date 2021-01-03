#include "simple_base64.hpp"
#include <string>
#include <vector>

std::string Base64::get_encoding_table(void){
	static std::string encoding_table =
		std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
		+ std::string("abcdefghijklmnopqrstuvwxyz")
		+ std::string("0123456789+/");
	return encoding_table;
}

std::vector<int> Base64::get_decoding_table(void){
	static std::vector<int> decoding_table(256, -1);
	auto encoding_table = get_encoding_table();
	for(int i = 0; i < 64; ++i){
		int index = (int)encoding_table[i];
		decoding_table[index] = i;
	}
	return decoding_table;
}

std::string Base64::encode(std::string str){
	if (str.empty()) return str;
	std::string encoded;
	auto encoding_table = Base64::get_encoding_table();
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
			output[2] = ((input[1] & 0xF) << 2) | ((input[2] & 0xC0) >> 6);
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
	int d, prev_d;
	int phase = 0;
	for(char &ch : code){
		d = Base64::get_decoding_table()[(int)ch];
		if (d == -1) continue;
		// make 6bits to 8bits.
		char c;
		if (phase == 1) c = (prev_d << 2) | ((d & 0x30) >> 4);
		else if (phase == 2) c = ((prev_d & 0xf) << 4) | ((d & 0x3c) >> 2);
		else if (phase == 3) c = ((prev_d & 0x03) << 6) | d;
		// append only when new characters decoded.
		if (phase > 0)
			decoded.push_back(c);
		phase = (phase + 1) % 4;
		prev_d = d;
	}
	return decoded;
}
