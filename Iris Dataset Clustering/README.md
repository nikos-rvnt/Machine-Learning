
Implemeted on Visual Studio 2017 (thats why included targetver.h, stdafx.cpp, stdafx.h). Using Eigen Library (http://eigen.tuxfamily.org/index.php?title=Main_Page) for matrix/vector manipulation and svd operation.

Clustering on data input of the "Fisher.csv" which includes 150 row data of 4 characteristics of 3 Types or Iris flower (Sentosa, Versicolor, Virginica).

The first column takes values {0,1,2} in respect of kind of type. The next four columns are the characteristics, that is PW (petal width), PL (petal length), SW (sepal width), SL (sepal length).

PCA on X (or SVD on XX') can be used for clustering purposes. (see: http://www2.imm.dtu.dk/pubdb/views/edoc_download.php/4000/pdf/imm4000 , http://meyer.math.ncsu.edu/Meyer/Talks/ClusteringMonopoli_9_11_07.pdf , https://people.eecs.berkeley.edu/~jrs/189/lec/21.pdf)

Multiplying the first # coeff. vectors producted by PCA (or the first # eigenvectors of SVD on XX') with the original data features
we get them in another space which maximises in between variance. So, multiplying :

                                          iris*irisSVDU(4,2) 
                                          
gives a 150x2 matrix which includes the 2 principal components. I save on .txt file the 2 vectors of each principal component and also the labels included on data. Sending them on matlab to use gscatter(). The result of the succeeded clustering on iris data is illustrated through "gscatplot_outs.m" on "iris_clusters.jpg" file included.