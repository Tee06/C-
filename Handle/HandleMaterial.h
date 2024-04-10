#ifndef HANDLE_MATERIAL_H
#define HANDLE_MATERIAL_H

#include "../Entity/Material.h"
#include<vector>

class HandleMaterial {
public:
    vector<Material> convertData(vector<Material> materials);
    void displayMenu();
    void displayDataList(vector<Material> materials);
    void insertRow();
    void deleteRow(string lineToRemove);
    void updateRow(string lineToUpdate);
    string findLineDataById(vector<Material> materials, string materialId);
    void rewriteFile(vector<string> lines);
    Material findMaterialById(vector<Material> materials, string materialId);
    void displayInfoMaterialAndSold(string materialId, int sold);
};

#endif
