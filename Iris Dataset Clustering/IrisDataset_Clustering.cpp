/** ----------------------------------------------------------------------------------------------------------------------------

IrisDataset_Clustering.cpp : Defines the entry point for the console application.

------------------------------------------------------------------------------------------------------------------------------ */

#include "stdafx.h"
#include <iostream>  
#include <fstream>      
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>    
#include <iterator>     
#include <Eigen\Dense>
#include <Eigen\Core>
#include <Eigen\Eigen>

//using std::istringstream;
//using std::ostringstream;
using namespace::std;
using namespace Eigen;

int main() 
{
	
	ifstream file("Fisher.csv"); 
	string value;
	MatrixXf iris(150, 4);
	iris.setZero();
	VectorXf irisLabels(150, 1);

	string grammh;
	int j, i = 0;
	float sam = 0.0, samCol1 = 0.0, samCol2 = 0.0, samCol3 = 0.0, samCol4 = 0.0;

	getline(file,grammh);
	// read line by line 
	while (getline(file, grammh))
	{
		// next line input of Fisher.csv
		string value;
		stringstream linestream(grammh);
		j = 0;
		
		// read column by column till not anymore ','
		while (getline(linestream, value, ','))
		{
			cout << " " << value << " ";
			
			// from first column keep the value as iris kind
			if (j == 0) {
				float valueLabel = (float)atoi(value.c_str());
					/* 3 iris kinds : 0 - Sentosa, 1 - Versicolor, 2 - Indica */ 
					irisLabels(i) = valueLabel;
			}
			
			// from the rest columns keep each characteristic as 
			// PW (petal width), PL (petal length), SW (sepal width), SL (sepal length)
			else {
				
				float valueFlo = (float)atoi(value.c_str());
				iris(i, j-1) = valueFlo;
				
				if ((j-1) == 0)
					samCol1 = samCol1 + valueFlo;
				if ((j-1) == 1)
					samCol2 = samCol2 + valueFlo;
				if ((j-1) == 2)
					samCol3 = samCol3 + valueFlo;
				if ((j-1) == 3)
					samCol4 = samCol4 + valueFlo;
				
			}
			j++;
		}
		cout << endl;
		i++;

	}

	/* ----------------------------------  Clustering using PCA via SVD ---------------------------------------------  */

	/* Preprocessing: normalising data each column divided by the sum of it (eitherwise could substract the mean)  */
	for (int i = 0; i < 150; i++) {
		j = 0;
		if (j == 0){
			iris(i, j) = iris(i, j) / samCol1;
			++j;
		}
		if (j == 1) {
			iris(i, j) = iris(i, j) / samCol2;
			++j;
		}
		if (j == 2) {
			iris(i, j) = iris(i, j) / samCol3;
			++j;
		}
		if (j == 3) {
			iris(i, j) = iris(i, j) / samCol4;
			++j;
		}
	}

	/* Forming (iris'*iris) matrix for input on svd */
	MatrixXf irisII(4, 4);
	irisII = iris*iris.transpose();

	/* Calling Eigen's svd() for calculating eigenvectors */
	JacobiSVD<MatrixXf> svdOfiris(irisII, ComputeFullU | ComputeFullV) ;
	
	// ----------------------------------- eigeniris - clusters ------------------------------------------------------------
	
	/** multiply original iris data by first two eigenvectors of first two highest eigenvalues respectively
	 this results in principal components. Plotin them (on scatter plot way) will show up the clusters 
	 of the data on the three iris kinds. */
	const MatrixXf irisSVDU = svdOfiris.matrixU().block(0,0,4,2);
	MatrixXf irisClust;
	irisClust.setZero();
	irisClust = iris*irisSVDU; 
	cout << "gr: " << irisClust.rows() << "st: " << irisClust.cols();

	vector<float> pc1(150);
	vector<float> pc2(150);
	vector<float> labels(150);
	for (int i = 0; i < 150; i++) {
		// first principal component comes from first column of irisClust
		pc1[i] = irisClust(i, 0);
		// second principal component comes from second column of irisClust
		pc2[i] = irisClust(i, 1);	
		labels[i] = irisLabels(i);
		cout << pc1[i] << "defsfrs" << pc2[i] << endl;
	}

	/* --------- Write output (pc1,pc2,labels) to .txt file (each output is each principal component) ---------- */
	ofstream output_file("./pc1.txt");
	ofstream output_file2("./pc2.txt");
	ofstream output_file4("./labels.txt");

	ostream_iterator<double> output_iterator1(output_file, "\n");
	ostream_iterator<double> output_iterator2(output_file2, "\n");
	ostream_iterator<double> output_iterator4(output_file4, "\n");

	copy(pc1.begin(), pc1.end(), output_iterator1);
	copy(pc2.begin(), pc2.end(), output_iterator2);
	copy(labels.begin(), labels.end(), output_iterator4);

	return 0 ;

}

