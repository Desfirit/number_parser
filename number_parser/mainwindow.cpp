#include <string>
#include <QString>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "lexer.h"
#include "parser.h"
#include "numconverter.h"
#include <lexem.h>
#include <algorithm>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translate_button_clicked()
{
    auto input = ui->text_input->toPlainText().toStdString();
    QString output;
    try {
        auto lexems (Lexer::read(input));
        output = NumConverter::toRoman((unsigned)Parser::parse(lexems)).c_str();

    }  catch (std::string& err) {
        output = err.c_str();
    }  catch (std::pair<LexemType,LexemType>& lexems){
        const std::map<LexemType,const std::string> converts{
            {UNIT, "1-9"},
            {MGER, "10-19"},
            {TWENTY, "20"},
            {SIXTY, "60"},
            {HUNDRED, "100"},
        };
        output = ("После " + converts.find(lexems.first)->second + " не может идти " + converts.find(lexems.second)->second).c_str();
    }

    ui->text_output->setPlainText(output);
}
