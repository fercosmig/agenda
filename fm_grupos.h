#ifndef FM_GRUPOS_H
#define FM_GRUPOS_H

#include <QDialog>
#include "Grupo.h"

namespace Ui {
class fm_grupos;
}

class fm_grupos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_grupos(QWidget *parent = nullptr);
    ~fm_grupos();

    //MY METHODS
    void inicializa_fm_grupos();
    void popula_table_widget(QVector<Grupo> listaGrupos);
    void atualiza_table_widget(QString descricao);
    void limpa_formulario();
    void insere_grupo_table_widget(int row, Grupo grupo);
    void altera_grupo_table_widget(int row, Grupo grupo);
    void carrega_combo_siglas();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_grupos_itemSelectionChanged();

    void on_pushButton_salvar_clicked();

private:
    Ui::fm_grupos *ui;
};

#endif // FM_GRUPOS_H
