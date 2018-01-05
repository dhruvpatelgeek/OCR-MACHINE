#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>
using namespace std;
struct pixel
{
	int mesh[30][30], label;
};
struct gradient_descent// using the pointer methord to dynamically allocate memory
{
	int nudge[13000];// the nudges to be made to each weight
};
class weights
{
public:
	long double w;
	int index, serial;//where is the weight pointing to
	weights()
	{
		index = serial = -1;
		w = ((rand()) % 10) - 5;// initializing a random weight coieffiecient which is both +ve and -ve
	}
};
class neuron_one
{
public:
	long double brightness;
	int position;

	neuron_one()
	{
		brightness = position = 0;
	}
	~neuron_one()
	{
		cout << "\n NEURON" << position << "\n brightness is \t" << brightness;
	}

};
class neuron_two : public neuron_one // using inheritance
{
public:
	neuron_two()
	{
		neuron_one::position = -1;
		neuron_one::brightness = -1;
	}
};
void test()
{
	int a, temp; // initialising the variables
	ifstream mnsit_reader;
	ifstream custom_file_dump;

	mnsit_reader.open("C:\\Users\\dhruv\\Downloads\\mnist_train.txt");
    custom_file_dump.open("C:\\Users\\dhruv\\Downloads\\solid_buffer.dat");

	if (mnsit_reader.is_open() && custom_file_dump.is_open())// checks if the file actually opens
		cout << "File successfully open" << endl;
	else
		cout << "Error opening file" << endl;

	cout << "\n enter the number of batches" << endl;//TYPICALLY 500-1500)
	cin >> a;
	pixel *p;
	p = new pixel[a];
	mnsit_reader.seekg(ios::beg);// puts the get point onto the beginning of the file
	custom_file_dump.seekg(ios::beg);
	
	for (int i = 0; i < a; i++)// takes the csv files and loads it into the structures 
	{
		cout << "\n SCANNING BLOCK = " << i << endl;// since this process is time consuming, i wrote this to detect system crash
		mnsit_reader >> temp;
		p[i].label = temp;
		for (int j = 0; j < 28; j++)
		{
			for (int k = 0; k < 28; k++)
			{
				mnsit_reader >> temp;
				p[i].mesh[j][k] = temp;
			}
		}

	}

	cout << "\n STRUCTURES READY IN THE BUFFER\n \n PROCEEDING TO TESTING" << endl;
	mnsit_reader.close();
	system("cls");
	cout << "\n bufferring layer one";
	neuron_one n[784];
	weights w[13002];/* 784x 16 + 16x16 + 160 (13000 approx) */
	long double temp99 = 0;
	for (int f = 12960; f >= 0; f--)// feeds the calibrated weights into the program
	{
		custom_file_dump >> temp99;
		w[f].w = temp99;
	}
	neuron_two n2[42]; // 16+16 +10
	int y = 0, y_mirror;// is the index for weights
						/*MAIN LOOP*/
	for (int i = 0; i < a; i++)// the main sturture loading loop
	{
		int l;
		long double w_sum = 0, temp;
		l = 0;

		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				temp = p[i].mesh[j][k];
				temp = (temp / 255);
				n[l].brightness = temp;
				n[l].position = l;
				l++;
			}
		/*for (int j = 0; j < 28; j++) // a visual interpretation of the image
		{
		cout << "\n";
		for (int k = 0; k < 28; k++)
		{
		if (p[i].mesh[j][k] > 0)
		cout << "# ";
		else
		cout << "  ";
		}
		}
		*/
		cout << "\n layer zero initalized";
		int while_counter = 0;// for having 748 iterations;

		for (int i = 0; i < 16; i++)
		{
			l = 783;
			w_sum = 0;
			for (; l >= 0; l--)
			{

				w_sum += n[l].brightness*w[while_counter++].w;


			}

			w_sum = w_sum / (784);// taking the average of w sum
			n2[i].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[i].position = i;
		}


		cout << "\n layer one initalized";

		for (int a = 16; a < 32; a++)
		{
			y_mirror = 15;
			w_sum = 0;
			l = 0;
			while (y_mirror >= 0)
			{
				w_sum += n2[l].brightness*w[while_counter++].w;
				y_mirror--;
				l++;
			}
			w_sum /= (16);

			n2[a].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[a].position = a;
		}
		l = 15;


		cout << "\n layer two initalized";

		for (int a = 32; a < 42; a++)
		{
			l = 16;
			w_sum = 0;
			while (!(l == 32))
			{

				w_sum += n2[l++].brightness*w[while_counter++].w;
			}
			w_sum /= (16);

			n2[a].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[a].position = a;

		}

		cout << "\n end layer initalized";
		long double big = n[32].brightness; // to find the most probable number
		int label;
		for (int i = 32; i < 42; i++)
		{
			if (n2[i].brightness > big)
			{
				big = n2[i].brightness;
				label = n2[i].position - 32;
			}
		}
		cout << "\n the digit this recognised is";
		int g;
		g = label;
		switch (g) // determining the correct number
		{
		case 1: cout << "\n 1";
			break;
		case 2: cout << "\n 2";
			break;
		case 3: cout << "\n 3";
			break;
		case 4: cout << "\n 4";
			break;
		case 5: cout << "\n 5";
			break;
		case 6: cout << "\n 6";
			break;
		case 7: cout << "\n 7";
			break;
		case 8: cout << "\n 8";
			break;
		case 9: cout << "\n 9";
			break;
		case 0: cout << "\n 0";
			break;
		default: cout << "\edit the code";
			break;
		}

	}
	cout << "\n";
	delete p;
	system("pause");

}
void train()// the same thing as the test function, but with the gradient descent
{
	int a, temp, grad = 0; // initialising the variables

	ifstream mnsit_reader;
	ofstream custom_file_dump;

	custom_file_dump.open("C:\\Users\\dhruv\\Downloads\\solid_buffer.dat");
	mnsit_reader.open("C:\\Users\\dhruv\\Downloads\\mnist_train.txt");

	if (mnsit_reader.is_open() && custom_file_dump.is_open())// checks if the file actually opens
		cout << "File successfully open" << endl;
	else
		cout << "Error opening file" << endl;

	cout << "\n enter the number of batches" << endl;//TYPICALLY 500-1500)
	cin >> a;

	pixel *p;// dynamic structure allocation of the mnist CSV to matrix format
	p = new pixel[a];

	gradient_descent *delta;// the Nudgeing arrays
	delta = new gradient_descent[a];

	mnsit_reader.seekg(ios::beg);// puts the get point onto the beginning of the file
	custom_file_dump.seekp(0, ios::beg);

	// puts the get point onto the beginning of the file
	for (int i = 0; i < a; i++)// takes the csv files and loads it into the structures 
	{
		cout << "\n SCANNING BLOCK = " << i << endl;
		mnsit_reader >> temp;
		p[i].label = temp;
		for (int j = 0; j < 28; j++)
		{
			for (int k = 0; k < 28; k++)
			{
				mnsit_reader >> temp;
				p[i].mesh[j][k] = temp;
			}
		}

	}

	cout << "\n STRUCTURES READY IN THE BUFFER\n \n PROCEEDING TO TESTING" << endl;
	mnsit_reader.close();
	system("cls");
	cout << "\n bufferring layer one";
	neuron_one n[784];
	weights w[13000];/* 784x 16 + 16x16 + 160(13000~12900) */
	neuron_two n2[42]; // 16+16 +10
	int y = 0, y_mirror;// is the index for weights
	for (int i = 0; i < a; i++)// the maing sturture loading loop
	{
		int l;
		long double w_sum = 0, temp;
		l = 0;

		system("pause");
		for (int j = 0; j < 28; j++)
			for (int k = 0; k < 28; k++)
			{
				temp = p[i].mesh[j][k];
				temp = (temp / 255);
				n[l].brightness = temp;
				n[l].position = l;
				cout << endl << "the brightness of the neuron" << n[l].brightness << "\tpos\t" << n[l].position;
				l++;
			}
		cout << "\n in the loop";
		system("pause");
		cout << "\n layer zero initalized";
		int while_counter = 0;// for having 748 iterations;

		for (int i = 0; i < 16; i++)
		{
			l = 783;
			w_sum = 0;
			for (; l >= 0; l--)
			{
				w[while_counter].index = a;
				w[while_counter].serial = while_counter;
				w_sum += n[l].brightness*w[while_counter++].w;
			}

			w_sum = w_sum / (784);// taking the average of w sum
			n2[i].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[i].position = i;


			cout << endl << "the brightness of the neuron" << n2[i].brightness << "\tpos\t" << n2[i].position;

		}

		system("pause");
		cout << "\n layer one initalized";

		for (int a = 16; a < 32; a++)
		{
			y_mirror = 15;
			w_sum = 0;
			l = 0;
			while (y_mirror >= 0)
			{
				cout << n2[l].brightness << "\n";
				w[while_counter].index = a;
				w[while_counter].serial = while_counter;
				w_sum += n2[l].brightness*w[while_counter++].w;
				y_mirror--;
				l++;
			}
			w_sum /= (16);

			n2[a].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[a].position = a;
		}
		l = 15;
		cout << l;
		system("pause");
		cout << "\n layer two initalized";

		for (int a = 32; a < 42; a++)
		{
			l = 16;
			w_sum = 0;
			while (!(l == 32))
			{
				w[while_counter].index = a;
				w[while_counter].serial = while_counter;
				w_sum += n2[l++].brightness*w[while_counter++].w;
			}
			w_sum /= (16);

			n2[a].brightness = (pow(2.71828, w_sum) / (1.0 + pow(2.71828, w_sum)));
			n2[a].position = a;

			cout << "the brightness of end layer is" << n2[a].brightness << "position is" << n2[a].position << endl;
		}
		system("pause");
		cout << "\n end layer initalized";
		int label, g;
		g = 32 + temp;
		label = p[g].label;
		long double big[10];
		int c = 0, index[10];
		for (int d = 16; d < 19; d++)
			big[c++] = n2[d].brightness;
		for (int d = 16; d < 32; d++)
			for (int c = 0; c < 4; c++)
				if (big[c] < n2[d].brightness)
				{
					big[c + 1] = big[c];
					index[c + 1] = index[c];
					big[c] = n2[d].brightness;
					index[c] = n2[d].brightness;
				}
		int writer = 0, d = 0;
		for (int f = 12960; f>12800; f--)// changing layer three
		{
			for (int c = 0; c < 4; c++)
				if (index[c] == w[i].index)// reduces or increases weights proportional to the brightness
					delta[a].nudge[f] = w[f].w*n[index[c]].brightness;
				else
					delta[a].nudge[f] = -1 * (w[f].w*n[index[c]].brightness);
		}
		// find the largest neurons in layer two that affect the layer three
		for (int d = 0; d < 6; d++)
			big[c++] = n2[d].brightness;
		for (int d = 0; d < 16; d++)
			for (int c = 0; c < 6; c++)
				if (big[c] < n2[d].brightness)
				{
					big[c + 1] = big[c];
					index[c + 1] = index[c];
					big[c] = n2[d].brightness;
					index[c] = n2[d].brightness;
				}
		for (int f = 12800; f>12544; f--)// changing layer three
		{
			for (int c = 0; c < 4; c++)
				if (index[c] == w[i].index)// reduces or increases weights proportional to the brightness
					delta[a].nudge[f] = w[f].w*n[index[c]].brightness;
				else
					delta[a].nudge[f] = -1 * (w[f].w*n[index[c]].brightness);
		}
		int final_layer_index = 783;
		for (int f = 12544; f >= 0; f--)
			delta[a].nudge[f] = w[f].w*n[final_layer_index--].brightness;
		cout << "\n gradient decent for the batch\t" << i << "computed" << "writing";


	}
	const int x = 99999;// this will calculate the average of the weights
	for (int i = 0; i < a; i++)
	{
		for (int f = 12960; f >= 0; f--)
			delta[x].nudge[f] += delta[i].nudge[f];
	}
	for (int f = 12960; f >= 0; f--)
	{
		custom_file_dump << delta[x].nudge[f] << "\n";
	}
	cout << "\n ALL OUT";
	system("pause");
	delete p;
	delete delta;
	custom_file_dump.close();

}
int main()
{
	char ch, i;

	for (int i = 1; i < 32; i++)
		cout << "#";

	cout << endl;
	cout << "\n SELECT AN OPTION\n";
	for (int i = 1; i < 32; i++)
		cout << "#";

	do
	{
		cout << "\n1- TEST\n2- TRAIN\n PRESS ANY OTHER KEY TO TERMINATE\n";
		cin >> ch;
		switch (ch)
		{
		case '1': test();
			break;
		case '2': train();
			break;
		default:
			cout << "\n";
			system("pause");
		}
		cout << "\n do you wish to continue(Y/N)" << endl;
		cin >> i;

	} while ((i == 'y') || (i == 'Y'));

}




