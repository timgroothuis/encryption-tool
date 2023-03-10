#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <thread>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <sys/stat.h>
namespace fs = std::filesystem;

bool doesPathExist(const std::string &s) {
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

std::string CharToString(unsigned char character){
	// if character is 0, return a 0 string, if character is 1, return a 1 string
	if (character == 0) {
		return "0";
	}
	else {
		return "1";
	}
}

std::string BinaryToHex(std::vector<unsigned char> binary) {
	// convert binary vector array to hex string
	std::string hexString;
	for (int i = 0; i < binary.size() / 4; i++) {
		std::string currentHexChar;
		currentHexChar = CharToString(binary[i * 4]) + CharToString(binary[i * 4 + 1]) + CharToString(binary[i * 4 + 2]) + CharToString(binary[i * 4 + 3]);
		
		if (currentHexChar == "0000") {
			hexString += "0";
		}
		else if (currentHexChar == "0001") {
			hexString += "1";
		}
		else if (currentHexChar == "0010") {
			hexString += "2";
		}
		else if (currentHexChar == "0011") {
			hexString += "3";
		}
		else if (currentHexChar == "0100") {
			hexString += "4";
		}
		else if (currentHexChar == "0101") {
			hexString += "5";
		}
		else if (currentHexChar == "0110") {
			hexString += "6";
		}
		else if (currentHexChar == "0111") {
			hexString += "7";
		}
		else if (currentHexChar == "1000") {
			hexString += "8";
		}
		else if (currentHexChar == "1001") {
			hexString += "9";
		}
		else if (currentHexChar == "1010") {
			hexString += "A";
		}
		else if (currentHexChar == "1011") {
			hexString += "B";
		}
		else if (currentHexChar == "1100") {
			hexString += "C";
		}
		else if (currentHexChar == "1101") {
			hexString += "D";
		}
		else if (currentHexChar == "1110") {
			hexString += "E";
		}
		else if (currentHexChar == "1111") {
			hexString += "F";
		}
	}
	
	return hexString;
}

std::vector<unsigned char> HexToBinary(std::string hexString) {
	// convert hex string to binary vector array
	std::vector<unsigned char> binary;
	for (char& c : hexString) {
		if (c == '0') {
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(0);
		}
		else if (c == '1') {
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(1);
		}
		else if (c == '2') {
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(0);
		}
		else if (c == '3') {
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(1);
		}
		else if (c == '4') {
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(0);
		}
		else if (c == '5') {
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(1);
		}
		else if (c == '6') {
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(0);
		}
		else if (c == '7') {
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(1);
		}
		else if (c == '8') {
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(0);
		}
		else if (c == '9') {
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(0);
			binary.push_back(1);
		}
		else if (c == 'A') {
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(0);
		}
		else if (c == 'B') {
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(1);
			binary.push_back(1);
		}
		else if (c == 'C') {
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(0);
		}
		else if (c == 'D') {
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(0);
			binary.push_back(1);
		}
		else if (c == 'E') {
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(0);
		}
		else if (c == 'F') {
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(1);
			binary.push_back(1);
		}
		else {
			std::cout << "Fatal error: Invalid hex character encountered, closing program" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			exit(1);
		}
	}
	return binary;
}

std::vector<unsigned char> DecimalToBinary(unsigned char decimal) {
	// convert unsigned char decimal to binary
	std::vector<unsigned char> binaryByte;
	float currentDecimal = decimal;
	for (int i = 0; i < 8; i++) {
		currentDecimal /= 2;
		if (ceil(currentDecimal) > currentDecimal) {
			binaryByte.push_back(1);
			currentDecimal = floor(currentDecimal);
		}
		else {
			binaryByte.push_back(0);
		}
	}
	// might remove reverse function later
	std::reverse(binaryByte.begin(), binaryByte.end());
	return binaryByte;
}

std::string fixed_getline()
{
	std::string result;

	while (!std::getline(std::cin, result) || result.empty());

	return result;
}


unsigned char BinaryToDecimal(std::vector<unsigned char> binary) {
	// might remove reverse function later
	std::reverse(binary.begin(), binary.end());
	int currentValue = 1;
	unsigned char decimal = 0;
	for (int i = 0; i < 8; i++) {
		if (binary[i] == 1) {
			decimal += currentValue;
		}
		currentValue *= 2;
	}
	return decimal;
}

std::vector<unsigned char> Encrypt(std::vector<unsigned char> inputData, std::vector<unsigned char> bitmask) {
	int byteIndex = 0;
	int bitmaskIndex = 0;

	// for each bit check if bitmask value at same index is 1, if the bitmask value is 1 then flip the bit
	for (unsigned char byte : inputData) {
		std::vector<unsigned char> binaryByte = DecimalToBinary(byte);
		for (int i = 0; i < 8; i++) {
			if (bitmaskIndex == bitmask.size()) {
				bitmaskIndex = 0;
			}
			if (bitmask[bitmaskIndex] == 1) {
				if (binaryByte[i] == 1) {
					binaryByte[i] = 0;
				}
				else {
					binaryByte[i] = 1;
				}
			}
			bitmaskIndex++;
		}
		inputData[byteIndex] = BinaryToDecimal(binaryByte);
		byteIndex++;
	}
	return inputData;
}

std::vector<unsigned char> Decrypt(std::vector<unsigned char> inputData, std::vector<unsigned char> bitmask) {
	int byteIndex = 0;
	int bitmaskIndex = 0;

	// for each bit check if bitmask value at same index is 1, if the bitmask value is 1 then flip the bit
	for (unsigned char byte : inputData) {
		std::vector<unsigned char> binaryByte = DecimalToBinary(byte);
		for (int i = 0; i < 8; i++) {
			if (bitmaskIndex == bitmask.size()) {
				bitmaskIndex = 0;
			}
			if (bitmask[bitmaskIndex] == 1) {
				if (binaryByte[i] == 1) {
					binaryByte[i] = 0;
				}
				else {
					binaryByte[i] = 1;
				}
			}
			bitmaskIndex++;
		}
		inputData[byteIndex] = BinaryToDecimal(binaryByte);
		byteIndex++;
	}
	return inputData;
}

std::vector<unsigned char> bitmaskGenerator(int size) {
	// Valid bitmask sizes: 8-bit, 16-bit, 32-bit, 64-bit, 128-bit, 256-bit
	std::vector<unsigned char> bitmask;
	std::cout << "Generating encryption key..." << std::endl;
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		bitmask.push_back(rand()%2);
	}
	std::cout << "Encryption key generated. Copy the key and save it somewhere to decrypt your files: ";
	// Get string from unsigned char vector
	std::string bitmaskString;
	for (unsigned char c : bitmask) {
		if (c == 1) {
			bitmaskString += "1";
		}
		else if (c == 0) {
			bitmaskString += "0";
		}
	}
	std::string hexKey = BinaryToHex(bitmask);
	std::cout << hexKey << std::endl;
	return bitmask;
}

void EncryptionDecryptionProcess(bool decrypt, int bitmaskSize, std::string encryptionFolder) {
	std::vector<unsigned char> bitmask;
	if (decrypt) {
		std::string keyInput;
		std::cout << "Enter encryption key: " << std::endl;
		std::cin >> keyInput;

		bitmask = HexToBinary(keyInput);
	}
	else {
		bitmask = bitmaskGenerator(bitmaskSize);
	}

	

	// get folder(s) to encrypt
	for (const auto& entry : fs::recursive_directory_iterator(encryptionFolder))
		// check if directory entry is a subdirectory
		if (entry.is_directory() == false) {
			std::ifstream currentFile;
			// get file data
			currentFile.open(entry.path(), std::ios::app | std::ios::binary);
			if (!currentFile) {
				std::cerr << "Could not open file: " + entry.path().string() << std::endl;
			}
			else {
				std::vector<unsigned char> fileDataBuffer;
				currentFile.seekg(0, std::ios::end);
				fileDataBuffer.resize(currentFile.tellg());
				currentFile.seekg(0, std::ios::beg);

				currentFile.read(reinterpret_cast<char*>(fileDataBuffer.data()), fileDataBuffer.size());
				std::cout << entry.path().string() << std::endl;
				currentFile.close();

				// ------------------------------------------------------------------
				// ENCRYPTION/DECRYPTION PROCESS STARTS HERE
				// ------------------------------------------------------------------
				
				if (decrypt == false) {
					// encrypt
					fileDataBuffer = Encrypt(fileDataBuffer, bitmask);
				}
				else {
					// decrypt
					fileDataBuffer = Decrypt(fileDataBuffer, bitmask);
				}

				// ------------------------------------------------------------------
				// ENCRYPTION/DECRYPTION PROCESS ENDS HERE
				// ------------------------------------------------------------------
				
				// remove old file
				std::remove(entry.path().string().c_str());

				// write file data to new file
				std::ofstream encryptedFile;
				encryptedFile.open(entry.path(), std::ios::app | std::ios::binary);
				encryptedFile.write(reinterpret_cast<char*>(fileDataBuffer.data()), fileDataBuffer.size());
				encryptedFile.close();
			}
		}
	std::string waitForUserInput;
	std::cout << "Done" << std::endl;
	std::cin >> waitForUserInput;
};

int main() {
	std::string choice;
	std::string waitForUserInput;

	std::cout << "The program can cause harm to your files, do you want to continue? (y/n)" << std::endl;
	std::cin >> choice;

	if (choice == "yes" || choice == "y") {
		std::string encryptionFolder, choice2;

		std::cout << "Enter the path of the folder you want to encrypt or decrypt: ";
		encryptionFolder = fixed_getline();
		if (doesPathExist(encryptionFolder) == false) {
			std::cout << "Path does not exist, closing program" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			exit(1);
		}

		std::cout << "Encrypt or decrypt?" << std::endl;
		choice2 = fixed_getline();

		bool decrypt;
		int bitmaskSize = 8;
		if (choice2 == "encrypt") {
			decrypt = false;
			std::cout << "Enter key size in bits (8, 16, 32, 64, 128, 256): " << std::endl;
			std::cin >> bitmaskSize;
		}
		else if (choice2 == "decrypt") {
			decrypt = true;
		}
		EncryptionDecryptionProcess(decrypt, bitmaskSize, encryptionFolder);
	}
	else {
		std::cout << "Closing program";
		exit(1);
	}
}