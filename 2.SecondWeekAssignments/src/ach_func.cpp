#include "../lib/func.h"

bool equal(float a,float b) {return abs(a - b) <= 0.0001;}
void bgr2gray(Mat &InputImage,Mat &OutputImage)
{
    for(int i=0;i<InputImage.rows;++i)
        for(int j=0;j<InputImage.cols;++j)
        {
            uchar B = InputImage.at<Vec3b>(i,j)[0],G = InputImage.at<Vec3b>(i,j)[1] ,R = InputImage.at<Vec3b>(i,j)[2];
            OutputImage.at<uchar>(i,j) = 1.0 * R * 0.299 + 1.0 * G * 0.587 + 1.0 * B * 0.114;
        }
}

void bgr2hsv(Mat &InputImage,Mat &OutputImage)
{
    for(int i=0;i<InputImage.rows;++i)
        for(int j=0;j<InputImage.cols;++j)
        {
            uchar B = InputImage.at<Vec3b>(i,j)[0],G = InputImage.at<Vec3b>(i,j)[1] ,R = InputImage.at<Vec3b>(i,j)[2];
            float B_ = B / 255.0,G_ = G / 255.0,R_ = R / 255.0;
            float Cmax = max(B_,max(G_,R_)),Cmin = min(B_,min(G_,R_));
            float delta = Cmax - Cmin;


            //calc h
            float h;
             if (equal(Cmax,Cmin)) 
                h = 0.0;
            else 
            {
                if (equal(R_,Cmax)) 
                {
                    h = 60.0 * (G_ - B_) / (Cmax - Cmin) + 0.0;
                } 
                else if (equal(Cmax,G_)) 
                {
                    h = 60.0 * (B_ - R_) / (Cmax - Cmin) + 120.0;
                } 
                else 
                {
                    h = 60.0 * (R_ - G_) / (Cmax - Cmin) + 240.0;
                }
                if (h < 0.0) h += 360.0;
            }

            //calc s
            float s;
            if(equal(Cmax,0)) s = 0;
            else s = delta / Cmax; 


            //calc v
            float v;
            v = Cmax;
            // cout<<h<<' '<<s<<' '<<v<<endl;
            OutputImage.at<Vec3f>(i,j)[0] = h;
            OutputImage.at<Vec3f>(i,j)[1] = s;
            OutputImage.at<Vec3f>(i,j)[2] = v;
        }

}
void ResizeScale(Mat &InputImage,Mat &OutputImage,double scale)
{
    if(scale == 1) return OutputImage = InputImage, void();
    Size newSize = Size((int)(floor)(InputImage.cols * scale),(int)(floor)(InputImage.rows * scale));
    if(scale >  1) return pyrUp(InputImage,OutputImage,newSize), void();
    return resize(InputImage,OutputImage,newSize), void();
}

vector<Mat> getCarLicense(Mat &InputImage)
{
    int pic_height = InputImage.rows;
    int pic_width = InputImage.cols;

    Mat image;
    GaussianBlur(InputImage, image, Size(3, 3), 0); 

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY); 

    Mat Sobel_x;
    Sobel(gray_image, Sobel_x, CV_16S, 1, 0);

    Mat absX;
    convertScaleAbs(Sobel_x, absX); 

    Mat thresholded;
    threshold(absX, thresholded, 0, 255, THRESH_OTSU);

    // imshow("th",thresholded);

    Mat kernelX = getStructuringElement(MORPH_RECT, Size(15, 4));
    morphologyEx(thresholded, thresholded, MORPH_CLOSE, kernelX, Point(-1,-1), 3);

    Mat kernelX_small = getStructuringElement(MORPH_RECT, Size(20, 1));
    Mat kernelY_small = getStructuringElement(MORPH_RECT, Size(1, 19));

    dilate(thresholded, thresholded, kernelX_small);
    erode(thresholded, thresholded, kernelX_small); 
    erode(thresholded, thresholded, kernelY_small);
    dilate(thresholded, thresholded, kernelY_small);

    medianBlur(thresholded, thresholded, 15);

    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(thresholded, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat image1 = InputImage.clone();
    drawContours(image1, contours, -1, Scalar(0, 255, 0), 5);
    //imshow("213",image1); 
    vector<Mat> Ret;
    for (int i = 0; i < contours.size(); i++) 
    {
        Rect rect = boundingRect(contours[i]);
        RotatedRect rect_min = minAreaRect(contours[i]);
        double weight = rect.width;
        double height = rect.height;

        if ((weight > (height * 2)) && (weight < (height * 5))) //瞎凑的
        {
            Mat CarLicenceImage = InputImage(rect);
            Ret.emplace_back(CarLicenceImage);
            // imshow("car", car_image);
            // waitKey(0);
            // destroyAllWindows();
        }
    }
    return Ret;
}