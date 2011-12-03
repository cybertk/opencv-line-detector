#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QtGui>
#include "regiongrabber.h"

#define SAVE_FILE_FORMAT "PNG"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QSpinBox;
class QVBoxLayout;
QT_END_NAMESPACE

class Screenshot : public QWidget
{
        Q_OBJECT

public:
        Screenshot();
        void updateImageLabel();

protected:
//        void resizeEvent(QResizeEvent *event);

private slots:
        void openImage();
        void saveImage();
        void captureScreenshot();
        void dumpFullScreen();
        void dumpPartialScreen();
        void zoomImage(int scaleFator);
        void changeBrightness(int brightness);
        void changeContrast(int contrast);
        void changeGamma(int gamma);
        void slotRegionGrabbed(const QPixmap &pix);
        void lineDetect();

private:
        int scaleFator;
        bool lineDetected;

        void createGroupBoxesLayout();
        void createButtonsLayout();
        void createParameterLayout();

        QPushButton *createButton(const QString &text, QWidget *receiver,
                              const char *member);
        void updatePreview();

        QPixmap originalPixmap;
        QPixmap currentPixmap;
        QPixmap detectingPixmap;
        RegionGrabber *rgnGrab;

        QLabel *imageLabel;
        QScrollArea *imageScrollArea;
        QPushButton *newScreenshotButton;
        QPushButton *saveScreenshotButton;
        QPushButton *captureScreenButton;
        QPushButton *detectLineButton;
        QPushButton *zoomInButton;
        QPushButton *zoomOutButton;
        QPushButton *increaseBrightnessButton;
        QPushButton *decreaseBrightnessButton;

        QSpinBox *zoomSpinBox;
        QSpinBox *brightnessSpinBox;
        QSpinBox *contrastSpinBox;
        QSpinBox *gammaSpinBox;

        QSpinBox *rhoSpinBox;
        QSpinBox *thetaSpinBox;
        QSpinBox *thresholdSpinBox;
        QSpinBox *minLineLengthSpinBox;
        QSpinBox *maxGapSpinBox;

        QGroupBox *zoomGroupBox;
        QGroupBox *brightnessGroupBox;
        QGroupBox *contrastGroupBox;
        QGroupBox *gammaGroupBox;

        QGroupBox *rhoGroupBox;
        QGroupBox *thetaGroupBox;
        QGroupBox *thresholdGroupBox;
        QGroupBox *minLineLengthGroupBox;
        QGroupBox *maxGapGroupBox;

        QHBoxLayout *mainLayout;
        QHBoxLayout *parameterLayout;
        QVBoxLayout *detectLayout;
        QVBoxLayout *buttonsLayout;
        QVBoxLayout *GroupBoxesLayoutLayout;
};

#endif
