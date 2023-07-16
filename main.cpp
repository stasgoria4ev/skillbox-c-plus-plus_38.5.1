#include <QPaintEvent>
#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QTimer>

#include <QMediaPlayer>

class ImageButton : public QPushButton {
Q_OBJECT
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    //bool isDown = false;
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("Стоп");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("..\\red_button_up.png");
    mButtonDownPixmap = QPixmap("..\\red_button_down.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const {
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}

void ImageButton::setDown() {
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(100, 100);
    redButton.move(1000, 400);

    QString filePath = ("..\\Kin-dza-dza.mp3");
    auto *player = new QMediaPlayer(&redButton);

    QObject::connect(&redButton, &QPushButton::clicked, [&filePath, player](){
        std::cout << "clicked\n";
        player->setMedia(QUrl::fromLocalFile(filePath));
        player->setVolume(75);
        player->play();
    });
    redButton.show();
    return QApplication::exec();
}

#include "main.moc"