#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H
#include <QVector3D>
#include <QVector4D>
#include <QString>

#include <vector>
#include <map>
/*
 * Texture resource manager
 */

#ifndef DEFAULT_MAT
#define DEFAULT_MAT "default_mat"
#endif
#ifndef BLACK_MAT
#define BLACK_MAT "black_mat"
#endif

struct Material // Material intance
{
    int id;//在list中的索引下标
    QString name;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    QVector4D texture;
    Material(const QString &mtlName){
        id = -1;
        name = mtlName;
        texture = QVector4D(-1,-1,-1,-1);
        ambient = QVector3D(0.4, 0.4, 0.4);
        diffuse = QVector3D(0.6, 0.6, 0.6);
        specular = QVector3D(0, 0, 0);
    }
};

class MaterialManager
{
public:
    static MaterialManager* materials;// SingleTon

    // Creator and Destroying
    static void Init();
    static void Release();

    // Modification
    unsigned int add(Material* material);
    void remove(unsigned int i);

    // Getter
    Material *find(unsigned int i);
    int find(QString name);
    unsigned int size();

private:
    std::vector<Material*> materialList;
    std::map<QString, Material*> materialMap; // To get the material quickly

    MaterialManager();
    ~MaterialManager();
};

#endif // MATERIALMANAGER_H
