#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include "Conexao.h"
#include "Grupo.h"

class GrupoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    GrupoController() {}

    // METHODS
    Grupo insere(Grupo grupo);
    QVector<Grupo> buscaTodos();
    QVector<Grupo> buscaPorDescricao(QString descricao);
    bool buscaDescricaoDuplicada(QString descricao);
    bool buscaSiglaDuplicada(QString sigla);
    bool altera(Grupo grupo);

};

inline Grupo GrupoController::insere(Grupo grupo)
{
    sql = "INSERT INTO tb_grupos ( descricao, sigla ) ";
    sql += "VALUES ( :descricao, :sigla )";

    if (!conn.isOpen())
    {
        conn.open();
    }

    if (conn.isOpen())
    {
        query.exec("BEGIN IMMEDIATE TRANSACTION");
        query.prepare(sql);
        query.bindValue(":descricao", grupo.getDescricao());
        query.bindValue(":sigla", grupo.getSigla());
        if (query.exec())
        {
            sql = "SELECT id FROM tb_grupos ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec())
            {
                if (query.next())
                {
                    grupo.setId(query.record().value("id").toInt());
                }
            }
            else
            {
                qDebug() << "GrupoController::insere() query.exec(SELECT): " << query.lastError().text();
            }
        }
        else
        {
            qDebug() << "GrupoController::insere() query.exec(INSERT): " << query.lastError().text();
        }
        query.exec("COMMIT");
    }
    conn.close();
    return grupo;
}

inline QVector<Grupo> GrupoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "id, descricao, sigla ";
    sql += "FROM tb_grupos ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    QVector<Grupo> listaGrupos;

    if (conn.isOpen())
    {
        query.prepare(sql);
        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                    listaGrupos.push_back(grupo);
                }
                while (query.next());
            }
            else
            {
                qDebug() << "GrupoController::buscaTodos() query.next(): 0 registros.";
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaTodos() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaGrupos;
}

inline QVector<Grupo> GrupoController::buscaPorDescricao(QString descricao)
{
    sql = "SELECT ";
    sql += "id, descricao, sigla ";
    sql += "FROM tb_grupos ";
    sql += "WHERE descricao LIKE :descricao ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
    {
        conn.open();
    }

    Grupo grupo;
    QVector<Grupo> listaGrupos;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":descricao", "%" + descricao + "%");
        if (query.exec())
        {
            if (query.next())
            {
                do
                {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                    listaGrupos.push_back(grupo);
                }
                while (query.next());
            }
            else
            {
                qDebug() << "GrupoController::buscaPorDescricao() query.next(): 0 registros.";
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaPorDescricao() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return listaGrupos;
}

inline bool GrupoController::buscaDescricaoDuplicada(QString descricao)
{
    sql = "SELECT ";
    sql += "descricao ";
    sql += "FROM tb_grupos ";
    sql += "WHERE descricao = :descricao";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":descricao", descricao);
        if (query.exec())
        {
            if (query.next())
            {
                retorno = true;
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaDescricaoDuplicada() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

inline bool GrupoController::buscaSiglaDuplicada(QString sigla)
{
    sql = "SELECT ";
    sql += "descricao ";
    sql += "FROM tb_grupos ";
    sql += "WHERE sigla = :sigla";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":sigla", sigla);
        if (query.exec())
        {
            if (query.next())
            {
                retorno = true;
            }
        }
        else
        {
            qDebug() << "GrupoController::buscaSiglaDuplicada() query.exec(): " << query.lastError().text();
        }
    }
    conn.close();
    return retorno;
}

inline bool GrupoController::altera(Grupo grupo)
{
    sql = "UPDATE tb_grupos SET ";
    sql += "descricao = :descricao, ";
    sql += "sigla = :sigla ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
    {
        conn.open();
    }

    bool retorno = false;

    if (conn.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":descricao", grupo.getDescricao());
        query.bindValue(":sigla", grupo.getSigla());
        query.bindValue(":id", grupo.getId());
        if (query.exec())
        {
            retorno = true;
        }
        else
        {
            qDebug() << "GrupoController::altera() query.exec(): " << query.lastError().text();
        }

    }
    conn.close();
    return retorno;
}

#endif // GRUPOCONTROLLER_H
