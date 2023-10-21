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