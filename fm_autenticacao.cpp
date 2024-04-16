#include "fm_autenticacao.h"
#include "ui_fm_autenticacao.h"

#include "global.h"
#include <QMessageBox>
#include "ColaboradorController.h"

fm_autenticacao::fm_autenticacao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_autenticacao)
{
    ui->setupUi(this);

    fm_autenticacao::inicializa_fm_autenticacao();
}

fm_autenticacao::~fm_autenticacao()
{
    delete ui;
}

/* ***** ***** *****
 * MY METHODS
 * ***** ***** *****/

void fm_autenticacao::inicializa_fm_autenticacao()
{
    fm_autenticacao::fechado.addFile(":/ico/images/hide.png");
    fm_autenticacao::aberto.addFile(":/ico/images/show.png");

    ui->pushButton_view_password->setText("");
    ui->pushButton_view_password->setIcon(fm_autenticacao::aberto);
    fm_autenticacao::isOpened = false;

    ui->lineEdit_email->setFocus();
}

void fm_autenticacao::limpa_formulario()
{
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->lineEdit_email->setFocus();
}

/* ***** ***** *****
 * SLOTS
 * ***** ***** *****/

void fm_autenticacao::on_pushButton_view_password_clicked()
{
    if (fm_autenticacao::isOpened)
    {
        fm_autenticacao::isOpened = false;
        ui->pushButton_view_password->setIcon(fm_autenticacao::aberto);
        ui->lineEdit_senha->setEchoMode(QLineEdit::Password);
    }
    else
    {
        fm_autenticacao::isOpened = true;
        ui->pushButton_view_password->setIcon(fm_autenticacao::fechado);
        ui->lineEdit_senha->setEchoMode(QLineEdit::Normal);
    }
}

void fm_autenticacao::on_pushButton_cancelar_clicked()
{
    close();
}

void fm_autenticacao::on_pushButton_autenticar_clicked()
{
    QString email, senha;
    ColaboradorController colaborador_controller;

    email = ui->lineEdit_email->text();
    senha = ui->lineEdit_senha->text();

    if (global::minCharacters(email, 7) && global::minCharacters(senha, 3))
    {
        global::colaboradorLogado = colaborador_controller.autentica(email, senha);
        if (global::colaboradorLogado.getId() > 0)
        {
            global::isLogged = true;
            close();
        }
        else
        {
            QMessageBox::warning(this, "", "E-mail e/ou senha inválidos");
            fm_autenticacao::limpa_formulario();
        }
    }
    else
    {
        QMessageBox::warning(this, "", "E-mail deve ter no mínimo 7 caracteres.\nSenha deve ter no mínimo 3 caracteres.");
    }
}
