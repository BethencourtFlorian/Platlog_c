#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QXmlStreamReader>
#include <QFile>
#include <qdom.h>
#include "user.h"

class XMLParser{
public:
    static int CheckUser(QDomDocument& document, QDomElement& users, QString filePath);
    static int CheckConnexion(QString filePath, user& foundUser, QString typedPassword, QString typedLogin);
};

#endif // XMLPARSER_H
