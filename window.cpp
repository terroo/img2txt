#include "window.hpp"
#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window){

    ui->setupUi(this);

    this->img2txt = std::make_shared<Img2Txt>();
    this->path = this->text = {};
    ui->textEdit->setDisabled(true);
    ui->textEdit->setStyleSheet("font-size: 27px");

    this->msg = {"Failed to get image path.",
                 "Failure. Text is empty.",
                 "Failed to save file.",
                 "File saved successfully!"};

}

Window::~Window(){
    delete ui;
}


void Window::on_actionOpen_image_triggered(){

    ui->textEdit->setText( "Extracting..." );
    ui->label->setText("Loading...");

    this->path = QFileDialog::getOpenFileName( this, "Open Image", QDir::homePath(), "Files *.png ;; Files *.jpg" );
    if( path.isEmpty() ){
        this->showMessage(MSG::PATH);
        this->resetContent();
        return;
    }

    text = QString::fromUtf8(img2txt->get_text( path.toStdString() ).c_str());

    if( text.isEmpty() ){
        showMessage(this->MSG::TEXT);
        return;
    }

    //qDebug() << text;
    this->setImage();
    ui->textEdit->setDisabled(false);
    ui->textEdit->setText( this->text );

}

void Window::showMessage(const int& msg){
    if( msg != MSG::PATH && msg != MSG::SAVE_SUCCESS ){
        QMessageBox::critical(this, this->msg[msg], this->msg[msg]);
    }

    ui->statusbar->showMessage(this->msg[msg], 3000);
}

void Window::setImage(){
    QPixmap currentimage( this->path );
    ui->label->setPixmap( currentimage.scaled(600,600, Qt::KeepAspectRatio) );
}

void Window::resetContent(){
    this->path = this->text = "";
    ui->textEdit->setDisabled(true);
    ui->textEdit->clear();
    ui->label->setText("<h1>No image</h1>");
}


void Window::on_actionSave_text_triggered(){

    if( this->text.isEmpty() ){
        this->showMessage(MSG::TEXT );
        return;
    }

    this->output = QFileDialog::getSaveFileName( this, "Save text", QDir::homePath(), "Files *.txt" );
    this->file.setFileName( output );

    if( !file.open( QFile::WriteOnly | QFile::Text ) ){
        this->showMessage( MSG::PERM );
        return;
    }

    QTextStream out( &this->file );
    out << ui->textEdit->toPlainText();
    this->file.flush();
    this->file.close();
    this->showMessage(MSG::SAVE_SUCCESS);


}


void Window::on_actionReset_triggered(){
    this->resetContent();
}


void Window::on_actionQuit_triggered(){
    close();
}

void Window::on_actionAbout_triggered(){
    QMessageBox::information(this, "About Img2Txt", ""
                                   "<h2>Img2Txt 1.0</h2>"
                                   "<p>Developed by Marcos Oliveira<br>Copyright 2022 Terminal Root Sistemas Inc.</p>"
                                   "<p><a style='color:#17a2b8;font-weight:bold;' href='https://terminalroot.com.br/'>"
                                   "terminalroot.com.br</a></p><hr>"
                                   "<p><i>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE "
                                   "WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.</i></p><br>");

}

