#include "FatTrainer.h"
#include "qdebug.h"

FatTrainer::FatTrainer()
{

}

FatTrainer::~FatTrainer()
{

}

void FatTrainer::train( std::string path)
{
	std::string trainImageName;
	std::string gtImageName;
	std::vector<Blob> list_blob;

	cv::Mat mat_gt;
	cv::Mat mat_original;

	std::vector<std::string> listImageName = getListFromFile(path + "/train_image_list.txt");

	for (int i = 0; i < listImageName.size(); i++)
	{
		trainImageName = listImageName[i] + ".tif";
		gtImageName = "(BG)" + trainImageName;

		//load ground truth and training image
		mat_gt = cv::imread(path + "/" + gtImageName, CV_LOAD_IMAGE_GRAYSCALE);
		mat_original = cv::imread(path + "/" + trainImageName, CV_LOAD_IMAGE_COLOR);

		//find contours from ground truth image
		findContoursFromGt(mat_gt, list_blob);
		
		FeatureExtractor::findAreaAndCircularity(list_blob);

		cv::Mat mat_grey;
		cv::cvtColor(mat_original, mat_grey, CV_BGR2GRAY);

		FeatureExtractor::findAverageGreyLevel(mat_grey, mat_gt, list_blob);
	}

	cv::Mat vect_feature, vect_label;

	//convert all sample into feature vector for SVM and train it
	convertBlobToVector(list_blob, vect_feature, vect_label);

	trainSVM(vect_feature, vect_label);
}

void FatTrainer::trainSVM(const cv::Mat& vect_feature, const cv::Mat& vect_label)
{
	cv::SVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::RBF;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, FLT_EPSILON);

	cv::SVM trainedSvm;
	trainedSvm.train_auto(vect_feature, vect_label, cv::Mat(), cv::Mat(), params);
	trainedSvm.save("C:/Users/X220/Desktop/hey_fat_train.xml");
	qDebug() << "SAVE COUNT" << trainedSvm.get_support_vector_count();
}

void FatTrainer::convertBlobToVector( const std::vector<Blob>& list_blob, cv::Mat& vect_feature, cv::Mat& vect_label )
{
	vect_feature = cv::Mat(list_blob.size(), 3, CV_32FC1); // 3 features
	vect_label = cv::Mat(list_blob.size(), 1, CV_32FC1);
	
	for (int i = 0; i < list_blob.size(); i++)
	{
		double area = list_blob[i].area;
		if (area > 3000)
			area = 3000;

		vect_feature.at<float>(i, 0) = normalize( area, 1, 3000 );
		vect_feature.at<float>(i, 1) = normalize(list_blob[i].circularity, 0, 1);
		vect_feature.at<float>(i, 2) = normalize(list_blob[i].avgGrayLevel, 0, 255);

		vect_label.at<float>(i, 0) = list_blob[i].label;
	}
}

float FatTrainer::normalize(float x, float min, float max)
{
	return (x - min) / (max - min);
}

std::vector<std::string> FatTrainer::getListFromFile(std::string path)
{
	std::vector<std::string> list;
	std::ifstream infile(path);
	std::string line;

	if (infile.is_open())
	{
		while (std::getline(infile, line))
			list.push_back(line);
	}

	return list;
}

void FatTrainer::findContoursFromGt(const cv::Mat& mat_blob, std::vector<Blob>& list_blob )
{
	produceBlobs(mat_blob, FAT_COLOR, FAT_LABEL, list_blob);
	produceBlobs(mat_blob, NON_FAT_COLOR, NON_FAT_LABEL, list_blob);
}

void FatTrainer::produceBlobs(const cv::Mat& mat_blob, int color, int label, std::vector<Blob>& list_blob )
{
	std::vector<Contour> list_contour;

	cv::Mat mat_target(mat_blob.rows, mat_blob.cols, mat_blob.type());
	detectColor(mat_blob, color, mat_target);
	cv::findContours(mat_target, list_contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (Contour contour : list_contour)
	{
		Blob blob;
		blob.contour = contour;
		blob.label = label;
		
		list_blob.push_back(blob);
	}

}

void FatTrainer::detectColor(const cv::Mat& img, const int color, cv::Mat& out)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++) 
		{
			int val = (int)img.at<uchar>(i, j);

			if (val == color)
				out.at<uchar>(i, j) = 255;	//white
			else
				out.at<uchar>(i, j) = 0;	//black
		}
	}
}

void FatTrainer::extractFeatures( cv::Mat& mat_original, std::vector<Contour>& list_contour, std::vector<Blob>& list_blob)
{

	cv::Mat mat_contour(mat_original.size(), CV_8UC3, cv::Scalar(0, 0, 0));

	cv::drawContours(mat_contour, list_contour, -1, cv::Scalar(255, 255, 255));

	cv::namedWindow("ccc");
	cv::imshow("ccc", mat_contour);

	//for (Contour contour : list_contour)
	//{
	//	qDebug() << contour.size();
	//}
}


//void FatTrainer::calculateFeatures(const cv::Mat& mat_gt, const cv::Mat& mat_input, std::vector<Blob>& list_blob, std::vector<int>& list_labels) 
//{
//	std::vector<int> list_tempLabel;
//	cv::Mat mat_fat, mat_nonFat;
//
//	mat_nonFat = mat_gt.clone();
//	mat_fat = mat_gt.clone();
//
//	for (int i = 0; i < mat_nonFat.rows; ++i)
//		for (int j = 0; j < mat_nonFat.cols; ++j)
//			if (mat_nonFat.at<uchar>(i, j) == 128)
//				mat_nonFat.at<uchar>(i, j) = 255;
//			else
//				mat_nonFat.at<uchar>(i, j) = 0;
//
//	for (int i = 0; i < mat_fat.rows; ++i)
//		for (int j = 0; j < mat_fat.cols; ++j)
//			if (mat_fat.at<uchar>(i, j) == 0)
//				mat_fat.at<uchar>(i, j) = 255;
//			else
//				mat_fat.at<uchar>(i, j) = 0;
//
//	cv::waitKey(0);
//	//------------------------------------ Non-fat ------------------------------------------------//
//	cv::Mat mat_blob1 = mat_nonFat.clone();
//	std::vector<Contour> list_nonFatContour;
//
//	cv::findContours(mat_blob1, list_nonFatContour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//
//	std::vector<Blob> list_blob1;
//	FatProcessor::findAreaAndCircularity(list_nonFatContour, mat_blob1);
//	findAverageGreyLevel(input, nonfatImg, nonFatContours, blobFts1);
//	std::vector<int> tempLabels1 = std::vector<int>(blobFts1.size(), NON_FAT_LABEL);
//
//	//----------------------------------- Fat --------------------------------------------------//
//	cv::Mat blobImg2 = fatImg.clone();
//	SetOfContours fatContours;
//	fatFindContours(blobImg2, fatContours);
//	std::vector<BlobFeatures> blobFts2;
//	findAreaAndCircularity(fatContours, blobFts2);
//	findAverageGreyLevel(input, fatImg, fatContours, blobFts2);
//	std::vector<int> tempLabels2 = std::vector<int>(blobFts2.size(), FAT_LABEL);
//
//	//---------------------------------------------------------
//	blobFts.insert(blobFts.end(), blobFts1.begin(), blobFts1.end());
//	blobFts.insert(blobFts.end(), blobFts2.begin(), blobFts2.end());
//	//---------------------------------------------------------
//}

//FatTrainer::extractFeatures( cv::Mat mat_gt, cv::Mat mat_original, int label )
//{
//	cv::Mat mat_blob = mat_gt.clone();
//	std::vector<Contour> list_contour;
//	cv::findContours(mat_blob, list_contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	std::vector<Blob> list_blob;
//
//	findAreaAndCircularity(list_contour, list_blob);
//	findAverageGreyLevel(mat_original, mat_gt, list_contour, list_blob);
//	std::vector<int> list_tempLabel = std::vector<int>(list_blob.size(), label );
//}
