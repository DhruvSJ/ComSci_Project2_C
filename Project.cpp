/*
Dhruv Jaiswal
 Problem:   Create a program that can draw data from a file of the user's choice,
            make calculations based with the drawn data using a certain element
            and its wavelength, then display that data in the form of a table in
            new file of the user's choice.

Input:      The input from the user should be the file they want to extract the
            data from and they file they want to open the table in.
    
            At the end of program, I will ask if they would like get data from
            another file and they will respond yes or no.

Output:     The output will be a file with a table displaying 4 sets of numbers:
            The 2-theta values,
            The intesity,
            The D-values, and
            The Q-values.
 
            This table will have a header saying material the anode is made of and
            the wavelength of that material.
            Under the table, will display how many peaks were in the file and
            ask if the user would like to pull data from a new file.

Algorithm:  This program will be built with the intention of analyzed data obtained
            from an x-ray powder diffractometer used to characterize
            materials.
 
            First, I will ask the user what file they would like to draw data from
            and what they want to output table of calculations in.
            
            Then take the data from the file and perform calculations for the
            D-value and Q value (1/(sin(theta))^2) from equation
            n(lamda) = 2*d*sin(theta).
            "n" is the harmonic of the diffracted beam.
            "d" is the interplanar spacing between the planes of specific
            orientation in the material.
            Theta is the angle between the x-ray beam and the sample of material.

            The data obtained from the file will be 2*theta, so I will have to
            divide by 2 to properly use it in my equation.
            Lamda is the wavelength of the material being tested. The certain
            material that is used will be read from the file and depending on what
            it is will what lamda is.
            The values from the file will be read till the end and a counter will
            keep track of how many peaks are in the file.
 
            This information will then displayed as a table using appropriate
            spacing between each of the four columns.
            The table will have a header displaying the material used and its
            wavelength.
            Ask if the user would like to draw data from a new file, in which they
            will respond with a "y" or "n" for yes or no.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
int main()
{
    //PI for calculations
    const double pi = 3.14159;
 
    
    //varibles and open functions
	ifstream gather;
	ofstream output;
	int intensity, peaks = 0, inRow = 0;
	double Q, d, twoTheta, lamda = 0, radians, n = 1;
	string inFile, outFile, material, sampleName;
	char rerun;
    
	do
	{
		cout << "What is the name of your input file?" << endl;
		cin >> inFile;

		cout << "What is the name of your output file?" << endl;
		cin >> outFile;

		gather.open(inFile);
		output.open(outFile);

		getline(gather, sampleName);
		gather >> material;

		// figure out the material used and its wavelength
		if (material == "Cu")
		{
			lamda = 1.54059;
		}
		if (material == "Cr")
		{
			lamda = 2.28973;
		}
		if (material == "Fe")
		{
			lamda = 1.93604;
		}
		if (material == "Co")
		{
			lamda = 1.78900;
		}
		if (material == "Mo")
		{
			lamda = 0.70932;
		}
		
		//header and column labels with setprecision for proper decimal places
		cout << endl << "For " << sampleName << " with an anode of " << material << " and wavelength of " << setprecision(6) << lamda << ", the" << endl;
		
        cout << "values are:" << endl << endl;
		
        cout << setw(12) << "2-theta" << setw(15) << "Insensity" << setw(15) << "d values" << setw(17) << "Q values" << endl;

		//output to paste the values and statements in the open file.
        output << endl << "For " << sampleName << " with an anode of " << material << " and wavelength of " << setprecision(6) << lamda << ", the" << endl;
		
        output << "values are:" << endl << endl;
		
        output << setw(12) << "2-theta" << setw(15) << "Insensity" << setw(15) << "d values" << setw(17) << "Q values" << endl;

		// gathers data and makes calculations until there is no data left
        
		while (!gather.eof())
		{
			gather >> twoTheta >> intensity;
			peaks++;

			radians = (pi * twoTheta) / 180.0;
			d = (n * lamda) / (2.0 * sin(radians / 2.0));
			Q = 1 / pow(sin(radians / 2.0), 2.0);

			cout << setw(12) << setprecision(5) << showpoint << twoTheta << setw(12) << intensity << setw(18) << setprecision(6) << d << setw(17) << setprecision(7) << Q << endl << endl;
			
            output << setw(12) << setprecision(5) << showpoint << twoTheta << setw(12) << intensity << setw(18) << setprecision(6) << d << setw(17) << setprecision(7) << Q << endl << endl;
		}

		cout << "There were " << peaks << " peaks in the file." << endl;
		output << "There were " << peaks << " peaks in the file." << endl;
	
		gather.close();
		output.close();

		// asking the user if they want to analyze another file
		cout << "Do you want to analyze data from another file? (y/n)" << endl;
		cin >> rerun;

		if (rerun == 'y' || rerun == 'Y')
		{
			cout << endl;
			peaks = 0;
		}
	} while (rerun == 'y' || rerun == 'Y');

	return (0);
}
