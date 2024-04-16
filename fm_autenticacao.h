#ifndef FM_AUTENTICACAO_H
#define FM_AUTENTICACAO_H

#include <QDialog>

namespace Ui {
class fm_autenticacao;
}

class fm_autenticacao : public QDialog
{
    Q_OBJECT

public:
    explicit fm_autenticacao(QWidget *parent = nullptr);
    ~fm_autenticacao();

    // MY VARIABLES & OBJECTS
    QIcon fechado, aberto;
    bool isOpened;

    // MY METHODS
    void inicializa_fm_autenticacao();
    void limpa_formulario();

private slots:
    void on_pushButton_view_password_clicked();

    void on_pushButton_cancelar_clicked();

    void on_pushButton_autenticar_clicked();

private:
    Ui::fm_autenticacao *ui;
};

#endif // FM_AUTENTICACAO_H
