#ifndef LINEDETECTOR_H
#define LINEDETECTOR_H

#include <opencv/cv.h>

class QPixmap;

namespace lineDetector
{
        QPixmap lineDetect(QPixmap* q, int rho = 1, 
                        int theta = CV_PI/180, int threshold = 30, 
                        int min_length = 2, int max_gap = 30);
}

#endif
