#ifndef CONTATOCONTROLLER_H
#define CONTATOCONTROLLER_H

#include "Conexao.h"
#include "Contato.h"

class ContatoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;
protected:
public:
    // CONSTRUCTOR
    ContatoController() {}

    // METHODS
    Contato insere(Contato contato);
    QVector<Contato> buscaTodos();
    QVector<Contato> buscaPorNomeEmail(QString nome_email);
    bool altera(Contato contato);
};

inline Contato ContatoController::insere(Contato contato)
{
    sql = "INSERT INTO tb_contatos ";
    sql += "( nome, email, telefone ) ";
    sql += "VALUES ";
    sql += "( :nome, :email, :telefone )";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");
        query.prepare(sql);
        query.bindValue(":nome", contato.getNome());
        query.bindValue(":email", contato.getEmail());
        query.bindValue(":telefone", contato.getTelefone());
        if (query.exec())
        {
            sql = "SELECT id FROM tb_contatos ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    contato.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "ContatoController::insere() query.exec(SELECT): " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "ContatoController::insere() query.exec(INSERT): " << query.lastError().text();
        }
        query.exec("COMMIT");
    }
    conn.close();
    return contato;
}

inline QVector<Contato> ContatoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "id, nome, email, telefone ";
    sql += "FROM ";
    sql += "tb_contatos ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    QVector<Contato> listaContatos;
    Contato contato;

    if (conn.isOpen())
    {
        query.prepare(sql);
        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    contato.setId(query.record().value("id").toInt());
                    contato.setNome(query.record().value("nome").toString());
                    contato.setEmail(query.record().value("email").toString());
                    contato.setTelefone(query.record().value("telefone").toString());
                    listaContatos.push_back(contato);
                }
                while (query.next());
            }
            else
            {
                qDebug() << "ContatoController::buscaTodos() query.next() Não retornou registros";
            }
        }
        else
        {
            qDebug() << "ContatoController::buscaTodos() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaContatos;
}

inline QVector<Contato> ContatoController::buscaPorNomeEmail(QString nome_email)
{
    sql = "SELECT ";
    sql += "id, nome, email, telefone ";
    sql += "FROM ";
    sql += "tb_contatos ";
    sql += "WHERE ";
    sql += "nome LIKE :nome OR ";
    sql += "email LIKE :email ";
    sql += "ORDER BY nome ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    QVector<Contato> listaContatos;
    Contato contato;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", "%" + nome_email + "%");
        query.bindValue(":email", "%" + nome_email + "%");
        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    contato.setId(query.record().value("id").toInt());
                    contato.setNome(query.record().value("nome").toString());
                    contato.setEmail(query.record().value("email").toString());
                    contato.setTelefone(query.record().value("telefone").toString());
                    listaContatos.push_back(contato);
                }
                while (query.next());
            }
            else
            {
                qDebug() << "ContatoController::buscaPorNomeEmail() query.next() Não retornou registros";
            }
        }
        else
        {
            qDebug() << "ContatoController::buscaPorNomeEmail() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaContatos;
}

inline bool ContatoController::altera(Contato contato)
{
    sql = "UPDATE tb_contatos SET ";
    sql += "nome = :nome, ";
    sql += "email = :email, ";
    sql += "telefone = :telefone ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":nome", contato.getNome());
        query.bindValue(":email", contato.getEmail());
        query.bindValue(":telefone", contato.getTelefone());
        query.bindValue(":id", contato.getId());
        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "ContatoController::altera() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

#endif // CONTATOCONTROLLER_H
