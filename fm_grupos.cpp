#include "fm_grupos.h"
#include "ui_fm_grupos.h"

#include "GrupoController.h"
#include <QMessageBox>

fm_grupos::fm_grupos(QWidget *parent) : QDialog(parent), ui(new Ui::fm_grupos)
{
    ui->setupUi(this);

    fm_grupos::inicializa_fm_grupos();
}

fm_grupos::~fm_grupos()
{
    delete ui;
}

/* ***** ***** *****
 * MY METHODS
 * ***** ***** *****/

void fm_grupos::inicializa_fm_grupos()
{
    QString descricao;

    descricao = "";
    fm_grupos::atualiza_table_widget(descricao);
    fm_grupos::carrega_combo_siglas();

    ui->label_selected_row->setVisible(false);
}

void fm_grupos::popula_table_widget(QVector<Grupo> listaGrupos)
{
    QStringList header;
    Grupo grupo;

    header = {"ID", "Descricao", "Sigla"};
    global::formatTableWidget(ui->tableWidget_grupos, header);

    for (int i = 0; i < listaGrupos.size(); ++i)
    {
        grupo = listaGrupos[i];
        ui->tableWidget_grupos->insertRow(i);
        ui->tableWidget_grupos->setItem(i, 0, new QTableWidgetItem(QString::number(grupo.getId())));
        ui->tableWidget_grupos->setItem(i, 1, new QTableWidgetItem(grupo.getDescricao()));
        ui->tableWidget_grupos->setItem(i, 2, new QTableWidgetItem(grupo.getSigla()));
        ui->tableWidget_grupos->setRowHeight(i, 20);
    }
}

void fm_grupos::atualiza_table_widget(QString descricao)
{
    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;

    if (global::minCharacters(descricao, 3))
    {
        listaGrupos = grupo_controller.buscaPorDescricao(descricao);
    }
    else
    {
        listaGrupos = grupo_controller.buscaTodos();
    }
    fm_grupos::popula_table_widget(listaGrupos);
}

void fm_grupos::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_descricao->clear();
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
    ui->comboBox_sigla->setCurrentIndex(0);
}

void fm_grupos::insere_grupo_table_widget(int row, Grupo grupo)
{
    ui->tableWidget_grupos->insertRow(row);
    ui->tableWidget_grupos->setItem(row, 0, new QTableWidgetItem(QString::number(grupo.getId())));
    ui->tableWidget_grupos->setItem(row, 1, new QTableWidgetItem(grupo.getDescricao()));
    ui->tableWidget_grupos->setItem(row, 2, new QTableWidgetItem(grupo.getSigla()));
    ui->tableWidget_grupos->setRowHeight(row, 20);
}

void fm_grupos::altera_grupo_table_widget(int row, Grupo grupo)
{
    ui->tableWidget_grupos->item(row, 1)->setText(grupo.getDescricao());
    ui->tableWidget_grupos->item(row, 2)->setText(grupo.getSigla());
}

void fm_grupos::carrega_combo_siglas()
{
    QStringList siglas;

    siglas = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "W", "V", "X", "Y", "Z"};

    ui->comboBox_sigla->addItem("Selecione", 0);

    for (int i = 0; i < siglas.size(); ++i)
    {
        ui->comboBox_sigla->addItem(siglas[i], i + 1);
    }
}

/* ***** ***** *****
 * SLOTS
 * ***** ***** *****/

void fm_grupos::on_pushButton_fechar_clicked()
{
    close();
}

void fm_grupos::on_pushButton_limpar_clicked()
{
    fm_grupos::limpa_formulario();
}

void fm_grupos::on_pushButton_pesquisar_clicked()
{
    QString descricao;

    descricao = ui->lineEdit_pesquisar->text().trimmed();
    if (global::minCharacters(descricao, 3))
    {
        fm_grupos::atualiza_table_widget(descricao);
        fm_grupos::limpa_formulario();
        ui->pushButton_mostrar_todos->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void fm_grupos::on_pushButton_mostrar_todos_clicked()
{
    QString descricao;
    descricao = "";
    fm_grupos::atualiza_table_widget(descricao);
    fm_grupos::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_grupos::on_tableWidget_grupos_itemSelectionChanged()
{
    int row, id, index_sigla;
    QString descricao, sigla;

    row = ui->tableWidget_grupos->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_grupos->item(row, 0)->text().toInt();
    descricao = ui->tableWidget_grupos->item(row, 1)->text();
    sigla = ui->tableWidget_grupos->item(row, 2)->text();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_descricao->setText(descricao);
    index_sigla = ui->comboBox_sigla->findText(sigla);
    ui->comboBox_sigla->setCurrentIndex(index_sigla);
}

void fm_grupos::on_pushButton_salvar_clicked()
{
    int row, id, data_sigla;
    QString descricao, sigla, descricao_db, sigla_db;
    Grupo grupo;
    GrupoController grupo_controller;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    descricao = ui->lineEdit_descricao->text().trimmed();
    sigla = ui->comboBox_sigla->currentText();
    data_sigla = ui->comboBox_sigla->currentData().toInt();

    if (data_sigla == 0)
    {
        QMessageBox::warning(this, "", "Selecione um grupo");
        return;
    }

    if (!global::minCharacters(descricao, 3))
    {
        QMessageBox::warning(this, "", "Descricao deve ter no mínimo 3 caracteres.");
        return;
    }

    grupo.setId(id);
    grupo.setDescricao(descricao);
    grupo.setSigla(sigla);

    if (row == -1)          // INCLUSÃO
    {
        if (grupo_controller.buscaDescricaoDuplicada(grupo.getDescricao()))
        {
            QMessageBox::warning(this, "", "Descrição já existe!");
            return;
        }

        if (grupo_controller.buscaSiglaDuplicada(grupo.getSigla()))
        {
            QMessageBox::warning(this, "", "Sigla já existe!");
            return;
        }

        grupo = grupo_controller.insere(grupo);
        row = ui->tableWidget_grupos->rowCount();
        fm_grupos::insere_grupo_table_widget(row, grupo);
        fm_grupos::limpa_formulario();
        QMessageBox::information(this, "", "Cadastrado com sucesso!");
    }
    else                    // ALTERAÇÃO
    {
        descricao_db = ui->tableWidget_grupos->item(row, 1)->text();
        sigla_db = ui->tableWidget_grupos->item(row, 2)->text();

        if (descricao_db != grupo.getDescricao())
        {
            if (grupo_controller.buscaDescricaoDuplicada(grupo.getDescricao()))
            {
                QMessageBox::warning(this, "", "Descrição já existe!");
                return;
            }
        }

        if (sigla_db != grupo.getSigla())
        {
            if (grupo_controller.buscaSiglaDuplicada(grupo.getSigla()))
            {
                QMessageBox::warning(this, "", "Sigla já existe!");
                return;
            }
        }

        if (grupo_controller.altera(grupo))
        {
            fm_grupos::altera_grupo_table_widget(row, grupo);
            fm_grupos::limpa_formulario();
            QMessageBox::information(this, "", "Alterado com sucesso!");
        }
    }
}
