#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QRandomGenerator>

class RandomNumberGenerator : public QWidget {
public:
    RandomNumberGenerator(QWidget *parent = nullptr) : QWidget(parent) {
        // Создание кнопки "Сгенерировать число"
        QPushButton *generateButton = new QPushButton("Сгенерировать число", this);

        // Обработка нажатия на кнопку
        connect(generateButton, &QPushButton::clicked, this, &RandomNumberGenerator::generateRandomNumber);

        // Создание метки для отображения случайного числа
        numberLabel = new QLabel(this);
        numberLabel->setAlignment(Qt::AlignCenter);

        // Расположение элементов в горизонтальном слое
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(generateButton);
        layout->addWidget(numberLabel);

        setLayout(layout);
    }

private:
    QLabel *numberLabel;

    void generateRandomNumber() {
        // Генерация случайного числа от 1 до 100
        int randomNumber = QRandomGenerator::global()->bounded(1, 101);
        numberLabel->setText(QString::number(randomNumber));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RandomNumberGenerator randomNumberGenerator;
    randomNumberGenerator.setWindowTitle("Генератор случайных чисел");
    randomNumberGenerator.show();

    return app.exec();
}
