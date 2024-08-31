// TrialExercise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int CreateFile(unsigned char  byteArray[]);
bool FindTargetInFile(ifstream& file, unsigned char targetByteArray[], int targetByteArraySize);

int main() {
    unsigned char byteArray[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    unsigned char targetByteArray[] = { 0x03, 0x04 };
	sizeof(targetByteArray);
    int retVal = CreateFile(byteArray);

	ifstream file("output.bin", ios::binary);

	if (!file || !file.is_open()) {
		cerr << "Error opening file for reading" << endl;
		return 1;
	}

	bool isFound = FindTargetInFile(file, targetByteArray, sizeof(targetByteArray));

    return retVal;
}

int CreateFile(unsigned char byteArray[])
{
    ofstream outFile("output.bin", ios::binary);

    if (!outFile) {
        cerr << "Error opening file for writing" << endl;
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(byteArray), sizeof(byteArray));
    outFile.close();

    return 0;
}

bool FindTargetInFile(ifstream& file, unsigned char targetByteArray[], int targetByteArraySize)
{
	file.seekg(0, ios::beg);
	unsigned char currentByte;
	int currentTargetCheckIndex = 0;
	streampos foundIndex = -1;

	while (file.read(reinterpret_cast<char*>(&currentByte), 1)) {
		if (currentByte == targetByteArray[currentTargetCheckIndex]) {
			if (currentTargetCheckIndex == 0) foundIndex = file.tellg();
			currentTargetCheckIndex++;
		}
		else if (currentTargetCheckIndex > 0)
		{
			currentTargetCheckIndex = 0;
			file.seekg(foundIndex);
		}

		if (currentTargetCheckIndex == targetByteArraySize / sizeof(targetByteArray[0])) {
			cout << "Target found at index: " << foundIndex << endl;
			return true;
		}
	}

	return false;
}