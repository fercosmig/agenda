#ifndef CONTATO_H
#define CONTATO_H

#include <QString>

class Contato
{
private:
    int id;
    QString nome;
    QString email;
    QString telefone;

protected:
public:
    // CONSTRUCTOR
    Contato() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QString getTelefone() const;
    void setTelefone(const QString &newTelefone);
};

inline int Contato::getId() const
{
    return id;
}

inline void Contato::setId(int newId)
{
    id = newId;
}

inline QString Contato::getNome() const
{
    return nome;
}

inline void Contato::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Contato::getEmail() const
{
    return email;
}

inline void Contato::setEmail(const QString &newEmail)
{
    email = newEmail;
}

inline QString Contato::getTelefone() const
{
    return telefone;
}

inline void Contato::setTelefone(const QString &newTelefone)
{
    telefone = newTelefone;
}

#endif // CONTATO_H
