#include <QtGui>
#include "screenshot.h"
#include "changeImage.h"
#include "lineDetector.h"

Screenshot::Screenshot()
{
        imageLabel = new QLabel;
        imageLabel->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Expanding);
        imageLabel->setAlignment(Qt::AlignCenter);

        imageScrollArea = new QScrollArea;
        imageScrollArea->setWidget(imageLabel);
        imageScrollArea->setMinimumSize(320,240);

        createButtonsLayout();

        createGroupBoxesLayout();

        createParameterLayout();

        buttonsLayout->addLayout(GroupBoxesLayoutLayout);

        detectLayout = new QVBoxLayout;
        detectLayout->addLayout(parameterLayout);
        detectLayout->addWidget(imageScrollArea);

        mainLayout = new QHBoxLayout;
        mainLayout->addLayout(buttonsLayout);
        mainLayout->addLayout(detectLayout);
        setLayout(mainLayout);

        zoomSpinBox->setValue(100);
        brightnessSpinBox->setValue(0);
        contrastSpinBox->setValue(100);
        gammaSpinBox->setValue(0);

        rhoSpinBox->setValue(1);
        thetaSpinBox->setValue(180);
        thresholdSpinBox->setValue(50);
        minLineLengthSpinBox->setValue(50);
        maxGapSpinBox->setValue(10);

        setWindowTitle(tr("Line detecting via Hough Transform Demo"));

        lineDetected = false;
        scaleFator = 100;
        dumpFullScreen();
        updatePreview();
}

void Screenshot::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image")
            , ".", tr("Image files(*.png *.jpg *.jpeg)"));

    if (!fileName.isEmpty()) {
        currentPixmap = QPixmap(fileName);
        originalPixmap = currentPixmap;
        scaleFator = 100;
        lineDetected = false;
        updatePreview();
    }
}

void Screenshot::captureScreenshot()
{
        hide();
        QTimer::singleShot(500, this, SLOT(dumpPartialScreen()));
}

//! [2]

//! [3]
void Screenshot::saveImage()
{
        QString format = SAVE_FILE_FORMAT;
        QString savePath = QFileDialog::getSaveFileName(this, tr("Save Image")
                , ".", tr("Images(*.png *.jpg)"));

        currentPixmap.save(savePath, format.toAscii());
}
//! [3]

void Screenshot::dumpPartialScreen()
{
            rgnGrab = new RegionGrabber();
            connect( rgnGrab, SIGNAL( regionGrabbed( const QPixmap & ) ),
                     SLOT( slotRegionGrabbed( const QPixmap & ) ) );
}

void Screenshot::dumpFullScreen()
{
        QDesktopWidget *desktop = QApplication::desktop();
        originalPixmap = QPixmap();
        originalPixmap = QPixmap::grabWindow(desktop->winId(), 0, 0,
                                             desktop->width(), desktop->height());
        currentPixmap = originalPixmap;
}

void Screenshot::lineDetect()
{
    if (!lineDetected)
        detectingPixmap = currentPixmap;
//    originalPixmap = currentPixmap;
        currentPixmap = lineDetector::lineDetect(&detectingPixmap,
                rhoSpinBox->value(),
                thetaSpinBox->value(),
                thresholdSpinBox->value(),
                minLineLengthSpinBox->value(),
                maxGapSpinBox->value());

        lineDetected = true;
        updatePreview();
}

//! [8]
void Screenshot::createButtonsLayout()
{
    newScreenshotButton = createButton(tr("Open"),
                                        this, SLOT(openImage()));
    saveScreenshotButton = createButton(tr("Save"),
                                        this, SLOT(saveImage()));
    captureScreenButton = createButton(tr("Capture"),
                                        this, SLOT(captureScreenshot()));
    detectLineButton = createButton(tr("Detect"),
                                        this, SLOT(lineDetect()));

    buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(newScreenshotButton);
    buttonsLayout->addWidget(saveScreenshotButton);
    buttonsLayout->addWidget(captureScreenButton);
    buttonsLayout->addWidget(detectLineButton);
}
//! [8]

void Screenshot::createGroupBoxesLayout()
{
    zoomGroupBox = new QGroupBox(tr("Zoom"));
    zoomSpinBox = new QSpinBox;
    zoomSpinBox->setSuffix(tr(" %"));
    zoomSpinBox->setMaximum(400);
    connect(zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomImage(int)));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(zoomSpinBox);
    zoomGroupBox->setLayout(layout);

    brightnessGroupBox = new QGroupBox(tr("Brightness"));
    brightnessSpinBox = new QSpinBox;
    brightnessSpinBox->setMaximum(100);
    connect(brightnessSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeBrightness(int)));
    layout = new QHBoxLayout();
    layout->addWidget(brightnessSpinBox);
    brightnessGroupBox->setLayout(layout);

    contrastGroupBox = new QGroupBox(tr("contrast"));
    contrastSpinBox = new QSpinBox;
    contrastSpinBox->setMaximum(100);
    connect(contrastSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
    layout = new QHBoxLayout();
    layout->addWidget(contrastSpinBox);
    contrastGroupBox->setLayout(layout);

    gammaGroupBox = new QGroupBox(tr("Gamma"));
    gammaSpinBox = new QSpinBox;
    gammaSpinBox->setMaximum(100);
    connect(gammaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));
    layout = new QHBoxLayout();
    layout->addWidget(gammaSpinBox);
    gammaGroupBox->setLayout(layout);

    GroupBoxesLayoutLayout = new QVBoxLayout;
    GroupBoxesLayoutLayout->addWidget(zoomGroupBox);
    GroupBoxesLayoutLayout->addWidget(brightnessGroupBox);
    GroupBoxesLayoutLayout->addWidget(contrastGroupBox);
    GroupBoxesLayoutLayout->addWidget(gammaGroupBox);
}

void Screenshot::createParameterLayout()
{
    rhoGroupBox = new QGroupBox(tr("Distance Resolution"));
    rhoSpinBox = new QSpinBox;
    rhoSpinBox->setSuffix(tr(" pixel"));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(rhoSpinBox);
    rhoGroupBox->setLayout(layout);

    thetaGroupBox = new QGroupBox(tr("Angel Resolution"));
    thetaSpinBox = new QSpinBox;
    thetaSpinBox->setSuffix(tr(" radian"));
    thetaSpinBox->setMaximum(360);
    layout = new QHBoxLayout();
    layout->addWidget(thetaSpinBox);
    thetaGroupBox->setLayout(layout);


    thresholdGroupBox = new QGroupBox(tr("Threshold"));
    thresholdSpinBox = new QSpinBox;
    thresholdSpinBox->setMaximum(400);
    layout = new QHBoxLayout();
    layout->addWidget(thresholdSpinBox);
    thresholdGroupBox->setLayout(layout);

    minLineLengthGroupBox = new QGroupBox(tr("Minimum Line Length"));
    minLineLengthSpinBox = new QSpinBox;
    minLineLengthSpinBox->setSuffix(tr(" pixel"));
    layout = new QHBoxLayout();
    layout->addWidget(minLineLengthSpinBox);
    minLineLengthGroupBox->setLayout(layout);

    maxGapGroupBox = new QGroupBox(tr("Max Gap"));
    maxGapSpinBox = new QSpinBox;
    maxGapSpinBox->setSuffix(tr(" pixel"));
    layout = new QHBoxLayout();
    layout->addWidget(maxGapSpinBox);
    maxGapGroupBox->setLayout(layout);

    parameterLayout = new QHBoxLayout;
    parameterLayout->addWidget(rhoGroupBox);
    parameterLayout->addWidget(thetaGroupBox);
    parameterLayout->addWidget(thresholdGroupBox);
    parameterLayout->addWidget(minLineLengthGroupBox);
    parameterLayout->addWidget(maxGapGroupBox);
}


QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
        QPushButton *button = new QPushButton(text);
        button->connect(button, SIGNAL(clicked()), receiver, member);
        return button;
}

void Screenshot::slotRegionGrabbed( const QPixmap &pix )
{
        if (!pix.isNull()) {
                originalPixmap = pix;
                currentPixmap = pix;
        }
        updatePreview();
        show();
        delete rgnGrab;
}

void Screenshot::updatePreview()
{
        QSize imageSize = originalPixmap.size() * scaleFator / 100;
        imageLabel->resize(imageSize);
        imageLabel->setPixmap(currentPixmap.scaled(imageSize,
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));
}

void Screenshot::zoomImage(int scaleFator)
{
        this->scaleFator = scaleFator;
        updatePreview();
}


void Screenshot::changeBrightness(int brightness)
{
        lineDetected = false;
        currentPixmap = transmationImage::changeBrightness(originalPixmap, brightness);
        updatePreview();
}

void Screenshot::changeContrast(int contrast)
{
        lineDetected = false;
        currentPixmap = transmationImage::changeContrast(originalPixmap, contrast);
        updatePreview();
}

void Screenshot::changeGamma(int gamma)
{
        lineDetected = false;
        currentPixmap = transmationImage::changeGamma(originalPixmap, gamma);
        updatePreview();
}
