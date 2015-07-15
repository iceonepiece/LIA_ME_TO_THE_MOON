#include "ImageHelper.h"
#include "qdebug.h"
#include "Blob.h"

ImageHelper::ImageHelper()
{

}

ImageHelper::~ImageHelper()
{

}

void ImageHelper::convertToGreyScale(const cv::Mat& input, cv::Mat& output)
{
	cv::cvtColor(input, output, CV_BGR2GRAY);
}

void ImageHelper::removeBackground(std::vector<Blob>& list_blob, cv::Mat& mat_blob)
{
	//set threshold values
	const int bgAreaTH = 3000;
	const int contourLenTH = 500;
	const int edgePixelTh = 100;
	//set constants for row/column before the last
	const int maxX = mat_blob.cols - 2;
	const int maxY = mat_blob.rows - 2;

	for (int i = 0; i < list_blob.size(); i++)
	{

		//get the area and length of each contour
		int area = list_blob[i].area;
		int len = list_blob[i].contour.size();

		//check conditions: large area and long contour
		if ((area > bgAreaTH) || (len > contourLenTH))
		{
			int countEdgePixel = 0;
			for (int n = 0; n < list_blob[i].contour.size(); ++n)
			{
				int x = list_blob[i].contour[n].x;
				int y = list_blob[i].contour[n].y;
				if ((x == 1) || (x == maxX) || (y == 1) || (y == maxY))
					countEdgePixel++;
			}

			//check condition: many contour points located of the boundary of image
			if (countEdgePixel > edgePixelTh)
			{
				list_blob[i].type = Blob::BACKGROUND;
				cv::floodFill(mat_blob, list_blob[i].contour[len / 2], 128);
			}
		}
	}
}

QImage ImageHelper::matToQImage(const cv::Mat& mat)
{
	switch (mat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
		return image;
	}

		// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

		return image.rgbSwapped();
	}

		// 8-bit, 1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable;

		// only create our color table once
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
				sColorTable.push_back(qRgb(i, i, i));
		}

		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);

		image.setColorTable(sColorTable);

		return image;
	}

	default:
		qDebug() << "Error: cannot convert mat to QImage -" << mat.type();
		break;
	}

	return QImage();
}

double ImageHelper::findZoomSize( int originalSize, int zoomValue )
{
	return (zoomValue / 100.0) * originalSize;
}

void ImageHelper::floodFill(cv::Mat& img, cv::Point point, int newColor, std::vector<cv::Point>& points)
{
	int width = img.cols;
	int height = img.rows;

	int seedColor = img.at<uchar>(point.y, point.x);

	if (seedColor == newColor)
		return;

	std::queue<cv::Point> analyze_queue;
	analyze_queue.push(point);
	cv::Point currentPoint;

	while (!analyze_queue.empty())
	{
		currentPoint = analyze_queue.front();

		if (img.at<uchar>(currentPoint.y, currentPoint.x) != seedColor)
		{
			analyze_queue.pop();
			continue;
		}

		cv::Point leftmost_pt = analyze_queue.front();

		leftmost_pt.x -= 1;
		analyze_queue.pop();
		cv::Point rightmost_pt = leftmost_pt;
		rightmost_pt.x += 2;

		while (leftmost_pt.x >= 0 && img.at<uchar>(leftmost_pt.y, leftmost_pt.x) == seedColor)
			--leftmost_pt.x;


		while (rightmost_pt.x < width && img.at<uchar>(rightmost_pt.y, rightmost_pt.x) == seedColor)
			++rightmost_pt.x;

		bool check_above = true;
		bool check_below = true;

		cv::Point pt = leftmost_pt;
		++pt.x;
		for (; pt.x < rightmost_pt.x; ++pt.x)
		{
			img.at<uchar>(pt.y, pt.x) = newColor;
			points.push_back(cv::Point(pt.x, pt.y));

			cv::Point pt_above = pt;
			--pt_above.y;

			if (pt_above.y >= 0)
			{
				if (check_above)
				{
					if (img.at<uchar>(pt_above.y, pt_above.x) == seedColor)
					{
						analyze_queue.push(pt_above);
						check_above = false;
					}
				}
				else // !check_above
				{
					check_above = (img.at<uchar>(pt_above.y, pt_above.x) != seedColor);
				}
			}

			cv::Point pt_below = pt;
			++pt_below.y;
			if (pt_below.y < height)
			{
				if (check_below)
				{
					if (img.at<uchar>(pt_below.y, pt_below.x) == seedColor)
					{
						analyze_queue.push(pt_below);
						check_below = false;
					}
				}
				else // !check_below
				{
					check_below = (img.at<uchar>(pt_below.y, pt_below.x) != seedColor);
				}
			}
		} // for 
	} // while queue not empty

}