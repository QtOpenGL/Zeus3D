#ifndef MTLLOADER_H
#define MTLLOADER_H
#include <map>
#include <QString>

/*
 * load the material of obj file
 */
class MtlLoader
{
public:
    std::map<QString,int> objMtls; // cache material name and it's index

    MtlLoader(const QString &mtlPath);
    ~MtlLoader();

private:
    QString mtlFilePath;
    int mtlCount;

    void readMtlInfo();
};

#endif // MTLLOADER_H
