#ifndef GRUPO_H
#define GRUPO_H

#include <QString>

class Grupo
{
private:
    int id;
    QString descricao;
    QString sigla;
protected:
public:
    // CONSTRUCTOR
    Grupo() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
    QString getSigla() const;
    void setSigla(const QString &newSigla);
};

inline int Grupo::getId() const
{
    return id;
}

inline void Grupo::setId(int newId)
{
    id = newId;
}

inline QString Grupo::getDescricao() const
{
    return descricao;
}

inline void Grupo::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

inline QString Grupo::getSigla() const
{
    return sigla;
}

inline void Grupo::setSigla(const QString &newSigla)
{
    sigla = newSigla;
}
#endif // GRUPO_H
