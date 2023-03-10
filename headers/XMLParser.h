#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QXmlStreamReader>
#include <QFile>
#include <qdom.h>
#include "user.h"

class XMLParser{
public:
    /**
     * @brief Consulte la liste des utilisateurs
     *
     * Si la liste est vide, un "super" utilisateur est créé.
     * Sinon on renvoie la liste de tous les utilisateurs
     * @param document Un QDomDocument pour copier le contenu du fichier XML
     * @param users Un QDomElement faisant partie de document nécessaire à la copie du fichier XML
     * @param filePath Le chemin vers le fichier XML des utilisateurs
     * @return 0 si tout va bien, un code d'erreur sinon
     */
    static int AddUser(QDomDocument& document, QDomElement newUser, QString filePath);
    /**
     * @brief Tente une combinaison login/mdp
     *
     * Parcourt le fichier XML : si une cominaison est trouvée, on stocke les infos de l'utilisateur dans foundUser
     * Sinon on renvoie un code d'erreur
     * @param filePath Le chemin vers le fichier XML des utilisateurs
     * @param foundUser contiendra les informations de l'utilisateur trouvé si la fonction n'échoue pas
     * @param typedPassword Le mot de passe rentré dans le formulaire
     * @param typedLogin Le login rentré dans le formulaire
     * @return 0 si tout va bien, un code d'erreur sinon
     */
    static int CheckConnexion(QString filePath, user& foundUser, QString typedPassword, QString typedLogin);

    static QDomNodeList getProfiles(QString path, QString username);
};

#endif // XMLPARSER_H
