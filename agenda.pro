QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_autenticacao.cpp \
    fm_colaboradores.cpp \
    fm_grupos.cpp \
    global.cpp \
    main.cpp \
    fm_principal.cpp

HEADERS += \
    Colaborador.h \
    ColaboradorController.h \
    Conexao.h \
    Contato.h \
    ContatoController.h \
    Grupo.h \
    GrupoController.h \
    fm_autenticacao.h \
    fm_colaboradores.h \
    fm_grupos.h \
    fm_principal.h \
    global.h

FORMS += \
    fm_autenticacao.ui \
    fm_colaboradores.ui \
    fm_grupos.ui \
    fm_principal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource_files.qrc
