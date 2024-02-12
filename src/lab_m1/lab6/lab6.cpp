#include "lab_m1/lab6/lab6.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

typedef struct coordonate {
    float x;
    float y;
    float z;
} coordonate;

typedef struct parte {
    Mesh *mesh;
    coordonate coord;
    glm::vec3 poz;
    glm::mat4 modelMatrix;
    Shader *shader;
} parte;

typedef struct tank {
    parte senila1;
    parte senila2;
    parte cap;
    parte corp;
    parte tun;
    parte bila;
    coordonate pas;
    coordonate centru;
    float unghi;
} tank;

Lab6::Lab6()
{
}


Lab6::~Lab6()
{
}


void Lab6::Init()
{
    {
        Mesh* mesh = new Mesh("senila");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senila.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cap");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cap.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("proiectil");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "proiectil.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cladire");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cladire.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    
    // Create a shader program for drawing face polygon with the color of the black
    {
        Shader *shader = new Shader("Negru");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "ngru_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "ngru_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the white
    {
        Shader *shader = new Shader("Alb");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "alb_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "alb_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the light pink
    {
        Shader *shader = new Shader("lpnk");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "rd_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "rd_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the dark pink
    {
        Shader *shader = new Shader("dpnk");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "ri_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "ri_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

     // Create a shader program for drawing face polygon with the color of the light pink
    {
        Shader *shader = new Shader("movd");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "md_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "md_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the dark pink
    {
        Shader *shader = new Shader("movi");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "mi_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "mi_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the light grey
    {
        Shader *shader = new Shader("GriDeschis");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "gri_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "gri_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the light green
    {
        Shader *shader = new Shader("VerdeDeschis");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "vd_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "vd_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a shader program for drawing face polygon with the color of the dark-green
    {
        Shader *shader = new Shader("VerdeInchis");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "vi_ver.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "vi_frag.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    renderCameraTarget = false;
    projectionType = true;

    right = 10.f;
    left = .01f;
    bottom = .01f;
    top = 10.f;
    fov = 40.f;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "proiectil.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    //projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, Z_NEAR, Z_FAR);

}


Mesh* Lab6::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

coordonate punct, sen1 = {0, 0.03f, -0.125f}, sen2 = {0, 0.03f, 0.125f}, 
crp = {0, 0.14f, 0}, cp = {0, 0.285f, 0}, tn = {-0.075f, 0.285f, 0}, ctr = {0, 0.224, 0},
isen2 = {-1.75f, 0.03f, -2}, isen1 = {-1.75f, 0.03f, -1.77f}, icrp = {-1.75f, 0.125f, -1.9f}, 
icp = {-1.75f, 0.285f, -1.9f}, itn = {-1.75f, 0.285f, -1.87f}, ictr = {-1.75f, 0.224, -1.9f},
insen2 = {-1.85f, 0.03f, 0.5}, insen1 = {-1.5f, 0.03f, 0.27f}, incrp = {-1.75f, 0.125f, 0.4f}, 
incp = {-1.75f, 0.285f, 0.4f}, intn = {-1.70f, 0.285f, 0.4f}, inctr = {-1.75f, 0.224, 0.4f};
glm::vec3 pozitie;
tank myTank;
tank inamic, ina;
parte myPart;
glm::vec3 cu_cat, to_ctr;
float unghi_turela, unghi_turela_up;
bool shooting = false, isBallVisible = false, apasat = false, dr = false;
float timp, timp_apasare;
coordonate pas_pr, ipas_pr;

void Lab6::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    myTank.centru = ctr;

}

void Lab6::Update(float deltaTimeSeconds)
{
    timp += deltaTimeSeconds;
    glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    myTank.unghi = glm::clamp(myTank.unghi, -glm::pi<float>(), glm::pi<float>());
    myTank.centru.x += myTank.pas.x * glm::cos(myTank.unghi) * deltaTimeSeconds;
    myTank.centru.y += myTank.pas.y * deltaTimeSeconds;
    myTank.centru.z += myTank.pas.z * glm::sin(myTank.unghi) * deltaTimeSeconds;
    cu_cat.x = -myTank.centru.x;
    cu_cat.y = -myTank.centru.y;
    cu_cat.z = -myTank.centru.z;

    // caldire1
    {
        punct = {0.8, 0.1f, -1};
        pozitie = {punct.x, punct.y, punct.z};
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pozitie);
        RenderSimpleMesh(meshes["cladire"], shaders["GriDeschis"], modelMatrix);
    }

    // caldire2
    {
        punct = {-1.5, 0.1f, -2};
        pozitie = {punct.x, punct.y, punct.z};
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pozitie);
        RenderSimpleMesh(meshes["cladire"], shaders["GriDeschis"], modelMatrix);
    }

    // caldire3
    {
        punct = {0.5, 0.1f, -3};
        pozitie = {punct.x, punct.y, punct.z};
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pozitie);
        RenderSimpleMesh(meshes["cladire"], shaders["Alb"], modelMatrix);
    }

    //player
    {
        glm::mat4 tankTransform = glm::translate(glm::mat4(1), glm::vec3(myTank.centru.x, myTank.centru.y, myTank.centru.z));
        tankTransform = glm::rotate(tankTransform, myTank.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
        tankTransform = glm::translate(tankTransform, glm::vec3(cu_cat.x, cu_cat.y, cu_cat.z));
        
        // senila1
        {
            punct = sen1;
            // Calculate the new position of senila1
            pozitie = {punct.x + myTank.pas.x, punct.y + myTank.pas.y, punct.z + myTank.pas.z};
            to_ctr = {myTank.centru.x, myTank.centru.y + 0.16f, myTank.centru.z + 0.125f};
            cu_cat = {(-1) * myTank.centru.x, (-1) * myTank.centru.y - 0.16f, (-1) * myTank.centru.z - 0.125f};
                // Apply the transformations to the model matrix
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, pozitie);
                modelMatrix = glm::translate(modelMatrix, to_ctr);
                modelMatrix = glm::rotate(modelMatrix, myTank.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
                modelMatrix = glm::translate(modelMatrix, cu_cat);
                // Render senila1
                myPart.coord = punct;
                myPart.mesh = meshes["senila"];
                myPart.shader = shaders["GriDeschis"];
                myPart.poz = pozitie;
                myPart.modelMatrix = modelMatrix;
                myTank.senila1 = myPart;
                RenderSimpleMesh(myTank.senila1.mesh, myTank.senila1.shader, myTank.senila1.modelMatrix);
        }
        
        // senila2
        {
            punct = sen2;
            // Calculate the new position of senila2
           pozitie = {punct.x + myTank.pas.x, punct.y + myTank.pas.y, punct.z + myTank.pas.z};
           to_ctr = {myTank.centru.x, myTank.centru.y + 0.16f, myTank.centru.z - 0.125f};
           cu_cat = {(-1) * myTank.centru.x, (-1) * myTank.centru.y - 0.16f, (-1) * myTank.centru.z + 0.125f};
            // Apply the transformations to the model matrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::translate(modelMatrix, to_ctr);
            modelMatrix = glm::rotate(modelMatrix, myTank.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, cu_cat);
            // Render senila2
            myPart.coord = punct;
            myPart.mesh = meshes["senila"];
            myPart.shader = shaders["GriDeschis"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            myTank.senila2 = myPart;
            RenderSimpleMesh(myTank.senila2.mesh, myTank.senila2.shader, myTank.senila2.modelMatrix);
        }

        // corp
        {
            punct = crp;
            pozitie = {punct.x + myTank.pas.x, punct.y + myTank.pas.y, punct.z + myTank.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["corp"];
            myPart.shader = shaders["VerdeInchis"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            myTank.corp = myPart;
            RenderSimpleMesh(myTank.corp.mesh, myTank.corp.shader, myTank.corp.modelMatrix);
        }

        // cap
        {
            punct = cp;
            pozitie = {punct.x + myTank.pas.x, punct.y + myTank.pas.y, punct.z + myTank.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank.centru.x, myTank.centru.y, myTank.centru.z));
            modelMatrix = glm::rotate(modelMatrix, unghi_turela, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-myTank.centru.x, -myTank.centru.y, -myTank.centru.z));
            myPart.coord = punct;
            myPart.mesh = meshes["cap"];
            myPart.shader = shaders["VerdeDeschis"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            myTank.cap = myPart;
            RenderSimpleMesh(myTank.cap.mesh, myTank.cap.shader, myTank.cap.modelMatrix);
        }
        //tun 
       {
            punct = tn;
            pozitie = { punct.x + myTank.pas.x, punct.y + myTank.pas.y, punct.z + myTank.pas.z };
            // Aplicarea transformărilor pe modelMatrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::rotate(modelMatrix, unghi_turela, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix *= tankTransform;  // Adaugă transformările pentru întregul tanc
            myPart.coord = punct;
            myPart.mesh = meshes["tun"];
            myPart.shader = shaders["GriDeschis"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            myTank.tun = myPart;
            RenderSimpleMesh(myTank.tun.mesh, myTank.tun.shader, myTank.tun.modelMatrix);
        }
        //bila
       {
              punct = myTank.centru;
            punct.y = tn.y;
            pozitie = {punct.x + myTank.pas.x + pas_pr.x, punct.y + myTank.pas.y + pas_pr.y, punct.z + myTank.pas.z + pas_pr.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank.centru.x, myTank.centru.y, myTank.centru.z));
            modelMatrix = glm::rotate(modelMatrix, unghi_turela, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-myTank.centru.x, -myTank.centru.y, -myTank.centru.z));
            myPart.coord = punct;
            myPart.mesh = meshes["proiectil"];
            myPart.shader = shaders["Negru"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            myTank.bila = myPart;
            if (isBallVisible) {
                myTank.bila.coord.x = punct.x + myTank.pas.x + pas_pr.x;
                myTank.bila.coord.y = punct.y;
                myTank.bila.coord.z = punct.z + myTank.pas.x + pas_pr.z;
                RenderSimpleMesh(myTank.bila.mesh, myTank.bila.shader, myTank.bila.modelMatrix);
                if (timp - timp_apasare >= 0.75f) {
                    // la fiecare 3 secunde
                    // Resetază starea bilei pentru a o face să dispară după un timp
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0,0,0));
                    RenderSimpleMesh(myTank.bila.mesh, myTank.bila.shader, myTank.bila.modelMatrix);
                    isBallVisible = false;
                    pas_pr.x = 0;
                    pas_pr.z = 0;
                    shooting = false;
                    timp_apasare = 0;
                    myTank.bila.modelMatrix = glm::mat3(1);
                    punct = tn;
                    pozitie = {punct.x + myTank.pas.x + pas_pr.x, punct.y + myTank.pas.y + pas_pr.y, punct.z + myTank.pas.z + pas_pr.z};
                    myTank.bila.coord.x = punct.x + myTank.pas.x + pas_pr.x;
                    myTank.bila.coord.y = punct.y;
                    myTank.bila.coord.z = punct.z + myTank.pas.x + pas_pr.z;
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, pozitie);
                    // modelMatrix = glm::scale(modelMatrix, glm::vec3(1,1,1));
                    modelMatrix *= tankTransform;
                    RenderSimpleMesh(myTank.bila.mesh, myTank.bila.shader, myTank.bila.modelMatrix);
                }
                myTank.bila.modelMatrix = glm::translate(myTank.bila.modelMatrix, glm::vec3(pas_pr.x, pas_pr.y, pas_pr.z));
                if (shooting && (timp - timp_apasare >= 0.25f)) {
                    pas_pr.x -= deltaTimeSeconds * cos(myTank.unghi + unghi_turela) * 5;
                    pas_pr.z -= -deltaTimeSeconds * sin(myTank.unghi + unghi_turela) * 5;
                }
            }
        }
        myTank.centru.x = (myTank.corp.coord.x + myTank.cap.coord.y) / 2;
        myTank.centru.y = (myTank.corp.coord.y + myTank.cap.coord.y) / 2;
        myTank.centru.z = (myTank.corp.coord.z + myTank.cap.coord.z) / 2;
    }

    inamic.unghi = glm::radians(90.0f);
    inamic.centru.x += inamic.pas.x * glm::cos(inamic.unghi) * deltaTimeSeconds;
    inamic.centru.y += inamic.pas.y * deltaTimeSeconds;
    inamic.centru.z += inamic.pas.z * glm::sin(inamic.unghi) * deltaTimeSeconds;
    cu_cat.x = -inamic.centru.x;
    cu_cat.y = -inamic.centru.y;
    cu_cat.z = -inamic.centru.z;

    // inamic
    {
        glm::mat4 tankTransform = glm::translate(glm::mat4(1), glm::vec3(inamic.centru.x, inamic.centru.y, inamic.centru.z));
        tankTransform = glm::rotate(tankTransform, inamic.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
        tankTransform = glm::translate(tankTransform, glm::vec3(cu_cat.x, cu_cat.y, cu_cat.z));
        
         // senila1
        {
            punct = isen1;
            // Calculate the new position of senila1
            pozitie = {punct.x + inamic.pas.x, punct.y + inamic.pas.y, punct.z + inamic.pas.z};
            to_ctr = {inamic.centru.x, inamic.centru.y + 0.16f, inamic.centru.z + 0.125f};
            cu_cat = {(-1) * inamic.centru.x + 0.26f, (-1) * inamic.centru.y - 0.16f, (-1) * inamic.centru.z - 0.125f};
            // Apply the transformations to the model matrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::translate(modelMatrix, to_ctr);
            modelMatrix = glm::rotate(modelMatrix, inamic.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, cu_cat);
            // Render senila1
            myPart.coord = punct;
            myPart.mesh = meshes["senila"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            inamic.senila1 = myPart;
            RenderSimpleMesh(inamic.senila1.mesh, inamic.senila1.shader, inamic.senila1.modelMatrix);
        }
        
        // senila2
        {
            punct = isen2;

            // Calculate the new position of senila2
           pozitie = {punct.x + inamic.pas.x, punct.y + inamic.pas.y, punct.z + inamic.pas.z};
           to_ctr = {inamic.centru.x, inamic.centru.y + 0.16f, inamic.centru.z};
           cu_cat = {(-1) * inamic.centru.x - 0.100f, (-1) * inamic.centru.y - 0.16f, (-1) * inamic.centru.z + 0.125f};
            // Apply the transformations to the model matrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::translate(modelMatrix, to_ctr);
            modelMatrix = glm::rotate(modelMatrix, inamic.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, cu_cat);
            // Render senila2
            myPart.coord = punct;
            myPart.mesh = meshes["senila"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            inamic.senila2 = myPart;
            RenderSimpleMesh(inamic.senila2.mesh, inamic.senila2.shader, inamic.senila2.modelMatrix);
        }

        // corp
        {
            punct = icrp;
            pozitie = {punct.x + inamic.pas.x, punct.y + inamic.pas.y, punct.z + inamic.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["corp"];
            myPart.shader = shaders["dpnk"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            inamic.corp = myPart;
            RenderSimpleMesh(inamic.corp.mesh, inamic.corp.shader, inamic.corp.modelMatrix);
        }

        // cap
        {
            punct = icp;
            pozitie = {punct.x + inamic.pas.x, punct.y + inamic.pas.y, punct.z + inamic.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["cap"];
            myPart.shader = shaders["lpnk"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            inamic.cap = myPart;
            RenderSimpleMesh(inamic.cap.mesh, inamic.cap.shader, inamic.cap.modelMatrix);
        }

        //tun
        {
            punct = itn;
            pozitie = {punct.x + inamic.pas.x, punct.y + inamic.pas.y, punct.z + inamic.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["tun"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            inamic.tun = myPart;
            RenderSimpleMesh(inamic.tun.mesh, inamic.tun.shader, inamic.tun.modelMatrix);
        }
        inamic.centru.x = (inamic.corp.coord.x + inamic.cap.coord.y) / 2;
        inamic.centru.y = (inamic.corp.coord.y + inamic.cap.coord.y) / 2;
        inamic.centru.z = (inamic.corp.coord.z + inamic.cap.coord.z) / 2;

        inamic.pas.x += -deltaTimeSeconds * cos(inamic.unghi) / 10;
        inamic.pas.z += deltaTimeSeconds * sin(inamic.unghi) / 10;
    }

    ina.unghi = glm::radians(180.0f);
   ina.centru.x += ina.pas.x * glm::cos(ina.unghi) * deltaTimeSeconds;
    ina.centru.y += ina.pas.y * deltaTimeSeconds;
    ina.centru.z += ina.pas.z * glm::sin(ina.unghi) * deltaTimeSeconds;
    cu_cat.x = -ina.centru.x;
    cu_cat.y = -ina.centru.y;
    cu_cat.z = -ina.centru.z;

    // inamic2
    {
        glm::mat4 tankTransform = glm::translate(glm::mat4(1), glm::vec3(ina.centru.x, ina.centru.y, ina.centru.z));
        tankTransform = glm::rotate(tankTransform, ina.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
        tankTransform = glm::translate(tankTransform, glm::vec3(cu_cat.x, cu_cat.y, cu_cat.z));
        
         // senila1
        {
            punct = insen1;
            // Calculate the new position of senila1
            pozitie = {punct.x + ina.pas.x, punct.y + ina.pas.y, punct.z + ina.pas.z};
            to_ctr = {ina.centru.x, ina.centru.y + 0.16f, ina.centru.z + 0.125f};
            cu_cat = {(-1) * ina.centru.x + 0.26f, (-1) * ina.centru.y - 0.16f, (-1) * ina.centru.z - 0.125f};
            // Apply the transformations to the model matrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::translate(modelMatrix, to_ctr);
            modelMatrix = glm::rotate(modelMatrix, ina.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, cu_cat);
            // Render senila1
            myPart.coord = punct;
            myPart.mesh = meshes["senila"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            ina.senila1 = myPart;
            RenderSimpleMesh(ina.senila1.mesh, ina.senila1.shader, ina.senila1.modelMatrix);
        }
        
        // senila2
        {
            punct = insen2;

            // Calculate the new position of senila2
           pozitie = {punct.x + ina.pas.x, punct.y + ina.pas.y, punct.z + ina.pas.z};
           to_ctr = {ina.centru.x, ina.centru.y + 0.16f, ina.centru.z};
           cu_cat = {(-1) * ina.centru.x - 0.100f, (-1) * ina.centru.y - 0.16f, (-1) * ina.centru.z + 0.125f};
            // Apply the transformations to the model matrix
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix = glm::translate(modelMatrix, to_ctr);
            modelMatrix = glm::rotate(modelMatrix, ina.unghi, glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, cu_cat);
            // Render senila2
            myPart.coord = punct;
            myPart.mesh = meshes["senila"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            ina.senila2 = myPart;
            RenderSimpleMesh(ina.senila2.mesh, ina.senila2.shader, ina.senila2.modelMatrix);
        }

        // corp
        {
            punct = incrp;
            pozitie = {punct.x + ina.pas.x, punct.y + ina.pas.y, punct.z + ina.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["corp"];
            myPart.shader = shaders["movi"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            ina.corp = myPart;
            RenderSimpleMesh(ina.corp.mesh, ina.corp.shader, ina.corp.modelMatrix);
        }

        // cap
        {
            punct = incp;
            pozitie = {punct.x + ina.pas.x, punct.y + ina.pas.y, punct.z + ina.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["cap"];
            myPart.shader = shaders["movd"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            ina.cap = myPart;
            RenderSimpleMesh(ina.cap.mesh, ina.cap.shader, ina.cap.modelMatrix);
        }

        //tun
        {
            punct = intn;
            pozitie = {punct.x + ina.pas.x, punct.y + ina.pas.y, punct.z + ina.pas.z};
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pozitie);
            modelMatrix *= tankTransform;
            myPart.coord = punct;
            myPart.mesh = meshes["tun"];
            myPart.shader = shaders["Alb"];
            myPart.poz = pozitie;
            myPart.modelMatrix = modelMatrix;
            ina.tun = myPart;
            RenderSimpleMesh(ina.tun.mesh, ina.tun.shader, ina.tun.modelMatrix);
        }
        ina.centru.x = (ina.corp.coord.x + inamic.cap.coord.y) / 2;
        ina.centru.y = (ina.corp.coord.y + inamic.cap.coord.y) / 2;
        ina.centru.z = (ina.corp.coord.z + inamic.cap.coord.z) / 2;

        ina.pas.x += -deltaTimeSeconds * cos(ina.unghi) / 5;
        ina.pas.z += deltaTimeSeconds * sin(ina.unghi) / 5;
    }

    if (timp >= 60.0f) {
        exit(0);
    }

     // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        myTank.tun.shader = shaders["Alb"];
        RenderSimpleMesh(myTank.senila2.mesh, shaders["Alb"], myTank.senila2.modelMatrix);
        RenderSimpleMesh(myTank.corp.mesh, shaders["Negru"], myTank.corp.modelMatrix);
        RenderSimpleMesh(myTank.cap.mesh, shaders["GriDeschis"], myTank.cap.modelMatrix);
        RenderSimpleMesh(myTank.tun.mesh, shaders["Alb"], myTank.tun.modelMatrix);
    }
}

void Lab6::FrameEnd()
{
    // DrawCoordinateSystem();
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab6::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location = glGetUniformLocation(shader->GetProgramID(), "Model");
    
    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
    // TODO(student): Get shader location for uniform mat4 "View"
    int viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    
    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    
    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab6::OnInputUpdate(float deltaTime, int mods)
{
   if (!dr)
    {
        if (window->KeyHold(GLFW_KEY_D)) {
            myTank.unghi -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            myTank.unghi += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            myTank.pas.x += deltaTime * cos(myTank.unghi);
            myTank.pas.z += -deltaTime * sin(myTank.unghi);
        }
        if (window->KeyHold(GLFW_KEY_W)) {
            myTank.pas.x += -deltaTime * cos(myTank.unghi);
            myTank.pas.z += deltaTime * sin(myTank.unghi);
        }
   }

   // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODqO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
    if (window->KeyHold(GLFW_KEY_F))
    {
        fov += deltaTime * cameraSpeed;

        if (projectionType)
        {
            projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
        }
    }
    if (window->KeyHold(GLFW_KEY_V))
    {
        fov -= deltaTime * cameraSpeed;

        if (projectionType)
        {
            projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
        }
    }
    }
}

void Lab6::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab6::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab6::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    
    if (!apasat) {
        //float sensivityOX1 = 0.0001f;
        // unghi_turela += sensivityOX1 * -mouseX;
        unghi_turela += deltaX * 0.1f;
    }

     if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
            camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
        }
    }
}


void Lab6::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
         apasat = true;
        isBallVisible = true;
        shooting = true;
        timp_apasare = timp;
    }
    if (button == 2) {
        dr = true;
       apasat = true;
    }
}


void Lab6::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1) {
        apasat = false;
    }
    if (button == 2) {
        dr = false;
    }
}


void Lab6::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab6::OnWindowResize(int width, int height)
{
}
