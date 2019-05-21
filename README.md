# Machine Learning Application

# How:
1. Download MLProcessor.zip
2. Unzip it, the executable file is in it.

# Outline:
1. Purpose of this software
2. Procedure for data mining
    1. Open proper data file
    2. Feature extraction and Data Preprocessing
    3. Classification model
    4. Accuracy judgement 
3. Prediction of unknown peptide 

# What:
1. Purpose of this software

    If you are a biology student, this software will help you classify raw peptide data into two classes, which is helpful to judge whether a peptide can resist certain virus, bacteria, fungi or so on. Later, you can predict unknown peptide using the most accurate classification model to judge whether it has certain function or not.

2. Procedure for data mining
    1. Open proper data file

        Click “File” -> “Open”.

        You should import a txt file. Its format for each line should be,

        1	AAARIRHEGVFLLIGNSCFSLPRNGPQLLLLAW
        0	VFDIIKGAGKQLIARAMGKIAEKVGLNKD

        where 0 stands for negative class, 1 stands for positive class. Following are raw peptides.

        If you import improper data, the program will return warning information.

    2. Feature extraction and Data Preprocessing

        Click “Data” -> “Data Extraction”.

        This process will calculate features of raw peptides including Amino Acid Composition, Composition of k-spaced Amino Acid Pairs (k = 0) and Amino Acid Composition of k-spaced.

        Histograms to compare features of positive data and negative data will be shown.

        Click “Data” -> “Data Preprocessing”

        This process will use Principal Component Analysis to reduce dimension of data. Data visualization of data will help to display outliers.

    3. Classification model

        (1) Click “Model” -> “Tree Model”   
        Decision tree model. Show structure of tree.

        (2) Click “Model” -> “SVM”
        Support vector machine model. Visualize hyperplanes of results.

        (3) Click “Model” -> “Logistic Regression”
        Logistic regression model. 

        (4) Click “Model” -> “Bayes”
        Naive Bayes model. 
        
        (5) Click “Model” -> “KNN”
        K-nearest neighbor model. Return a plot to show relationship between k and accuracy.

    4. Accuracy judgement

        Use cross validation to calculate accuracy, error rate, sensitivity, specificity to compare different models. Also, ROC curves will be provided for further judgement after you click each model.


3. Predict unknown peptides

    Click “Predict”
    Enter a peptide string you want to predict whether it has the same function of positive data in previous classification dataset. 
    Select the model you want. For KNN model, you should select proper value for K which has been reflected in previous plot.
    Later, the program will provide you the predicting result of positive/negative.


Great thanks to to my teammates!

Lirong Wang, Binbin Huang, Dinglin Xia, Minjue Zhang, Nuoyao Yang
