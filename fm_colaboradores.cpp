#include "fm_colaboradores.h"
#include "ui_fm_colaboradores.h"

#include "global.h"
#include "ColaboradorController.h"
#include "GrupoController.h"
#include <QMessageBox>

fm_colaboradores::fm_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_colaboradores)
{
    ui->setupUi(this);

    fm_colaboradores::inicializa_fm_colaboradores();
}

fm_colaboradores::~fm_colaboradores()
{
    delete ui;
}

/* ***** ***** *****
 *  MY METHODS
 * ***** ***** *****/

void fm_colaboradores::inicializa_fm_colaboradores()
{
    QString nome_email;

    nome_email = "";
    fm_colaboradores::atualiza_table_widget(nome_email);
    fm_colaboradores::carrega_combo_grupos();

    ui->label_selected_row->setVisible(false);
}

void fm_colaboradores::popula_table_widget(QVector<Colaborador> listaColaboradores)
{
    QStringList header;
    Colaborador colaborador;

    header = {"ID", "Nome", "E-mail", "Senha", "Id grupo", "Grupo", "Sigla"};
    global::formatTableWidget(ui->tableWidget_colaboradores, header);

    for (int i = 0; i < listaColaboradores.size(); ++i)
    {
        colaborador = listaColaboradores[i];
        ui->tableWidget_colaboradores->insertRow(i);
        ui->tableWidget_colaboradores->setItem(i, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(i, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(i, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaboradores->setItem(i, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaboradores->setItem(i, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaboradores->setItem(i, 5, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setItem(i, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
        ui->tableWidget_colaboradores->setRowHeight(i, 20);
        ui->tableWidget_colaboradores->setColumnHidden(3, true);
        ui->tableWidget_colaboradores->setColumnHidden(4, true);
    }
}

void fm_colaboradores::atualiza_table_widget(QString nome_email)
{
    QVector<Colaborador> listaColaboradores;
    ColaboradorController colaborador_controller;

    if (global::minCharacters(nome_email, 3))
    {
        listaColaboradores = colaborador_controller.buscaPorNomeEmail(nome_email);
    }
    else
    {
        listaColaboradores = colaborador_controller.buscaTodos();
    }
    fm_colaboradores::popula_table_widget(listaColaboradores);
}

void fm_colaboradores::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->label_selected_row->setText("-1");
    ui->lineEdit_pesquisar->setFocus();
}

void fm_colaboradores::adiciona_colaborador_table_widget(int row, Colaborador colaborador)
{
    ui->tableWidget_colaboradores->insertRow(row);
    ui->tableWidget_colaboradores->setItem(row, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
    ui->tableWidget_colaboradores->setItem(row, 1, new QTableWidgetItem(colaborador.getNome()));
    ui->tableWidget_colaboradores->setItem(row, 2, new QTableWidgetItem(colaborador.getEmail()));
    ui->tableWidget_colaboradores->setItem(row, 3, new QTableWidgetItem(colaborador.getSenha()));
    ui->tableWidget_colaboradores->setItem(row, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
    ui->tableWidget_colaboradores->setItem(row, 5, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
    ui->tableWidget_colaboradores->setItem(row, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
    ui->tableWidget_colaboradores->setRowHeight(row, 20);
}

void fm_colaboradores::altera_colaborador_table_widget(int row, Colaborador colaborador)
{
    ui->tableWidget_colaboradores->item(row, 1)->setText(colaborador.getNome());
    ui->tableWidget_colaboradores->item(row, 2)->setText(colaborador.getEmail());
    ui->tableWidget_colaboradores->item(row, 3)->setText(colaborador.getSenha());
    ui->tableWidget_colaboradores->item(row, 4)->setText(QString::number(colaborador.getGrupo().getId()));
    ui->tableWidget_colaboradores->item(row, 5)->setText(colaborador.getGrupo().getDescricao());
    ui->tableWidget_colaboradores->item(row, 6)->setText(colaborador.getGrupo().getSigla());
}

void fm_colaboradores::carrega_combo_grupos()
{
    QVector<Grupo> listaGrupos;
    GrupoController  grupo_controller;
    Grupo grupo;

    listaGrupos = grupo_controller.buscaTodos();

    ui->comboBox_grupo->addItem("Selecione", 0);

    for (int i = 0; i < listaGrupos.size(); ++i)
    {
        grupo = listaGrupos[i];
        ui->comboBox_grupo->addItem(grupo.getSigla() + "-" + grupo.getDescricao(), grupo.getId());
    }
}

/* ***** ***** *****
 *  SLOTS
 * ***** ***** *****/

void fm_colaboradores::on_pushButton_pesquisar_clicked()
{
    QString nome_email;
    nome_email = ui->lineEdit_pesquisar->text().trimmed();
    if (global::minCharacters(nome_email, 3))
    {
        fm_colaboradores::atualiza_table_widget(nome_email);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
    ui->pushButton_mostrar_todos->setEnabled(true);
    fm_colaboradores::limpa_formulario();
}

void fm_colaboradores::on_pushButton_mostrar_todos_clicked()
{
    QString nome_email;
    nome_email = "";
    fm_colaboradores::atualiza_table_widget(nome_email);
    ui->pushButton_mostrar_todos->setEnabled(false);
    fm_colaboradores::limpa_formulario();
}

void fm_colaboradores::on_tableWidget_colaboradores_itemSelectionChanged()
{
    int row, id, id_grupo, index_grupo;
    QString nome, email, senha;

    row = ui->tableWidget_colaboradores->currentRow();

    id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();
    nome = ui->tableWidget_colaboradores->item(row, 1)->text();
    email = ui->tableWidget_colaboradores->item(row, 2)->text();
    senha = ui->tableWidget_colaboradores->item(row, 3)->text();
    id_grupo = ui->tableWidget_colaboradores->item(row, 4)->text().toInt();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_senha->setText(senha);
    index_grupo = ui->comboBox_grupo->findData(id_grupo);
    ui->comboBox_grupo->setCurrentIndex(index_grupo);

    ui->label_selected_row->setText(QString::number(row));
}

void fm_colaboradores::on_pushButton_salvar_clicked()
{
    int row, id, id_grupo;
    QStringList dados_grupo;
    QString nome, email, senha, descricao, sigla, email_anterior;
    Grupo grupo;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text();
    email = ui->lineEdit_email->text();
    senha = ui->lineEdit_senha->text();
    id_grupo = ui->comboBox_grupo->currentData().toInt();

    if (id_grupo == 0)
    {
        QMessageBox::warning(this, "", "Selecione um grupo.");
        return;
    }

    dados_grupo = ui->comboBox_grupo->currentText().split("-");
    descricao = dados_grupo[1];
    sigla = dados_grupo[0];

    if (!global::minCharacters(nome, 3) || !global::minCharacters(email, 7) || !global::minCharacters(senha, 3))
    {
        QMessageBox::warning(this, "", "Nome e senhs devem ter no mínimo 3 caracteres.\nE-mail deve ter no mínimo 7 caracteres.");
        return;
    }

    grupo.setId(id_grupo);
    grupo.setDescricao(descricao);
    grupo.setSigla(sigla);

    colaborador.setId(id);
    colaborador.setNome(nome);
    colaborador.setEmail(email);
    colaborador.setSenha(senha);
    colaborador.setGrupo(grupo);

    if (row == -1)          // INCLUSÃO
    {
        if (colaborador_controller.buscaEmailDuplicidade(colaborador.getEmail()))
        {
            QMessageBox::warning(this, "", "E-mail já existe.");
            return;
        }
        row = ui->tableWidget_colaboradores->rowCount();
        colaborador = colaborador_controller.insere(colaborador);
        fm_colaboradores::adiciona_colaborador_table_widget(row, colaborador);
        fm_colaboradores::limpa_formulario();
        QMessageBox::warning(this, "", "Cadastrado com sucesso.");
    }
    else                    // ALTERAÇÃO
    {
        email_anterior = ui->tableWidget_colaboradores->item(row, 2)->text();
        if (email_anterior != colaborador.getEmail())
        {
            if (colaborador_controller.buscaEmailDuplicidade(colaborador.getEmail()))
            {
                QMessageBox::warning(this, "", "E-mail já existe.");
                return;
            }
        }

        if (colaborador_controller.altera(colaborador))
        {
            fm_colaboradores::altera_colaborador_table_widget(row, colaborador);
            fm_colaboradores::limpa_formulario();
            QMessageBox::warning(this, "", "Alteradso com sucesso.");
        }
    }
}

void fm_colaboradores::on_pushButton_limpar_clicked()
{
    fm_colaboradores::limpa_formulario();
}

void fm_colaboradores::on_pushButton_fechar_clicked()
{
    close();
}
