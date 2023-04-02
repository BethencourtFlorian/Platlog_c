#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QXmlStreamReader>
#include <QFile>
#include <qdom.h>
#include "user.h"
#include "profile.h"
#include "database.h"

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
     * @brief Ajoute une base de données à un profil
     *
     * @param path chemin d'accès au fichier XML
     * @param user utilisateur actuellement connecté au logiciel
     * @param database base de données à insérer
     * @param idProfile identifiant de profil dans le fichier XML
     * @return void
     */
    static void AddDatabase(QString path, User& user, Database& database, int idProfile);

    /**
     * @brief Retrouve une base de données dans le fichier XML, puis la retourne
     *
     * @param path chemin d'accès au fichier XML
     * @param user utilisateur actuellement connecté au logiciel
     * @param profileName nom du profil de l'utilisateur
     * @param databaseName nom de la base de données à retrouver
     * @return Database* pointeur vers la base de données (url et nom)
     */

    static Database* searchDatabase(QString path, User& user, QString profileName, QString databaseName);
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
    static int CheckConnexion(QString filePath, User& foundUser, QString typedPassword, QString typedLogin);

    /**
     * @brief Retourne la liste des utilisateurs créés depuis le fichier XML
     *
     * @param filePath chemin d'accès au fichier XML
     * @return filePath liste des utilisateurs du fichier XML
     */
    static std::list<User*> GetUsers(QString filePath);

    /**
     * @brief Permet de remplir un objet user avec les profils/base de données du fichier XML
     *
     * @param path chemin d'accès au fichier XML
     * @param user utilisateur à remplir avec les profils et bases de données correspondants.
     * @return void
     */
    static void fillUser(QString path, User& user);

    /**
     * @brief Supprime un profil ainsi que ses bases de données pour un fichier XML
     *
     * @param filePath chemin d'accès au fichier XML
     * @param user utilisateur possédant le profil à supprimer
     * @param profileName nom du profil à supprimer
     * @return void
     */
    static void deleteProfileById(QString filePath, User& user, QString profileName);

    /**
     * @brief Supprime la base de données d'un profil pour un fichier XML
     *
     * @param filePath chemin d'accès au fichier XML
     * @param user utilisateur possédant la base de données à supprimer
     * @param profileName nom du profil possédant la base de données à supprimer
     * @param databaseName nom de la base de données à supprimer
     * @return void
     */
    static void deleteDatabaseById(QString filePath, User& user, QString profileName, QString databaseName);

    /**
     * @brief Permet de recharger le contenu du fichier XML dans les objets utilisateurs, profils et bases de données
     *
     * @param path chemin d'accès au fichier XML
     * @param listUsers liste d'utilisateurs à mettre à jour selon le fichier XML
     * @return void
     */
    static void saveChanges(QString path, list<User*> listUsers);

    /**
     * @brief Permet de recharger le contenu du fichier XML dans les objets utilisateurs, profils et bases de données
     *
     * @param path chemin d'accès au fichier XML
     * @param oldLogin string pour trouver l'utilisateur à modifier
     * @param userUpdated utilisateur contenant les nouvelles informations
     * @return void
     */
    static void editUserInfo(QString path, QString oldLogin, User userUpdated);
};

#endif // XMLPARSER_H
