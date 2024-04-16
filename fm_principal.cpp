#include "fm_principal.h"
#include "ui_fm_principal.h"

#include "global.h"
#include "ContatoController.h"
#include "fm_autenticacao.h"
#include <QMessageBox>
#include "fm_grupos.h"
#include "fm_colaboradores.h"

fm_principal::fm_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::fm_principal)
{
    ui->setupUi(this);

    fm_principal::inicializa_fm_principal();
}

fm_principal::~fm_principal()
{
    delete ui;
}

/* ***** ***** *****
 * MY METHODS
 * ***** ***** *****/

void fm_principal::inicializa_fm_principal()
{
    QString nome_email;


    global::initializeGlobalVariables();

    fm_principal::iconLocked.addFile(":/ico/images/lock.png");
    fm_principal::iconUnlocked.addFile(":/ico/images/unlock.png");

    ui->label_versao->setText("Versão: " + global::version);

    global::isLogged = false;
    fm_principal::configura_autenticacao();

    nome_email = "";
    fm_principal::atualiza_table_widget(nome_email);

    ui->label_selected_row->setVisible(false);
}

void fm_principal::configura_autenticacao()
{
    QString strLabel;

    ui->pushButton_autenticacao->setText("");

    if (global::isLogged)
    {
        ui->pushButton_autenticacao->setIcon(fm_principal::iconUnlocked);
        strLabel = global::colaboradorLogado.getGrupo().getSigla();
        strLabel += " | ";
        strLabel += global::colaboradorLogado.getNome();
    }
    else
    {
        ui->pushButton_autenticacao->setIcon(fm_principal::iconLocked);
        strLabel = "Autentique-se!";
    }

    fm_principal::tela_lock_unlock(global::isLogged);

    ui->label_colaborador_logado->setText(strLabel);

    ui->statusbar->addWidget(ui->pushButton_autenticacao);
    ui->statusbar->addWidget(ui->label_colaborador_logado);
}

void fm_principal::tela_lock_unlock(bool isLogged)
{
    ui->lineEdit_pesquisar->setEnabled(isLogged);
    ui->pushButton_pesquisar->setEnabled(isLogged);
    ui->tableWidget_contatos->setEnabled(isLogged);
    ui->lineEdit_nome->setEnabled(isLogged);
    ui->lineEdit_email->setEnabled(isLogged);
    ui->lineEdit_telefone->setEnabled(isLogged);
    ui->pushButton_salvar->setEnabled(isLogged);
    ui->pushButton_limpar->setEnabled(isLogged);
}

void fm_principal::popula_table_widget(QVector<Contato> listaContatos)
{
    QStringList header;
    Contato contato;

    header = {"ID", "Nome", "E-mail", "Telefone"};
    global::formatTableWidget(ui->tableWidget_contatos, header);

    for (int i = 0; i < listaContatos.size(); ++i)
    {
        contato = listaContatos[i];
        ui->tableWidget_contatos->insertRow(i);
        ui->tableWidget_contatos->setItem(i, 0, new QTableWidgetItem(QString::number(contato.getId())));
        ui->tableWidget_contatos->setItem(i, 1, new QTableWidgetItem(contato.getNome()));
        ui->tableWidget_contatos->setItem(i, 2, new QTableWidgetItem(contato.getEmail()));
        ui->tableWidget_contatos->setItem(i, 3, new QTableWidgetItem(contato.getTelefone()));
        ui->tableWidget_contatos->setRowHeight(i, 20);
    }
}

void fm_principal::atualiza_table_widget(QString nome_email)
{
    QVector<Contato> listaContatos;
    ContatoController contato_controller;

    if (global::minCharacters(nome_email, 3))
    {
        listaContatos = contato_controller.buscaPorNomeEmail(nome_email);
    }
    else
    {
        listaContatos = contato_controller.buscaTodos();
    }
    fm_principal::popula_table_widget(listaContatos);
}

void fm_principal::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_telefone->clear();
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
}

void fm_principal::insere_contato_table_widget(int row, Contato contato)
{
    ui->tableWidget_contatos->insertRow(row);
    ui->tableWidget_contatos->setItem(row, 0, new QTableWidgetItem(QString::number(contato.getId())));
    ui->tableWidget_contatos->setItem(row, 1, new QTableWidgetItem(contato.getNome()));
    ui->tableWidget_contatos->setItem(row, 2, new QTableWidgetItem(contato.getEmail()));
    ui->tableWidget_contatos->setItem(row, 3, new QTableWidgetItem(contato.getTelefone()));
    ui->tableWidget_contatos->setRowHeight(row, 20);
}

void fm_principal::altera_contato_table_widget(int row, Contato contato)
{
    ui->tableWidget_contatos->item(row, 1)->setText(contato.getNome());
    ui->tableWidget_contatos->item(row, 2)->setText(contato.getEmail());
    ui->tableWidget_contatos->item(row, 3)->setText(contato.getTelefone());
}

/* ***** ***** *****
 * SLOTS
 * ***** ***** *****/

void fm_principal::on_pushButton_autenticacao_clicked()
{
    fm_autenticacao f_autenticacao;

    if (global::isLogged)
    {
        global::isLogged = false;
    }
    else
    {
        f_autenticacao.exec();
    }
    fm_principal::configura_autenticacao();
}

void fm_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}

void fm_principal::on_actionSobre_triggered()
{
    QString informacoes;
    informacoes = "Agenda de contatos\n\n";
    informacoes += "Desenvolvido por Fernando Costa Migliorini\n\n";
    informacoes += "entre 04/04/2024 e 07/04/2024.\n\n";
    informacoes +="Desenvolvido em C++ (QtCreator) & SQLITE\n\n";
    informacoes +="Versão: " + global::version;
    QMessageBox::information(this, "Controle de EStoque", informacoes);
}

void fm_principal::on_actionSair_triggered()
{
    QApplication::quit();
}

void fm_principal::on_pushButton_limpar_clicked()
{
    fm_principal::limpa_formulario();
}

void fm_principal::on_pushButton_pesquisar_clicked()
{
    QString nome_email;

    nome_email = ui->lineEdit_pesquisar->text();

    if (global::minCharacters(nome_email, 3))
    {
        fm_principal::atualiza_table_widget(nome_email);
        fm_principal::limpa_formulario();
        ui->pushButton_mostrar_todos->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
    }
}

void fm_principal::on_tableWidget_contatos_itemSelectionChanged()
{
    fm_principal::limpa_formulario();
    int row, id;
    QString nome, email, telefone;

    row = ui->tableWidget_contatos->currentRow();
    id = ui->tableWidget_contatos->item(row, 0)->text().toInt();
    nome = ui->tableWidget_contatos->item(row, 1)->text();
    email = ui->tableWidget_contatos->item(row, 2)->text();
    telefone = ui->tableWidget_contatos->item(row, 3)->text();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_telefone->setText(telefone);
    ui->label_selected_row->setText(QString::number(row));
}

void fm_principal::on_pushButton_salvar_clicked()
{
    int row, id;
    QString nome, email, telefone;
    Contato contato;
    ContatoController contato_controller;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    email = ui->lineEdit_email->text().trimmed();
    telefone = ui->lineEdit_telefone->text().trimmed();

    contato.setId(id);
    contato.setNome(nome);
    contato.setEmail(email);
    contato.setTelefone(telefone);

    if (global::minCharacters(nome, 3) && global::minCharacters(email, 7) && global::minCharacters(telefone, 8))
    {
        if (row == -1)          // INCLUSÃO
        {
            row = ui->tableWidget_contatos->rowCount();
            contato = contato_controller.insere(contato);
            fm_principal::insere_contato_table_widget(row, contato);
            fm_principal::limpa_formulario();
        }
        else                  // ALTERAÇÃO
        {
            resposta = QMessageBox::question(this, "ALTERAÇÂO DE CONTATO", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);
            if (resposta == QMessageBox::Yes)
            {
                if (contato_controller.altera(contato))
                {
                    fm_principal::altera_contato_table_widget(row, contato);
                    QMessageBox::information(this, "", "Alterado com sucesso.");
                    fm_principal::limpa_formulario();
                }
                else
                {
                    QMessageBox::warning(this, "", "Erro ao tentar alterar.");
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Nome deve ter no mínimo 3 caracteres.\nE-mail deve ter no mínimo 7 caracteres.\nTelefone deve ter no mínimo 8 caracteres.");
    }
}

void fm_principal::on_pushButton_mostrar_todos_clicked()
{
    QString nome_email;

    nome_email = "";
    fm_principal::atualiza_table_widget(nome_email);
    fm_principal::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}


void fm_principal::on_actionGrupos_triggered()
{
    fm_grupos f_grupos;

    if (global::isLogged)
    {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
        {
            f_grupos.exec();
        }
        else
        {
            QMessageBox::warning(this, "", "Sem permissão!");
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}


void fm_principal::on_actionColaboradores_triggered()
{
    fm_colaboradores f_colaboradores;

    if (global::isLogged)
    {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
        {
            f_colaboradores.exec();
        }
        else
        {
            QMessageBox::warning(this, "", "Sem permissão!");
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Autentique-se!");
    }
}

