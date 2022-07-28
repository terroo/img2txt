#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "img2txt.hpp"
#include <memory>
#include <QDebug>
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow {

    Q_OBJECT
    std::shared_ptr<Img2Txt> img2txt;

    void showMessage(const int &);
    void setImage();
    void resetContent();

    enum MSG {
        PATH,
        TEXT,
        PERM,
        SAVE_SUCCESS
    };

    QStringList msg;


public:
    Window(QWidget *parent = nullptr);
    ~Window();
    QString path, text, output;
    QFile file;

private slots:
    void on_actionOpen_image_triggered();

    void on_actionSave_text_triggered();

    void on_actionReset_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
