#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>

#include "Contato.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class fm_principal;
}
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();

    // MY VARIABLES
    QIcon iconLocked, iconUnlocked;

    // MY METHODS
    void inicializa_fm_principal();
    void configura_autenticacao();
    void tela_lock_unlock(bool isLogged);
    void popula_table_widget(QVector<Contato> listaContatos);
    void atualiza_table_widget(QString nome_email);
    void limpa_formulario();
    void insere_contato_table_widget(int row, Contato contato);
    void altera_contato_table_widget(int row, Contato contato);

private slots:
    void on_pushButton_autenticacao_clicked();

    void on_pushButton_fechar_clicked();

    void on_actionSobre_triggered();

    void on_actionSair_triggered();

    void on_pushButton_limpar_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_tableWidget_contatos_itemSelectionChanged();

    void on_pushButton_salvar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_actionGrupos_triggered();

    void on_actionColaboradores_triggered();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
