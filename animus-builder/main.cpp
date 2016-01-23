#include <QCoreApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    qDebug() << "Hello World!\n" << endl;
    QCoreApplication a(argc, argv);

    return a.exec();
}
