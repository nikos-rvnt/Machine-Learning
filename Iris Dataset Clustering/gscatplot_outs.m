
filename = fullfile( 'IrisDataset_Clustering', 'IrisDataset_Clustering', 'pc1.txt') ;
fileID = fopen(filename) ;
C = textscan( fileID, '%f') ;
fclose(fileID);

filename2 = fullfile( 'IrisDataset_Clustering', 'IrisDataset_Clustering', 'pc2.txt');
fileID2 = fopen(filename2);
C2 = textscan(fileID2,'%f');
fclose(fileID2);

filename3 = fullfile( 'IrisDataset_Clustering', 'IrisDataset_Clustering', 'labels.txt');
fileID3 = fopen(filename3);
C3 = textscan(fileID3,'%f');
fclose(fileID3);

pc1 = C{1,1}; % zeros(150,1);
pc2 = C2{1,1}; % zeros(150,1)
labels = C3{1,1};

figure(1) ;
title('Red-Green-Blue in respect to Sentosa-Virginica-Versicolor');
gscatter( pc1, pc2, labels, [], [], [], 'on', 'PC1', 'PC2') ;