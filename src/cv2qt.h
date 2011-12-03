#ifndef CV2QT_H
#define CV2QT_H

#include <QtGui>
#include <ctype.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace cv2qt
{

IplImage *QImageToIplImage(const QImage * qImage);
QImage IplImageToQImage(const IplImage  *iplImage, uchar **data , bool mirroRimage = false);

}
#endif
