#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "header/cube.h"
#include "header/objectMat.h"
#include "header/shader.h"
#include "header/stb_image.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int loadCubemap(std::vector<string> &mFileName);

struct material_t{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float gloss;
};

struct light_t{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct model_t{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    ObjectMat* objectmat;
};

struct camera_t{
    glm::vec3 position;
    glm::vec3 up;
    float rotationY;
};

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// cube map 
unsigned int cubemapTexture;
unsigned int cubemapVAO, cubemapVBO;

// shader programs 
int shaderProgramIndex = 0;
std::vector<shader_program_t*> shaderPrograms;
shader_program_t* cubemapShader;

// additional dependencies
light_t light;
material_t material;
camera_t camera;
// model_t helicopter;
// model_t helicopterBlade;
model_t santa;

// model matrix
int moveDir = -1;
// glm::mat4 helicopterModel;
// glm::mat4 helicopterBladeModel;
glm::mat4 cameraModel;
glm::mat4 santaModel;


// handle sun and cube map
glm::vec3 sunPosition;
float timeFactor;
float timeofDay = glm::pi<float>();
float timeSpeed = 0.005f;
// glm::mat4 sunModel;
float transFactor = 0.0f;
bool night2day = 0;
bool day2night = 0;

// melting
float timing = 0;
bool isMelting = false;

//////////////////////////////////////////////////////////////////////////
// Parameter setup, 
// You can change any of the settings if you want

void camera_setup(){
    camera.position = glm::vec3(0.0, 20.0, 100.0);
    camera.up = glm::vec3(0.0, 1.0, 0.0);
    camera.rotationY = 0;
}

void light_setup(){
    light.position = glm::vec3(0.0, 1000.0, 0.0);
    // light.ambient = glm::vec3(1.0);
    light.ambient = glm::vec3(1.0);
    light.diffuse = glm::vec3(1.0);
    light.specular = glm::vec3(1.0);
}

void material_setup(){
    material.ambient = glm::vec3(1.0);
    material.diffuse = glm::vec3(1.0);
    material.specular = glm::vec3(0.7);
    material.gloss = 10.5;
}
//////////////////////////////////////////////////////////////////////////

void santa_setup () {
    #if defined(__linux__) || defined(__APPLE__)
        std::string objDir = "../../src/asset/obj/";
        std::string textureDir = "../../src/asset/texture/santa";
    #else
        std::string objDir = "..\\..\\src\\asset\\obj\\";
        std::string textureDir = "..\\..\\src\\asset\\texture\\santa\\";
    #endif
    santaModel = glm::mat4(1.0f);

    santa.position = glm::vec3(0, -20, 0);
    santa.scale = glm::vec3(0.25, 0.25, 0.25);
    santa.rotation = glm::vec3(-90.0f, 0.0f, 0.0f);

    santa.objectmat = new ObjectMat(objDir + "santa.obj");
    printf("santa object loaded\n");
    
    santa.objectmat->load_material(textureDir + "santa.mtl");
    santa.objectmat->load_to_buffer();
    printf("load material success\n");
    for (const auto &material : santa.objectmat->materials) {
        printf("load %s\n", material.second.fileName.c_str());
        std::string texturePath = material.second.fileName;
        std::string materialName = material.first;
        std::ifstream file(texturePath);
        if (!file.good()) {
            std::cerr << "file not exist: " << texturePath << "\n";
            return; 
        }
        santa.objectmat->load_texture(texturePath);
        printf("santa texture load\n");
        santa.objectmat->materials[materialName].textureID = santa.objectmat->get_texture();
        // santa.object->textureIDs[material.first] = santa.objectget_texture();
    }
}


// void model_setup(){

// // Load the object and texture for each model here 

// #if defined(__linux__) || defined(__APPLE__)
//     std::string objDir = "../../src/asset/obj/";
//     std::string textureDir = "../../src/asset/texture/";
// #else
//     std::string objDir = "..\\..\\src\\asset\\obj\\";
//     std::string textureDir = "..\\..\\src\\asset\\texture\\";
// #endif
//     helicopterModel = glm::mat4(1.0f);

//     helicopter.position = glm::vec3(0.0f, -50.0f, 0.0f);
//     helicopter.scale = glm::vec3(0.1f, 0.1f, 0.1f);
//     helicopter.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
//     helicopter.object = new Object(objDir + "helicopter_body.obj");
//     helicopter.object->load_to_buffer();
//     helicopter.object->load_texture(textureDir + "helicopter_red.jpg");

//     helicopterBlade.position = helicopter.position;
//     helicopterBlade.scale = helicopter.scale;
//     helicopterBlade.rotation = helicopter.rotation;
//     helicopterBlade.object = new Object(objDir + "helicopter_blade.obj");
//     helicopterBlade.object->load_to_buffer();
//     helicopterBlade.object->load_texture(textureDir + "helicopter_red.jpg");
// }


void shader_setup(){

// Setup the shader program for each shading method

#if defined(__linux__) || defined(__APPLE__)
    std::string shaderDir = "../../src/shaders/";
#else
    std::string shaderDir = "..\\..\\src\\shaders\\";
#endif

    std::vector<std::string> shadingMethod = {
        "default",                              // default shading
        "rainbow",
        "water",
        "watertrans",
        "watertrans",
        "wave",
        // "bling-phong", "gouraud", "metallic",   // addional shading effects (basic)
        // "glass_schlick", "glass_empricial",     // addional shading effects (advanced)
    };

    for(int i=0; i<shadingMethod.size(); i++){
        std::string vpath = shaderDir + shadingMethod[i] + ".vert";
        std::string fpath = shaderDir + shadingMethod[i] + ".frag";

        shader_program_t* shaderProgram = new shader_program_t();
        shaderProgram->create();
        shaderProgram->add_shader(vpath, GL_VERTEX_SHADER);
        shaderProgram->add_shader(fpath, GL_FRAGMENT_SHADER);
        shaderProgram->link_shader();
        shaderPrograms.push_back(shaderProgram);
    } 
}


void cubemap_setup(){

// Setup all the necessary things for cubemap rendering
// Including: cubemap texture, shader program, VAO, VBO

#if defined(__linux__) || defined(__APPLE__)
    std::string cubemapDir = "../../src/asset/texture/skybox/";
    std::string shaderDir = "../../src/shaders/";
#else
    std::string cubemapDir = "..\\..\\src\\asset\\texture\\skybox\\";
    std::string shaderDir = "..\\..\\src\\shaders\\";
#endif

    // setup texture for cubemap
    std::vector<std::string> faces
    {
        cubemapDir + "right.jpg",
        cubemapDir + "left.jpg",
        cubemapDir + "top.jpg",
        cubemapDir + "bottom.jpg",
        cubemapDir + "front.jpg",
        cubemapDir + "back.jpg"
    };
    cubemapTexture = loadCubemap(faces);   

    // setup shader for cubemap
    std::string vpath = shaderDir + "cubemap.vert";
    std::string fpath = shaderDir + "cubemap.frag";
    
    cubemapShader = new shader_program_t();
    cubemapShader->create();
    cubemapShader->add_shader(vpath, GL_VERTEX_SHADER);
    cubemapShader->add_shader(fpath, GL_FRAGMENT_SHADER);
    cubemapShader->link_shader();

    glGenVertexArrays(1, &cubemapVAO);
    glGenBuffers(1, &cubemapVBO);
    glBindVertexArray(cubemapVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubemapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubemapVertices), &cubemapVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}

void setup(){

    // Initialize shader model camera light material
    light_setup();
    // model_setup();
    santa_setup();
    shader_setup();
    camera_setup();
    cubemap_setup();
    material_setup();

    // Enable depth test, face culling ...
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Debug: enable for debugging
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](  GLenum source, GLenum type, GLuint id, GLenum severity, 
                                GLsizei length, const GLchar* message, const void* userParam) {

    std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") 
              << "type = " << type 
              << ", severity = " << severity 
              << ", message = " << message << std::endl;
    }, nullptr);
}

void update(){
    santaModel = glm::mat4(1.0f);
    santaModel = glm::translate(santaModel, santa.position);
    // santaModel = glm::rotate(santaModel, glm::radians(santa.rotation.x), glm::vec3(0.0, 1.0, 0.0));
    santaModel = glm::rotate(santaModel, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    santaModel = glm::scale(santaModel, santa.scale);

    camera.rotationY = (camera.rotationY > 360.0) ? 0.0 : camera.rotationY;
    cameraModel = glm::mat4(1.0f);
    cameraModel = glm::rotate(cameraModel, glm::radians(camera.rotationY), camera.up);
    cameraModel = glm::translate(cameraModel, camera.position);

    // handle sun of day
    sunPosition = glm::vec3(sin(timeofDay), cos(timeofDay), 0.0f);
    timeFactor = glm::clamp((sunPosition.y + 1.0f) / 2.0f, 0.0f, 1.0f);
    transFactor = timeFactor;
    if (day2night) {
        if (timeofDay < glm::pi<float>()) timeofDay += timeSpeed;
        // if (timeofDay > 2.0f * glm::pi<float>()) {
        //     timeofDay -= 2.0f * glm::pi<float>();
        // }
    }
    if (night2day) {
        if (timeofDay > 0.0f) timeofDay -= timeSpeed;
    }
    
    // melting
    timing += 0.005;
}

void render(){

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate view, projection matrix
    glm::mat4 view = glm::lookAt(glm::vec3(cameraModel[3]), glm::vec3(0.0), camera.up);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

    // Set matrix for view, projection, model transformation
    shaderPrograms[shaderProgramIndex]->use();
    shaderPrograms[shaderProgramIndex]->set_uniform_value("model", santaModel);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("view", view);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("projection", projection);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("ourTexture", 0);
    // TODO 1
    // Set uniform value for each shader program
    shaderPrograms[shaderProgramIndex]->set_uniform_value("cameraPos", glm::vec3(cameraModel[3]));
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("lightPos", light.position);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("lightAmb", light.ambient);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("lightDiff", light.diffuse);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("lightSpec", light.specular);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("matGloss", material.gloss);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("matAmb", material.ambient);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("matDiff", material.diffuse);
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("matSpec", material.specular);
    float currentTime = glfwGetTime();
    shaderPrograms[shaderProgramIndex]->set_uniform_value("time", currentTime);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("distortionScale", 0.05f);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("timeFactor", timeFactor);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("noiseScale", 0.5f);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("amplitude", 0.1f);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("transFactor", transFactor);
    //在液化的part加
    shaderPrograms[shaderProgramIndex]->set_uniform_value("timing", timing);
    shaderPrograms[shaderProgramIndex]->set_uniform_value("isMelting", isMelting);
    santa.objectmat->render();
    // shaderPrograms[shaderProgramIndex]->set_uniform_value("model", helicopterBladeModel);
    // helicopterBlade.object->render();
    shaderPrograms[shaderProgramIndex]->release();

    // TODO 4-2 
    // Rendering cubemap environment
    // Hint:
    // 1. All the needed things are already set up in cubemap_setup() function.
    // 2. You can use the vertices in cubemapVertices provided in the header/cube.h
    // 3. You need to set the view, projection matrix.
    // 4. Use the cubemapShader to render the cubemap 
    //    (refer to the above code to get an idea of how to use the shader program)
    glm::mat4 cubemapView = glm::mat4(glm::mat3(view));
    cubemapShader->use();
    cubemapShader->set_uniform_value("projection", projection);
    cubemapShader->set_uniform_value("view", cubemapView);
    cubemapShader->set_uniform_value("timeFactor", timeFactor);
    // cubemapShader->set_uniform_value("time", glfwGetTime());
    glDepthFunc(GL_LEQUAL); // Render skybox after all objects
    glBindVertexArray(cubemapVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

}


int main() {
    
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HW3-111550139", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set viewport
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Setup texture, model, shader ...e.t.c
    setup();
    
    // Render loop, main logic can be found in update, render function
    while (!glfwWindowShouldClose(window)) {
        update();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Add key callback
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    // The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
    // Events with GLFW_PRESS and GLFW_RELEASE actions are emitted for every key press.
    // Most keys will also emit events with GLFW_REPEAT actions while a key is held down.
    // https://www.glfw.org/docs/3.3/input_guide.html

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // shader program selection
    if (key == GLFW_KEY_0 && (action == GLFW_REPEAT || action == GLFW_PRESS)) 
        shaderProgramIndex = 0;
    if (key == GLFW_KEY_1 && (action == GLFW_REPEAT || action == GLFW_PRESS)) 
        shaderProgramIndex = 1;
    if (key == GLFW_KEY_2 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        shaderProgramIndex = 2;
        printf("is melting %d\n", isMelting);
        isMelting = !isMelting;
        timing = 0;
    }
       
    if (key == GLFW_KEY_3 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        shaderProgramIndex = 3;
    }
    if (key == GLFW_KEY_4 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        shaderProgramIndex = 4;
    }
    if (key == GLFW_KEY_5 && (action == GLFW_REPEAT || action == GLFW_PRESS))
        shaderProgramIndex = 5;
    if (key == GLFW_KEY_M && (action == GLFW_PRESS)) {  // to day
        transFactor = 0.0f;
        night2day = 1;
        day2night = 0;
        timeofDay = glm::pi<float>();  // mid night
    }
    if (key == GLFW_KEY_N && (action == GLFW_PRESS)) {  // to night
        transFactor = 0.0f;
        day2night = 1;
        night2day = 0;
        timeofDay = 0.0f;  // day
    }
    

    // camera movement
    float cameraSpeed = 0.5f;
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.position.z -= 10.0;
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.position.z += 10.0;
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.rotationY -= 10.0;
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.rotationY += 10.0;
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

// Loading cubemap texture
unsigned int loadCubemap(vector<std::string>& faces){

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture;
}  