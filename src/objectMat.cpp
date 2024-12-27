#include "header/objectMat.h"
#include <glad/glad.h>
#include "header/stb_image.h"
#include <unordered_map>
#include <sstream>
#include <fstream>

void ObjectMat::load_material(const std::string &filepath) {
    std::ifstream mtlFile(filepath);
    if (!mtlFile.is_open()) {
        std::cerr << "Failed to open MTL file: " << filepath << std::endl;
        return;
    }
    std::string line, materialName, textureFile;
    std::string textureDir = "..\\..\\src\\asset\\texture\\santa\\";
    while (std::getline(mtlFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "newmtl") {
            iss >> materialName;
        }
        else if (prefix == "map_Kd") {
            iss >> textureFile;
            textureFile = textureDir + textureFile;

            materials[materialName].fileName = textureFile;
        }
    }
    mtlFile.close();
}

void ObjectMat::load_texture(const std::string &filepath){
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // std::string materialName = m
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // materials[materialName].textureID = texture;
    } else {
        std::cout << "Failed to load texture1" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void ObjectMat::load_to_buffer(){
    for (auto it = materials.begin(); it != materials.end(); it++) {
        std::string materialName = it->first;
        Mesh& mesh = it->second;
        if (mesh.positions.empty()) {
            std::cerr << "Warning: Mesh positions are empty for material " << materialName << std::endl;
        }

        glGenVertexArrays(1, &mesh.VAO);
        if (mesh.VAO == 0) {
            std::cerr << "Failed to generate VAO\n";
        }
        glBindVertexArray(mesh.VAO);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << " during VAO binding" << std::endl;
        }
        glGenBuffers(3, mesh.VBO);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (mesh.positions.size()), &(mesh.positions[0]), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (mesh.normals.size()), &(mesh.normals[0]), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (mesh.texcoords.size()), &(mesh.texcoords[0]), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }    
}

void ObjectMat::render(){
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);
    // for (const auto &[material, mesh] : materials) {
    for (auto it = materials.begin(); it != materials.end(); it++) {
        const std::string& material = it->first;
        const Mesh& mesh = it->second;
        if (mesh.positions.empty()) {
            std::cerr << "Warning: Mesh positions are empty for material " << material << std::endl;
        }
        glBindVertexArray(mesh.VAO);
        // const auto &textureID = textureIDs[material.first];
        // cout << "using mat: " << material.first << "\n";
        // if (textureID) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh.textureID);
        // }
        // Draw the ObjectMatmat
        // glBindVertexArray(mesh.VAO);
        GLint currentVAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
        // if (currentVAO == 0) {
        //     std::cerr << "No VAO bound before glDrawArrays()" << std::endl;
        // }
        glDrawArrays(GL_TRIANGLES, 0, mesh.positions.size());
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(0);
    }

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture);
    
    // glDrawArrays(GL_TRIANGLES, 0, positions.size());
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glBindVertexArray(0);
}

unsigned int ObjectMat::get_texture () {
    return texture;
}