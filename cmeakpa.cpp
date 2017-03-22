#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <tgmath.h>
#define BLOCK 8
#define COUNT 256

using namespace std;

int tmapping[COUNT][COUNT];
int tmappingC[COUNT][COUNT];
int plainSize = 0;
unsigned char p[100][3];
unsigned char c[100][3];
unsigned char k67[10][2];
int k67count = 0;
unsigned char uniqueT[4][2];
int uniqueTcount = 0;
unsigned char cave[164]  = {0x00, 0x01, 0x04, 0x05, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x17, 0x18, 0x1b, 0x1c, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x25, 0x26, 0x29, 0x2b, 0x2d, 0x2f, 0x30, 0x33, 0x34, 0x36, 0x37, 0x38, 0x3a, 0x3c, 0x3e, 0x3f, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x49, 0x4a, 0x4d, 0x4e, 0x51, 0x54, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x62, 0x64, 0x65, 0x66, 0x67, 0x68, 0x6c, 0x6d, 0x6f, 0x70, 0x71, 0x73, 0x74, 0x76, 0x77, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x80, 0x81, 0x83, 0x84, 0x86, 0x88, 0x89, 0x8b, 0x8d, 0x8e, 0x91, 0x93, 0x94, 0x95, 0x96, 0x97, 0x9b, 0x9d, 0x9e, 0x9f, 0xa2, 0xa4, 0xa5, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xae, 0xb0, 0xb1, 0xb3, 0xb5, 0xb6, 0xb8, 0xba, 0xbb, 0xbc, 0xbd, 0xbf, 0xc3, 0xc4, 0xc5, 0xc7, 0xc9, 0xca, 0xcb, 0xcf, 0xd0, 0xd1, 0xd2, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xde, 0xe0, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf5, 0xf6, 0xf8, 0xfa, 0xfe, 0xff};
unsigned char cavetable[256] = {
		0xd9,0x23,0x5f,0xe6,0xca,0x68,0x97,0xb0,0x7b,0xf2,0x0c,0x34,0x11,0xa5,0x8d,0x4e,
		0x0a,0x46,0x77,0x8d,0x10,0x9f,0x5e,0x62,0xf1,0x34,0xec,0xa5,0xc9,0xb3,0xd8,0x2b,
		0x59,0x47,0xe3,0xd2,0xff,0xae,0x64,0xca,0x15,0x8b,0x7d,0x38,0x21,0xbc,0x96,0x00,
		0x49,0x56,0x23,0x15,0x97,0xe4,0xcb,0x6f,0xf2,0x70,0x3c,0x88,0xba,0xd1,0x0d,0xae,
		0xe2,0x38,0xba,0x44,0x9f,0x83,0x5d,0x1c,0xde,0xab,0xc7,0x65,0xf1,0x76,0x09,0x20,
		0x86,0xbd,0x0a,0xf1,0x3c,0xa7,0x29,0x93,0xcb,0x45,0x5f,0xe8,0x10,0x74,0x62,0xde,
		0xb8,0x77,0x80,0xd1,0x12,0x26,0xac,0x6d,0xe9,0xcf,0xf3,0x54,0x3a,0x0b,0x95,0x4e,
		0xb1,0x30,0xa4,0x96,0xf8,0x57,0x49,0x8e,0x05,0x1f,0x62,0x7c,0xc3,0x2b,0xda,0xed,
		0xbb,0x86,0x0d,0x7a,0x97,0x13,0x6c,0x4e,0x51,0x30,0xe5,0xf2,0x2f,0xd8,0xc4,0xa9,
		0x91,0x76,0xf0,0x17,0x43,0x38,0x29,0x84,0xa2,0xdb,0xef,0x65,0x5e,0xca,0x0d,0xbc,
		0xe7,0xfa,0xd8,0x81,0x6f,0x00,0x14,0x42,0x25,0x7c,0x5d,0xc9,0x9e,0xb6,0x33,0xab,
		0x5a,0x6f,0x9b,0xd9,0xfe,0x71,0x44,0xc5,0x37,0xa2,0x88,0x2d,0x00,0xb6,0x13,0xec,
		0x4e,0x96,0xa8,0x5a,0xb5,0xd7,0xc3,0x8d,0x3f,0xf2,0xec,0x04,0x60,0x71,0x1b,0x29,
		0x04,0x79,0xe3,0xc7,0x1b,0x66,0x81,0x4a,0x25,0x9d,0xdc,0x5f,0x3e,0xb0,0xf8,0xa2,
		0x91,0x34,0xf6,0x5c,0x67,0x89,0x73,0x05,0x22,0xaa,0xcb,0xee,0xbf,0x18,0xd0,0x4d,
		0xf5,0x36,0xae,0x01,0x2f,0x94,0xc3,0x49,0x8b,0xbd,0x58,0x12,0xe0,0x77,0x6c,0xda};

unordered_map< unsigned char, vector<unsigned char> >  inversecave;
unordered_map< string, vector<vector<unsigned char> > > tableM;

void createTmapping();
int readFiles(int argc, char const *argv[]);
void findT0();
int checkEquations(unsigned char plain[3], unsigned char cipher[3], unsigned char t0);
void getPossibleK6K7();
void printTBox();
void findUniqueT();
void inverseCavetable();
void createTableM();
void searchTableM();
void printCaveInverse();
int tryKey(vector<unsigned char> key);
unsigned char T(unsigned char z, vector <unsigned char> key);

int main(int argc, char const *argv[])
{
	printf("Trying to break the CMEA\n");

	if(argc != 3)
    {
oops:   fprintf(stderr, "\nUsage: %s <plaintext file> <ciphertext file>\n\n", argv[0]);
        exit(0);
    }

	int error = 0;
	error = readFiles(argc, argv);
	if(error != 0)
	{
		exit(0);
	}
	createTmapping();
	findT0();
	//printTBox();
	getPossibleK6K7();
	findUniqueT();
	inverseCavetable();
	//printCaveInverse();
	createTableM();
	searchTableM();
	return error;
}

void createTmapping()
{
	printf("-> Initializing TBox mapping table\n");
	// intialize all the values in mapping matrxix as 0
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			tmapping[i][j] = 0 ;
		}
	}

	//for each T(i) mark set the possible values. 92 zeroes
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < 164; ++j)
		{
			unsigned char y = cave[j] + i;
			tmapping[i][y] = 1 ;
		}
	}
	printf("<- TBox mapping table initialized\n");
}

int readFiles(int argc, char const *argv[])
{
	printf("-> Reading files\n");
	FILE *pf, *cf;

	//open plaintext file
	//printf("%s\n", argv[1]);
	pf = fopen(argv[1],"rb");
	if (!pf)
	{
		fprintf(stderr, "\nUnable to open plaintext file\n\n");
		return 1;
	}
	fseek(pf, 0L, SEEK_END);
	plainSize = ftell(pf) / 3;
	printf("   Number of known plaintext blocks of 3 byte Size: %d\n", plainSize);
	fseek(pf, 0L, SEEK_SET);

	//open ciphertext file
	//printf("%s\n", argv[2]);
	cf = fopen(argv[2],"rb");
	if (!cf)
	{
		fprintf(stderr, "\nUnable to open ciphertext file\n\n");
		return 1;
	}

	int flag = 1;
	unsigned char buf[3];
	size_t block;
	int i = 0;
	while(i<plainSize)
	{
		block = fread(buf, 1, 3, pf);
		if(block < 3){
			flag = 0;
		}
		p[i][0] = buf[0];
		p[i][1] = buf[1];
		p[i][2] = buf[2];
		fread(buf, 1, 3, cf);
		c[i][0] = buf[0];
		c[i][1] = buf[1];
		c[i][2] = buf[2];
		i++;
	}
	printf("<- Completed reading files\n");
	return 0;
}

void findT0()
{
	printf("-> Starting Phase 1 : Finding putative T0\n");

	for (int i = 0; i < 164; ++i)
	{
		unsigned char t0 = cave[i];
		//printf("Guessing t0 = %x\n", t0);

		for(int j = 0; j < COUNT; ++j)
		{
			for (int k = 0; k < COUNT; ++k)
			{
				tmappingC[j][k] = tmapping[j][k];
			}
		}
		for (int j = 0; j < COUNT; ++j)
		{
			if(j != cave[i])
			{
				tmappingC[0][j] = 0;
			}
		}

		int correctResult = 1;
		int flag = 1;
		while(flag)
		{
			flag = 0;
			for(int j = 0; j < plainSize; j++)
			{
				int result = checkEquations(p[j], c[j], t0);
				flag = flag | result;
			}

			for(int j = 0; j < plainSize; j++)
			{
				int result = checkEquations(c[j], p[j], t0);
				flag = flag | result;
			}

			for(int j = 0; j < COUNT; ++j)
			{
				int flagCheckRow = 0;
				for (int k = 0; k < COUNT; ++k)
				{
					if(tmappingC[j][k] == 1)
					{
						flagCheckRow = 1;
					}
				}
				if(flagCheckRow == 0)
				{
					correctResult = 0;
					break;
				}
			}
		}// while
		if(correctResult == 1){
			printf("   T0 = %02x\n", t0);
			break;
		}
	}// for t0
	printf("<- Completed Phase 1\n");
}

int checkEquations(unsigned char plain[3], unsigned char cipher[3], unsigned char t0)
{
	unsigned char p0, p1, p2, c0, c1, c2;
	p0 = plain[0];
	p1 = plain[1];
	p2 = plain[2];
	c0 = cipher[0];
	c1 = cipher[1];
	c2 = cipher[2];
	unsigned char pt0 = p0 + t0;
	unsigned char imb = pt0 ^ 1;
	int result = 0;
	for (int j = 0; j < COUNT; ++j)
	{
		if(tmappingC[imb][j] == 1)
		{
			unsigned char imbr = j;

			// check eq1
			unsigned char ct0 = c0 + t0;
			unsigned char ptc0 = pt0 ^ ct0;
			unsigned char eq1v1 = ptc0 - p2;
			unsigned char eq1v2 = (ptc0 ^ 1) - p2;
			unsigned char eq1k = (pt0 + p1 + imbr) ^ 2;

			// check eq2
			unsigned char eq2v = p1 + imbr - c1;
			unsigned char eq2k = ct0 ^ 1;

			// check eq3
			unsigned char eq3v1 = ptc0 - c2;
			unsigned char eq3v2 = (ptc0 ^ 1) - c2;
			unsigned char eq3k = (ct0 + p1 + imbr) ^ 2;

			// evaluation
			if((tmappingC[eq1k][eq1v1] == 0 && tmappingC[eq1k][eq1v2] == 0) ||
				tmappingC[eq2k][eq2v] == 0 ||
				(tmappingC[eq3k][eq3v1] == 0 && tmappingC[eq3k][eq3v2] == 0))
			{
				tmappingC[imb][imbr] = 0;
				result = 1;
			}
		}
	}
	return result;
}

void printTBox(){
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			if(tmappingC[i][j] == 1)
			{
				printf("   T[%d] = %02x\n", i, j);
			}
		}
	}
}

void getPossibleK6K7()
{
	printf("-> Starting Phase 2a: Backtracking for finding K6 K7\n");
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			int discard = 0;
			for (int x = 0; x < COUNT; ++x)
			{
				int found = 0;
				for (int v = 0; v < 164; ++v)
				{
					unsigned char y = cavetable[(unsigned char)(((cave[v] + x) ^ i) + j)] + x;

					if(tmappingC[x][y] == 1)
					{
						found = 1;
						break;
					}
				}
				if(!found)
				{
					discard = 1;
					break;
				}
			}
			if(!discard)
			{
				printf("   K6, K7 = {%02x %02x}\n", i, j);
				k67[k67count][0] = i;
				k67[k67count][1] = j;
				k67count++;
			}
			if(k67count == 10)
			{
				break;
			}
		}
		if(k67count == 10)
			{
				break;
			}
	}
	printf("<- Completed Phase 2a\n");
}

void findUniqueT()
{
	printf("-> Starting Phase 2b: Meet in the middle\n");
	printf("   -> Finding 4 unique TBox entries\n");
	for (int i = 0; i < COUNT; ++i)
	{
		int possibleVal[256];
		int possibleValCount = 0;
		for (int j = 0; j < COUNT; ++j)
		{
			if(tmappingC[i][j] == 1)
			{
				possibleVal[possibleValCount] = j;
				possibleValCount++;
			}
		}
		if(possibleValCount == 1)
		{
			printf("      T[%d] = %02x\n", i, possibleVal[0]);
			uniqueT[uniqueTcount][0] = i;
			uniqueT[uniqueTcount][1] = possibleVal[0];
			uniqueTcount++;
		}
		if(uniqueTcount == 4)
		{
			break;
		}
	}
	printf("   <- Completed finding unique TBox entries\n");
}

void inverseCavetable()
{
	//printf("-> Creating Inverse Cave table\n");
	for (int i = 0; i < COUNT; ++i)
	{
		unordered_map< unsigned char, vector<unsigned char> >::iterator it = inversecave.find(cavetable[i]);
		if(it != inversecave.end())
		{
			vector<unsigned char> temp = it->second;
			temp.push_back(i);
			inversecave[cavetable[i]] = temp;
		}
		else
		{
			vector<unsigned char> temp;
			temp.push_back(i);
			inversecave[cavetable[i]] = temp;
		}
	}
	//cout<<"   Size of inversecave: "<<inversecave.size()<<endl;
	//printf("<- Creating Inverse Cave table completed\n");
}

void createTableM()
{
	printf("   -> Starting construction of search table M\n");
	//printf("   Size of table M = %lu\n", tableM.size());
	for (int i = 0; i < COUNT; ++i)
	{
		unsigned char k0 = i;
		for (int j = 0; j < COUNT; ++j)
		{
			unsigned char k1 = j;
			for (int k = 0; k < COUNT; ++k)
			{
				unsigned char k2 = k;
				vector< unsigned char > ads; 
				for (int l = 0; l < 4; ++l)
				{
					unsigned char a = uniqueT[l][0];
					unsigned char ad = (cavetable[(unsigned char)((a^k0) + k1)] + a) ^ k2;
					ads.push_back(ad);
				}
				// addd = a' - d'
				unsigned char addd = ads[0] - ads[3];
				unsigned char bddd = ads[1] - ads[3];
				unsigned char cddd = ads[2] - ads[3];

				// addd,bddd,cddd
				string s = to_string(addd)+to_string(bddd)+to_string(cddd);
				vector< unsigned char> val;

				// k0, k1, k2, a'
				val.push_back(k0);
				val.push_back(k1);
				val.push_back(k2);
				val.push_back(ads[0]);
				if(tableM.find(s)!=tableM.end())
				{
					tableM[s].push_back(val);
				}
				else
				{
					vector< vector<unsigned char> > temp;
					temp.push_back(val);
					tableM[s] = temp;
				}
			}
		}
	}
	printf("      Size of search table M = %lu\n", tableM.size());
	printf("   -> Completed contruction of search table\n");
}

void searchTableM()
{
	printf("   -> Starting comparison of guessed keys to search table M\n");
	int count=0;
	int firstFind = 0;
	int firstFindFlag = 1;
	for (int i = 0; i < COUNT; ++i)
	{
		unsigned char k4 = i;
		for (int j = 0; j < COUNT; ++j)
		{
			unsigned char k5 = j;
			for (int k = 0; k < k67count; ++k)
			{
				unsigned char k6 = k67[k][0];
				unsigned char k7 = k67[k][1];
				//printf("K6 K7 = {%02x %02x}\n", k6, k7);
				vector< vector< unsigned char> > adds;
				int discard=0;
				for(int l = 0; l < 4; ++l)
				{
					unsigned char a = uniqueT[l][0];
					unsigned char at = uniqueT[l][1];
					vector <unsigned char> tci;

					//key = T(a) - a
					unsigned char key = at-a;
					//printf("Finding key: %02x\n", key);
					if (inversecave.find(key)!=inversecave.end())
					{
						// tci = (S(a) ^ k6) + k7
						tci = inversecave[key];
					}
					
					vector<unsigned char> sci;
					vector<unsigned char> rci;
					vector<unsigned char> add;
					for(int m = 0; m < tci.size(); m++)
					{
						//printf("   Found value TCI: %d\n", tci[m]);
						//key = S(a) - a;
						key = ((tci[m]-k7)^k6)-a;
						//printf("   Finding key: %02x\n", key);
						if (inversecave.find(key)!=inversecave.end())
						{
							// temp = (R(a) ^ K4) + K5
							vector <unsigned char> temp = inversecave[key];
							sci.insert(sci.end(), temp.begin(), temp.end());
						}
					}
					for (int n = 0; n < sci.size(); ++n)
					{
						//printf("      Found SCI: %d\n", sci[n]);
						// R(a) - a
						key = ((sci[n]-k5)^k4)-a;
						//printf("      Finding key: %02x\n", key);
						if (inversecave.find(key)!=inversecave.end())
						{
							// temp = a''
							vector <unsigned char> temp = inversecave[(unsigned char)(((sci[n]-k5)^k4)-a)];
							add.insert(add.end(), temp.begin(), temp.end());
							//rci.insert(rci.end(), temp.begin(), temp.end());
						}
					}
					// for (int m = 0; m < rci.size(); ++m)
					// {
					// 	//printf("         Found RCI: %d\n", rci[m]);
					// 	if (inversecave.find(rci[m])!=inversecave.end())
					// 	{
					// 		vector <unsigned char> temp =  inversecave[rci[m]];
					// 		add.insert(add.end(), temp.begin(), temp.end());
					// 	}
					// }
					if(add.size()==0)
					{
						discard = 1;
						break;
					}
					adds.push_back(add);
				}
				if(discard == 1)
				{
					continue;
				}
				//printf("Did not continue...\n");
				
				for(int addc = 0; addc<adds[0].size(); ++addc)
				{
					for (int bddc = 0; bddc < adds[1].size(); ++bddc)
					{
						for (int cddc = 0; cddc < adds[2].size(); ++cddc)
						{
							for (int dddc = 0; dddc < adds[3].size(); ++dddc)
							{
								unsigned char ad5 = adds[0][addc] - adds[3][dddc];
								unsigned char bd5 = adds[1][bddc] - adds[3][dddc];
								unsigned char cd5 = adds[2][cddc] - adds[3][dddc];
								string key = to_string(ad5)+to_string(bd5)+to_string(cd5);
								//cout<<"Searching: "<<key<<endl;
								if(tableM.find(key) != tableM.end())
								{
									vector< vector< unsigned char> > temp = tableM[key];
									for(int l=0; l<temp.size(); ++l)
									{
										count++;
										vector <unsigned char> val = temp[l];
										unsigned char k0 = val[0];
										unsigned char k1 = val[1];
										unsigned char k2 = val[2];
										unsigned char k3 = adds[0][addc] - val[3];
										vector< unsigned char> key;
										key.push_back(k0);
										key.push_back(k1);
										key.push_back(k2);
										key.push_back(k3);
										key.push_back(k4);
										key.push_back(k5);
										key.push_back(k6);
										key.push_back(k7);
										if(tryKey(key))
										{
											if(firstFindFlag)
											{
												firstFindFlag = 0;
												firstFind = count;
											}
											printf("      key = [%02x %02x %02x %02x %02x %02x %02x %02x] at trial %d\n", k0, k1, k2, k3, k4, k5, k6, k7, count);
										}
									}
								}
							}
						}
					}
				} 
			}
		}
	}
	printf("      Tried number of keys: %d\n", count);
	printf("   <- Completed comparison\n");
	printf("<- Completed Phase 2b\n");
	if(!firstFindFlag)
	{
		cout<<"Computed first correct key in 2^"<<log2(firstFind)<<" attempts"<<endl;
		cout<<"Effort reduction by factor of 2^"<<64-(log2(firstFind))<<endl;
	}
}

void printCaveInverse()
{
	for (int i = 0; i < inversecave.size(); ++i)
	{
		vector< unsigned char> temp = inversecave[i];
		for (std::vector<unsigned char>::iterator j = temp.begin(); j != temp.end(); ++j)
		{
			printf("%02x %d\n", i, *j);
		}
	}
}

int tryKey(vector<unsigned char> key)
{
	int i,
		j,
		half;

	int n = 3;
	
	unsigned char k,
				  z;

	unsigned char p1[3],
				  c1[3];
	
	for(int j=0; j<100; j++)
	{
		p1[0]=p[j][0];
		p1[1]=p[j][1];
		p1[2]=p[j][2];
		c1[0]=c[j][0];
		c1[1]=c[j][1];
		c1[2]=c[j][2];

		/// first manipulation (inverse of third)
		z = 0;
		for(i = 0; i < n; ++i)
		{
			k = T((unsigned char)(z ^ i), key);
			p1[i] += k;
			z += p1[i];
		}
		// second manipulation (self-inverse)
		half = n >> 1;// half = n / 2
		for(i = 0; i < half; ++i)
		{
			p1[i] ^= p1[n - 1 - i] | 0x01;
		}
		// third manipulation (inverse of first)
		z = 0;
		for(i = 0; i < n; ++i)
		{
			k = T((unsigned char)(z ^ i), key);
			z += p1[i];
			p1[i] -= k;// mod 256
		}

		/// first manipulation (inverse of third)
		z = 0;
		for(i = 0; i < n; ++i)
		{
			k = T((unsigned char)(z ^ i), key);
			c1[i] += k;
			z += c1[i];
		}
		// second manipulation (self-inverse)
		half = n >> 1;// half = n / 2
		for(i = 0; i < half; ++i)
		{
			c1[i] ^= c1[n - 1 - i] | 0x01;
		}
		// third manipulation (inverse of first)
		z = 0;
		for(i = 0; i < n; ++i)
		{
			k = T((unsigned char)(z ^ i), key);
			z += c1[i];
			c1[i] -= k;// mod 256
		}

		if(p1[0]!=c[j][0] || p1[1]!=c[j][1] || p1[2]!=c[j][2]
			|| c1[0]!=p[j][0] || c1[1]!=p[j][1] || c1[2]!=p[j][2])
		{
			return 0;
		}
	}
	return 1;
}

unsigned char T(unsigned char z, vector<unsigned char> key)
{
	int i,
		k;
	
	unsigned char y;

	k = 0;
	y = z;
	for (i = 0; i < 4; i++)
	{
		y = y ^ key[k];
		y = y + key[k + 1];
		y = z + cavetable[y];
		k += 2;
	}
	return(y);

}// end T()