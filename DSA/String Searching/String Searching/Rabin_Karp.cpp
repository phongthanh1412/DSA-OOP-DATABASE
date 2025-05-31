#include<iostream>
#include<string>
#include<climits>
using namespace std;

void searchSubString(char pattern[], char text[], int prime) {
	int h = 1, i = 0, j = 0;
	int txtHash = 0, patHash = 0;
	int patLen = strlen(pattern);
	int txtLen = strlen(text);
	for (i = 0; i < patLen - 1; i++)
		h = (h * 256) % INT_MAX;

	//Tính giá trị hash của paterrn và phần đầu của text 
	for (i = 0; i < patLen; i++) {
		patHash = (256 * patHash + pattern[i]) % INT_MAX;
		txtHash = (256 * txtHash + text[i]) % INT_MAX;
	}
	// Trượt pattern trên text 
	for (i = 0; i <= txtLen - patLen; i++) {
		if (patHash == txtHash) {
			for (j = 0; j < patLen; j++) {
				if (text[i + j] != pattern[j])
					break;
			}
			if (j == patLen)
				cout << "Pattern was found at index " << i << endl;
		}
		if (i < txtLen - patLen) {
			txtHash = (256 * (txtHash - h * text[i]) + text[i + patLen]) % INT_MAX;
			if (txtHash < 0)
				txtHash = txtHash + INT_MAX;
		}
	}
}
int main() {
	char text[] = "AABAACAADAABAABA";
	char pattern[] = "AABA";
	searchSubString(pattern, text, INT_MAX);
	return 0;
}