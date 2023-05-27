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

        // Обработка нажатия на кнопку "Сгенерировать число"
        connect(generateButton, &QPushButton::clicked, this, &RandomNumberGenerator::generateRandomNumber);

        // Создание кнопки "Сбросить число"
        QPushButton *resetButton = new QPushButton("Сбросить число", this);

        // Обработка нажатия на кнопку "Сбросить число"
        connect(resetButton, &QPushButton::clicked, this, &RandomNumberGenerator::resetNumber);

        // Создание метки для отображения случайного числа
        numberLabel = new QLabel(this);
        numberLabel->setAlignment(Qt::AlignCenter);

        // Расположение элементов в горизонтальном слое
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(generateButton);
        layout->addWidget(resetButton);
        layout->addWidget(numberLabel);

        setLayout(layout);
    }

private:
    QLabel *numberLabel;
    int randomNumber;

    void generateRandomNumber() {
        // Генерация случайного числа от 1 до 100
        randomNumber = QRandomGenerator::global()->bounded(1, 101);
        numberLabel->setText(QString::number(randomNumber));

        // Проверка четности числа и отображение результата
        if (randomNumber % 2 == 0) {
            numberLabel->setText(numberLabel->text() + " (четное)");
        } else {
            numberLabel->setText(numberLabel->text() + " (нечетное)");
        }

        // Проверка простоты числа и отображение результата
        if (isPrime(randomNumber)) {
            numberLabel->setText(numberLabel->text() + " (простое)");
        } else {
            numberLabel->setText(numberLabel->text() + " (составное)");
        }

        // Вычисление суммы цифр числа и отображение результата
        int digitSum = calculateDigitSum(randomNumber);
        numberLabel->setText(numberLabel->text() + " | Сумма цифр: " + QString::number(digitSum));

        // Вычисление факториала числа и отображение результата
        int factorial = calculateFactorial(randomNumber);
        numberLabel->setText(numberLabel->text() + " | Факториал: " + QString::number(factorial));
    }

    void resetNumber() {
        randomNumber = 0;
        numberLabel->clear();
    }

    bool isPrime(int number) {
        if (number < 2) {
            return false;
        }

        for (int i = 2; i <= number / 2; ++i) {
            if (number % i == 0) {
                return false;
            }
        }

        return true;
    }

    int calculateDigitSum(int number) {
        int sum = 0;
        while (number != 0) {
            sum += number % 10;
            number /= 10;
        }
        return sum;
    }

    int calculateFactorial(int number) {
        int factorial = 1;
        for (int i = 2; i <= number; ++i) {
            factorial *= i;
        }
        return factorial;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RandomNumberGenerator randomNumberGenerator;
    randomNumberGenerator.setWindowTitle("Генератор случайных чисел");
    randomNumberGenerator.show();

    return app.exec();
}
