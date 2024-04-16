#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSqlDatabase>
#include <QTableWidget>
#include "Colaborador.h"

class global
{
public:
    global();

    // VARIABLES
    static Colaborador colaboradorLogado;
    static bool isLogged;
    static QSqlDatabase dataBase;
    static QString version;

    // FUNCTIONS
    static void initializeGlobalVariables();
    static bool minCharacters(QString str, int quantity);
    static void formatTableWidget(QTableWidget *tw, QStringList header);

};

#endif // GLOBAL_H
