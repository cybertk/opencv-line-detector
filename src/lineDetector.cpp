#include <QImage>
#include <QPixmap>
#include <opencv/cv.h>
#include "lineDetector.h"
#include "cv2qt.h"

namespace lineDetector
{

QPixmap lineDetect(QPixmap* srcPixmap, int rho, 
    int theta, int threshold, int min_length, int max_gap)
{
    IplImage* src = cv2qt::QImageToIplImage(&(srcPixmap->toImage()));
    IplImage* dst = cvCreateImage(cvGetSize(src), 8, 1 );
    IplImage* color_dst = cvCreateImage(cvGetSize(src), 8, 3 );
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* lines = 0;

    int i;
    cvCanny(src, dst, 50, 200, 3);
    cvCvtColor(dst, color_dst, CV_GRAY2BGR);
    lines = cvHoughLines2(dst, storage, CV_HOUGH_PROBABILISTIC,
                    rho, CV_PI/theta, threshold, min_length, max_gap);
//lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 50, 50, 10 );
    for(i = 0; i < lines->total; i++)
    {
        CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
        cvLine(color_dst, line[0], line[1], CV_RGB(255, 0, 0), 3, 8 );
    }
    uchar **data = (uchar **)malloc(1024 * 768 * 4);

    return QPixmap::fromImage(cv2qt::IplImageToQImage(color_dst, data));

}

}
