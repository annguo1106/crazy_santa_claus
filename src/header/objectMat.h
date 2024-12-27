#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <glm/glm.hpp>
#include <string.h>
#include <unordered_map>

using namespace std;

enum class FACETYPE1 {
    TRIANGLE,
    QUAD
};

class ObjectMat {
public:

    ObjectMat(const string &obj_file) {
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        vector<glm::vec3> tmp_vertices;
        vector<glm::vec3> tmp_normals;
        vector<glm::vec2> tmp_texcoords;

        regex wTexture_3(" [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ *\n");
        regex woTexture_3(" [0-9]+//[0-9]+ [0-9]+//[0-9]+ [0-9]+//[0-9]+ *\n");
        regex wTexture_4(" [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ *\n");

        FILE *file = fopen(obj_file.c_str(), "r");
        if (file == NULL) {
            cout << "Can't open obj file!\n";
            return;
        }

        int line_count = 1;
        char currentmaterial[512] = {0};
        while (true) {
            // cout << "Line " << line_count << "\n";
            line_count++;
            char lineHead[512];
            int res = fscanf(file, "%s", lineHead);
            if (res == EOF) {
                break;
            }
            if (strcmp(lineHead, "usemtl") == 0) {
                fscanf(file, "%s", currentmaterial);
                if (materials.find(currentmaterial) == materials.end()) {
                    materials[currentmaterial] = Mesh();
                }
            }
            if (strcmp(lineHead, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                // materials[currentmaterial].positions.push_back(vertex);
                tmp_vertices.push_back(vertex);
            } else if (strcmp(lineHead, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                // materials[currentmaterial].normals.push_back(normal);
                tmp_normals.push_back(normal);
            } else if (strcmp(lineHead, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                // materials[currentmaterial].texcoords.push_back(uv);
                tmp_texcoords.push_back(uv);
            } else if (strcmp(lineHead, "f") == 0) {
                char f_line[128];
                int vertexIndex[4], uvIndex[4], normalIndex[4];
                fgets(f_line, sizeof(f_line), file);
                // materials[currentmaterial].numFace++;

                if (regex_match(f_line, wTexture_3)) {
                    sscanf(f_line, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                           &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                           &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                           &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                } else if (regex_match(f_line, woTexture_3)) {
                    sscanf(f_line, "%d//%d %d//%d %d//%d\n",
                           &vertexIndex[0], &normalIndex[0],
                           &vertexIndex[1], &normalIndex[1],
                           &vertexIndex[2], &normalIndex[2]);
                    uvIndex[0] = -1;
                    uvIndex[1] = -1;
                    uvIndex[2] = -1;
                } else if (regex_match(f_line, wTexture_4)) {
                    faceType = FACETYPE1::QUAD;
                    sscanf(f_line, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                           &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                           &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                           &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                           &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
                }

                Mesh& mesh = materials[currentmaterial];

                if (faceType == FACETYPE1::QUAD) {
                    numFace++;
                    // for (int i : {0, 1, 2}) add_face_data(mesh, tmp_vertices, tmp_texcoords, tmp_normals, vertexIndex[i], uvIndex[i], normalIndex[i]);
                    // for (int i : {2, 3, 0}) add_face_data(mesh, tmp_vertices, tmp_texcoords, tmp_normals, vertexIndex[i], uvIndex[i], normalIndex[i]);
                    
                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[0]);
                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[1]);
                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[2]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[0]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[1]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[2]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[0]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[1]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[2]);

                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[2]);
                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[3]);
                    materials[currentmaterial].vertexIndices.push_back(vertexIndex[0]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[2]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[3]);
                    materials[currentmaterial].uvIndices.push_back(uvIndex[0]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[2]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[3]);
                    materials[currentmaterial].normalIndices.push_back(normalIndex[0]);
                } else {
                    // for (int i = 0; i < 3; i++) {
                    //     add_face_data(mesh, tmp_vertices, tmp_texcoords, tmp_normals, vertexIndex[i], uvIndex[i], normalIndex[i]);
                    // }
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                }
            } else {
            }
        }

        // file read ends
        printf("file read ends\n");
        for (auto it = materials.begin(); it != materials.end(); it++) {
            const std::string& material = it->first;
            // printf("now material: %s\n", material);
            // cout << "now material " << material << "\n";
            Mesh& mesh = it->second;
            for (unsigned int i = 0; i < mesh.vertexIndices.size(); i++) {
                // cout << "now i : " << i << "\n";
                unsigned int vertexIndex = mesh.vertexIndices[i];
                glm::vec3 vertex = tmp_vertices[vertexIndex - 1];
                mesh.positions.push_back(vertex.x);
                mesh.positions.push_back(vertex.y);
                mesh.positions.push_back(vertex.z);
                // cout << "push position\n";
                // mesh.positions.push_back(vertex.x);
                // mesh.positions.push_back(vertex.y);
                // mesh.positions.push_back(vertex.z);
                vertexIndex = mesh.uvIndices[i];

                if (vertexIndex != -1) {
                    glm::vec2 uv = tmp_texcoords[vertexIndex - 1];
                    // texcoords.push_back(uv.x);
                    // texcoords.push_back(uv.y);
                    mesh.texcoords.push_back(uv.x);
                    mesh.texcoords.push_back(uv.y);
                } else {
                    // texcoords.push_back(0);
                    // texcoords.push_back(0);
                    mesh.texcoords.push_back(0.0f);
                    mesh.texcoords.push_back(0.0f);
                }
                // cout << "push texcoords\n";

                vertexIndex = mesh.normalIndices[i];
                glm::vec3 normal = tmp_normals[vertexIndex - 1];
                // normals.push_back(normal.x);
                // normals.push_back(normal.y);
                // normals.push_back(normal.z);
                mesh.normals.push_back(normal.x);
                mesh.normals.push_back(normal.y);
                mesh.normals.push_back(normal.z);
                // cout << "push normal\n";
            }  
        }
        

    };
    void load_material(const string& filepath);
    void load_to_buffer();
    void load_texture(const string& filepath);
    void render();
    unsigned int get_texture();
    struct Mesh {
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> texcoords;
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        unsigned int VAO;
        unsigned int VBO[3];
        unsigned int textureID;
        int numFace = 0;
        std::string fileName;
    };
    std::unordered_map<std::string, Mesh> materials;
    std::unordered_map<std::string, unsigned int> textureIDs;
    

    

private:
    FACETYPE1 faceType = FACETYPE1::TRIANGLE;
    vector<float> positions;
    vector<float> normals;
    vector<float> texcoords;
    unsigned int texture;
    unsigned int VAO; 
    unsigned int VBO[3];
    int numFace = 0;
    // void add_face_data (Mesh& mesh, const std::vector<glm::vec3>& tmp_vertices,
    //                    const std::vector<glm::vec2>& tmp_texcoords, const std::vector<glm::vec3>& tmp_normals,
    //                    int vertexIndex, int uvIndex, int normalIndex) {
    //     if (vertexIndex > 0 && vertexIndex <= tmp_vertices.size()) {
    //         mesh.positions.push_back(tmp_vertices[vertexIndex - 1]);
    //     }

    //     // Texture coordinates
    //     if (uvIndex > 0 && uvIndex <= tmp_texcoords.size()) {
    //         mesh.texcoords.push_back(tmp_texcoords[uvIndex - 1]);
    //     } else {
    //         mesh.texcoords.push_back(glm::vec2(0.0f, 0.0f)); // Default UV
    //     }

    //     // Normals
    //     if (normalIndex > 0 && normalIndex <= tmp_normals.size()) {
    //         mesh.normals.push_back(tmp_normals[normalIndex - 1]);
    //     }
    // }
};