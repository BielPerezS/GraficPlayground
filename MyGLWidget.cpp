// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

using namespace std;
#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
  GLenum glErr;
  int retCode = 0;

  glErr = glGetError();
  const char *error = 0;
  switch (glErr)
  {
  case 0x0500:
    error = "GL_INVALID_ENUM";
    break;
  case 0x501:
    error = "GL_INVALID_VALUE";
    break;
  case 0x502:
    error = "GL_INVALID_OPERATION";
    break;
  case 0x503:
    error = "GL_STACK_OVERFLOW";
    break;
  case 0x504:
    error = "GL_STACK_UNDERFLOW";
    break;
  case 0x505:
    error = "GL_OUT_OF_MEMORY";
    break;
  default:
    error = "unknown error!";
  }
  if (glErr != GL_NO_ERROR)
  {
    printf("glError in file %s @ line %d: %s function: %s\n",
           file, line, error, func);
    retCode = 1;
  }
  return retCode;
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::iniEscena()
{
  creaBuffersPatricio();
  creaBuffersAvio();
  creaBuffersHangar();
  creaBuffersSonic();
  creaBuffersTerra();
  creaBuffersTower();
  creaBuffersHand();
  creaBuffersArbre();
  creaBuffersFont();
  creaBuffersGrua();
  creaBuffersMax();
  creaBuffersCruz();
  creaBuffersFarola();
  creaBuffersAcera();
  creaBuffersHouse();

  // Paràmetres de l'escena - arbitraris
  glm::vec3 pmin, pmax;
  pmin = glm::vec3(0, 0, 0);
  pmax = glm::vec3(30, 2.5, 24);

  centreEsc = glm::vec3(pmin + pmax) / 2.0f;
  radiEsc = glm::distance(pmin, pmax) / 2.0f;

  connect(&timer, SIGNAL(timeout()), this, SLOT(animacioAvio()));
  connect(&timerSol, SIGNAL(timeout()), this, SLOT(animacioSol()));
  connect(&timerSalt, SIGNAL(timeout()), this, SLOT(animacioSalt()));
  connect(&timerMans, SIGNAL(timeout()), this, SLOT(animacioMans()));
  timerSol.start(10);
  timerMans.start(refreshRate);
}

void MyGLWidget::paintGL()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  //  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // inicialitzem llum
  enviaPosFocus();

  // Pintem el terra
  glBindVertexArray(VAO_Terra);
  modelTransformTerra(0, 0, 0, 0, 0, 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem les torres
  glBindVertexArray(VAO_Tower);
  modelTransformTower(30, 0, 30);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, Tower.faces().size() * 3);

  glBindVertexArray(VAO_Tower);
  modelTransformTower(30, 0, -30);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, Tower.faces().size() * 3);

  glBindVertexArray(VAO_Tower);
  modelTransformTower(-30, 0, 30);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, Tower.faces().size() * 3);

  glBindVertexArray(VAO_Tower);
  modelTransformTower(-30, 0, -30);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, Tower.faces().size() * 3);
  // Pintem les mans
  // mans plaza//------------------------------------------------------------------------------------------------
  glBindVertexArray(VAO_Hand);
  modelTransformHand2(0, glm::radians(angleMans - 135.f), 0, 3, -2.5, 0);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand2(0, glm::radians(angleMans + 135.f), 0, 3, -2.5, 0);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand2(0, glm::radians(angleMans - 45.f), 0, 3, -2.5, 0);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand2(0, glm::radians(angleMans + 45.f), 0, 3, -2.5, 0);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);
  //------------------------------------------------------------------------------------------------
  // 1
  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, -M_PI / 2, 0, -25.5, 0, 30);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, 0, 0, -30, 0, 25.5);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);
  // 2
  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, M_PI / 2, 0, 25.5, 0, 30);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, 0, 0, 30, 0, 25.5);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);
  // 3
  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, M_PI / 2, 0, 25.5, 0, -30);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, M_PI, 0, 30, 0, -25.5);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);
  // 4
  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, -M_PI / 2, 0, -25.5, 0, -30);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  glBindVertexArray(VAO_Hand);
  modelTransformHand(M_PI / 3, M_PI, 0, -30, 0, -25.5);
  glDrawArrays(GL_TRIANGLES, 0, Hand.faces().size() * 3);

  // Pintem Arbre's
  glBindVertexArray(VAO_Arbre);
  modelTransformArbre(0, 0, 0, 0, 0, -10, 7);
  glDrawArrays(GL_TRIANGLES, 0, Arbre.faces().size() * 3);

  glBindVertexArray(VAO_Arbre);
  modelTransformArbre(0, 0, 0, 0, 0, 10, 7);
  glDrawArrays(GL_TRIANGLES, 0, Arbre.faces().size() * 3);

  glBindVertexArray(VAO_Arbre);
  modelTransformArbre(0, 0, 0, 10, 0, 0, 7);
  glDrawArrays(GL_TRIANGLES, 0, Arbre.faces().size() * 3);

  glBindVertexArray(VAO_Arbre);
  modelTransformArbre(0, 0, 0, -10, 0, 0, 7);
  glDrawArrays(GL_TRIANGLES, 0, Arbre.faces().size() * 3);

  // Pintem Font
  glBindVertexArray(VAO_Font);
  modelTransformFont(0, 0, 0, 0, 0, 0, 4);
  glDrawArrays(GL_TRIANGLES, 0, Font.faces().size() * 3);

  // Pintem el Patricio
  glBindVertexArray(VAO_Patr);
  modelTransformPatricio();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);

  // Pintem l'Avio
  glBindVertexArray(VAO_Avio);
  modelTransformAvio();
  glDrawArrays(GL_TRIANGLES, 0, avio.faces().size() * 3);

  glBindVertexArray(VAO_Sonic);
  modelTransformSonic();
  glDrawArrays(GL_TRIANGLES, 0, sonic.faces().size() * 3);

  // Pintem l'Hangar
  glBindVertexArray(VAO_Hang);
  modelTransformHangar();
  glDrawArrays(GL_TRIANGLES, 0, hang.faces().size() * 3);

  // Pintem Grua
  glBindVertexArray(VAO_Grua);
  modelTransformGrua(0, 0, 0, -30, 0, -3, 35);
  glDrawArrays(GL_TRIANGLES, 0, Grua.faces().size() * 3);

  // Pintem Max
  glBindVertexArray(VAO_Max);
  modelTransformMax(0, 0, 0, 3.5, 0, 3.5, 1);
  glDrawArrays(GL_TRIANGLES, 0, Max.faces().size() * 3);

  // Pintem Cruz

  // he añadido patricio? para que se vean las cruces con el patricio como el centro, va raro aun... FIXME
  glBindVertexArray(VAO_Cruz);
  modelTransformCruz(M_PI / 4, 0, 0, patricioX, patricioY + 90, patricioZ - 90, 20);
  glDrawArrays(GL_TRIANGLES, 0, Cruz.faces().size() * 3);

  glBindVertexArray(VAO_Cruz);
  modelTransformCruz(-M_PI / 4, M_PI, 0, patricioX, patricioY + 90, patricioZ + 90, 20);
  glDrawArrays(GL_TRIANGLES, 0, Cruz.faces().size() * 3);

  glBindVertexArray(VAO_Cruz);
  modelTransformCruz(0, -M_PI / 2, M_PI / 4, patricioX + 90, patricioY + 90, patricioZ, 20);
  glDrawArrays(GL_TRIANGLES, 0, Cruz.faces().size() * 3);

  glBindVertexArray(VAO_Cruz);
  modelTransformCruz(0, M_PI / 2, -M_PI / 4, patricioX - 90, patricioY + 90, patricioZ, 20);
  glDrawArrays(GL_TRIANGLES, 0, Cruz.faces().size() * 3);

  // Pintem Acera
  glBindVertexArray(VAO_Acera);
  modelTransformAcera(2, 1, 8, 0, -3.9, 21, 0);
  glDrawArrays(GL_TRIANGLES, 0, Acera.faces().size() * 3);

  glBindVertexArray(VAO_Acera);
  modelTransformAcera(2, 1, 8, 0, -3.9, -21, M_PI);
  glDrawArrays(GL_TRIANGLES, 0, Acera.faces().size() * 3);

  glBindVertexArray(VAO_Acera);
  modelTransformAcera(2, 1, 8, 21, -3.9, 0, M_PI / 2);
  glDrawArrays(GL_TRIANGLES, 0, Acera.faces().size() * 3);

  glBindVertexArray(VAO_Acera);
  modelTransformAcera(2, 1, 8, -21, -3.9, 0, -M_PI / 2);
  glDrawArrays(GL_TRIANGLES, 0, Acera.faces().size() * 3);

  // Pintem House
  glBindVertexArray(VAO_House);
  modelTransformHouse(0, glm::radians(0.f), 0, 20, 0, -10, 10);
  glDrawArrays(GL_TRIANGLES, 0, House.faces().size() * 3);

  glBindVertexArray(VAO_House);
  modelTransformHouse(0, glm::radians(-90.f), 0, 10, 0, -20, 10);
  glDrawArrays(GL_TRIANGLES, 0, House.faces().size() * 3);

  // Pintem Farolas
  for (int i = -25; i < 30; i += 10)
  {
    if (i != 0 && i != 5 && i != -5)
    {
      glBindVertexArray(VAO_Farola);
      modelTransformFarola(0, 0, 0, i, 0, -4, 5);
      glDrawArrays(GL_TRIANGLES, 0, Farola.faces().size() * 3);

      glBindVertexArray(VAO_Farola);
      modelTransformFarola(0, 0, 0, i, 0, 4, 5);
      glDrawArrays(GL_TRIANGLES, 0, Farola.faces().size() * 3);

      glBindVertexArray(VAO_Farola);
      modelTransformFarola(0, 0, 0, -4, 0, i, 5);
      glDrawArrays(GL_TRIANGLES, 0, Farola.faces().size() * 3);

      glBindVertexArray(VAO_Farola);
      modelTransformFarola(0, 0, 0, 4, 0, i, 5);
      glDrawArrays(GL_TRIANGLES, 0, Farola.faces().size() * 3);
    }
  }
  glBindVertexArray(0);
}

void MyGLWidget::iniMaterialTerra()
{
  // Donem valors al material del terra
  amb = glm::vec3(0, 0, 0);  // color  ----------
  diff = glm::vec3(1, 1, 1); // color +++++++++++
  spec = glm::vec3(1, 1, 1); // brillo
  shin = 250;                // mida de la taca especular
}

void MyGLWidget::enviaPosFocus()
{
  if (!focusModel)
  {
    // modo cmaara
    /*
    posFoc = glm::vec3(0, 0, 0);
   */
    posFoc = glm::vec3(View * glm::vec4(0, alturaSol, 0, 1));
   
    glUniform3fv(posfocusLoc, 1, &posFoc[0]);
  }
  else
  {
    float x = (capsaAvioMax.x + capsaAvioMin.x) / 2.0f;
    float y = (capsaAvioMax.y + capsaAvioMin.y) / 2.0f;
    float z = capsaAvioMin.z;


    posFoc = glm::vec3(View * TGAvio * glm::vec4(x, y, z, 1));

    glUniform3fv(posfocusLoc, 1, &posFoc[0]);
  }
}

void MyGLWidget::iniCamera()
{
  timerON = false;
  anglePatricio = 0;
  angleY = 0.5;
  angleX = -0.5;
  camera2 = false;
  ra = float(width()) / height();
  fov = float(M_PI / 3.0);
  // float alfa = asin(radiEsc/(2*radiEsc));
  // fov = 2*alfa;
  zn = 0.01f;
  zf = 10 * radiEsc;

  OBS = glm::vec3(patricioX, 1, patricioZ);
  VRP = glm::vec3(100 * sin((anglePatricio - 8) * saltsAngle), 1, 100 * cos(anglePatricio));
  UP = glm::vec3(0, 1, 0);

  fov2 = float(M_PI / 2.0f);
  zn2 = 0.3f;
  zf2 = 10 * radiEsc;

  alturaAvio = 0.0f;
  angleAvio = 0.0f;

  focusModel = false;

  projectTransform();
  viewTransform();
}

void MyGLWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(lila[0], lila[1], lila[2], lila[3]); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  iniEscena();
  iniCamera();
}

void MyGLWidget::modelTransformHouse(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(scale * escalaHouse, scale * escalaHouse, scale * escalaHouse));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAcera(float anchoX, float anchoY, float anchoZ, float x, float y, float z, float angleY)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(anchoX * 4 * escalaAcera, anchoY * 4 * escalaAcera, anchoZ * 4 * escalaAcera));
  TG = glm::translate(TG, -centreBaseAcera);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCruz(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);

  TG = glm::translate(TG, glm::vec3(x, y, z));

  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));

  TG = glm::scale(TG, glm::vec3(scale * escalaMax, scale * escalaMax, scale * escalaMax));
  TG = glm::translate(TG, -centreBaseCruz);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformMax(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(scale * escalaMax / 1.5, scale * escalaMax / 1.5, scale * escalaMax / 1.5));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformFarola(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TGFarola(1.f);
  TGFarola = glm::translate(TGFarola, glm::vec3(x, y, z));
  TGFarola = glm::rotate(TGFarola, angleZ, glm::vec3(0, 0, 1));
  TGFarola = glm::rotate(TGFarola, angleY, glm::vec3(0, 1, 0));
  TGFarola = glm::rotate(TGFarola, angleX, glm::vec3(1, 0, 0));
  TGFarola = glm::scale(TGFarola, glm::vec3(scale * escalaFarola, scale * escalaFarola, scale * escalaFarola));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TGFarola[0][0]);
}

void MyGLWidget::modelTransformFont(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(scale * escalaFont, scale * escalaFont * 0.35, scale * escalaFont));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformArbre(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);
  TG = glm::rotate(TG, float(M_PI / 4), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(scale * escalaArbre, scale * escalaArbre, scale * escalaArbre));

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformHand2(float angleX, float angleY, float angleZ, float x, float y, float z)
{
  glm::mat4 TG(1.f);

  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, float(-M_PI / 2), glm::vec3(0, 1, 0));

  TG = glm::scale(TG, glm::vec3(4 * escalaHand, 4 * escalaHand, 4 * escalaHand));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformHand(float angleX, float angleY, float angleZ, float x, float y, float z)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));

  TG = glm::scale(TG, glm::vec3(4 * escalaHand, 4 * escalaHand, 4 * escalaHand));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTower(float x, float y, float z)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::scale(TG, glm::vec3(30 * escalaTower, 30 * escalaTower, 30 * escalaTower));
  TG = glm::translate(TG, -centreBaseTower);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra(float angleX, float angleY, float angleZ, float x, float y, float z)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformGrua(float angleX, float angleY, float angleZ, float x, float y, float z, int scale)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, angleZ, glm::vec3(0, 0, 1));
  TG = glm::rotate(TG, angleY, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, angleX, glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(scale * escalaGrua, scale * escalaGrua, scale * escalaGrua));

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformSonic()
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(0, alturaSol, 0));
  TG = glm::rotate(TG, (saltsAngle / 5) * factorSol, glm::vec3(1.5, 2, 0.5));
  TG = glm::scale(TG, glm::vec3(7 * escalaSonic, 7 * escalaSonic, 7 * escalaSonic));
  TG = glm::translate(TG, -centreBaseSonic);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio()
{
  glm::mat4 TG(1.f);
  if (!PatricioAvionador)
  {
    TG = glm::translate(TG, glm::vec3(patricioX, patricioY, patricioZ));
    TG = glm::rotate(TG, float(anglePatricio * saltsAngle), glm::vec3(0, 1, 0));
  }
  else
  {
    TG = glm::translate(TG, glm::vec3(0, alturaAvio, 0));
    TG = glm::translate(TG, glm::vec3(25 - 10, 0, 12));

    TG = glm::rotate(TG, angleAvio, glm::vec3(0, 1, 0));
    // distancia entre avio i patricio
    TG = glm::translate(TG, glm::vec3(10, 0, 0));
  }
  int factor = 1;
  TG = glm::scale(TG, glm::vec3(factor * escalaPat, factor * escalaPat, factor * escalaPat));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAvio()
{
  TGAvio = glm::mat4(1.f);
  TGAvio = glm::translate(TGAvio, glm::vec3(0, alturaAvio, 0));
  TGAvio = glm::translate(TGAvio, glm::vec3(25 - 10, 0, 12));

  TGAvio = glm::rotate(TGAvio, angleAvio, glm::vec3(0, 1, 0));
  // distancia entre avio i patricio
  TGAvio = glm::translate(TGAvio, glm::vec3(10, 0, 0));

  TGAvio = glm::scale(TGAvio, glm::vec3(1.5 * escalaAvio, 1.5 * escalaAvio, 1.5 * escalaAvio));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TGAvio[0][0]);
}

void MyGLWidget::viewTransform()
{
  if (!camera2)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -3 * radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -glm::vec3(0, 0, 0));

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else
  {
    View = glm::mat4(1.f);
    if (!PatricioAvionador)
    {

      OBS = glm::vec3(patricioX, patricioY + 0.75, patricioZ);
      VRP = glm::vec3(1000 * sin((anglePatricio)*saltsAngle), 1000 * sin((anglePatricioY)*saltsAngle), 1000 * cos((anglePatricio)*saltsAngle));
    }
    else
    {
      float x = (capsaAvioMax.x + capsaAvioMin.x) / 2.0f;
      float y = ((capsaAvioMax.y + capsaAvioMin.y) / 2.0f) + 0.5f;
      float z = (capsaAvioMin.z + capsaAvioMax.z) / 2.0f;
      OBS = glm::vec3(View * TGAvio * glm::vec4(x, y + 0.5, z, 1));
      VRP = glm::vec3(View * TGAvio * glm::vec4(x - avionadorX, y - avionadorY, capsaAvioMax.z, 1));
    }
    View = glm::lookAt(OBS, VRP, UP);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform()
{
  if (!camera2)
  {
    glm::mat4 Proj; // Matriu de projecció
    Proj = glm::perspective(fov, ra, zn, zf);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
  else
  {
    glm::mat4 Proj; // Matriu de projecció
    Proj = glm::perspective(fov2, ra, zn2, zf2);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  // CANVIAR VELOCITAT
  case Qt::Key_Shift:
  {
    correr = !correr;
    break;
  }
  // LES FLECHES S'usen PER MOURE LA CAMARA DEL PATRICIO QUANT ESTA VIATJANT en l'avio
  case Qt::Key_Up:
  {
    if (PatricioAvionador)
      --avionadorY;
    if (alturaAvio < 5)
      alturaAvio += 1;
    modelTransformAvio();

    emit signalAltura(alturaAvio);
    break;
  }
  case Qt::Key_Down:
  {
    if (PatricioAvionador)
      ++avionadorY;
    if (alturaAvio > 0 && !timerON)
      alturaAvio -= 1;
    modelTransformAvio();

    emit signalAltura(alturaAvio);
    break;
  }
  // EL AVIO ES MOU EN ORBITES
  case Qt::Key_T:
  {
    timerON = !timerON;
    if (timerON)
      timer.start(10);
    else
      timer.stop();

    cout << timerON << endl;

    break;
  }
  case Qt::Key_U:
  {
    if (!timerON)
    {
      angleAvio -= float((2 * M_PI) / 32.f);
      viewTransform();
      modelTransformAvio();
    }
    break;
  }
  // ILUMINACIO AVIO-ESCENA
  case Qt::Key_F:
  {
    focusModel = !focusModel;
    enviaPosFocus();
    break;
  }
  // CANVI CAMARA FPS O GLOBAL
  case Qt::Key_C:
  {
    camera2 = !camera2;
    viewTransform();
    projectTransform();

    emit signalCam(camera2);
    break;
  }
  case Qt::Key_R:
  {
    // ExamGLWidget::initializeGL();
    iniCamera();
    timer.stop();
    emit signalCam(false);
    emit signalAltura(0);
    break;
  }
  // MOURE PATRICIO
  case Qt::Key_W:
  {
    /*
    float sumaZ = patricioZ + speed * cos(anglePatricio * saltsAngle),
          sumaX = patricioX + speed * sin(anglePatricio * saltsAngle);
*/
    int factorCorrer = 1;
    if (correr)
      factorCorrer = 5;

    patricioZ += factorCorrer * speed * cos(anglePatricio * saltsAngle);
    patricioX += factorCorrer * speed * sin(anglePatricio * saltsAngle);

    modelTransformPatricio();
    viewTransform();
    projectTransform();
    break;
  }
  case Qt::Key_A:
  {
    /*
    float sumaZ = patricioZ + speed * cos(anglePatricio * saltsAngle + M_PI / 2),
          sumaX = patricioX + speed * sin(anglePatricio * saltsAngle + M_PI / 2);
*/

    patricioZ += speed * cos(anglePatricio * saltsAngle + M_PI / 2);
    patricioX += speed * sin(anglePatricio * saltsAngle + M_PI / 2);

    modelTransformPatricio();
    viewTransform();
    projectTransform();

    break;
  }
  case Qt::Key_S:
  {
    /*
    float sumaZ = patricioZ - speed * cos(anglePatricio * saltsAngle),
          sumaX = patricioX - speed * sin(anglePatricio * saltsAngle);
*/

    patricioZ -= speed * cos(anglePatricio * saltsAngle);
    patricioX -= speed * sin(anglePatricio * saltsAngle);

    modelTransformPatricio();
    viewTransform();
    projectTransform();

    break;
  }
  case Qt::Key_D:
  {
    /*
    float sumaZ = patricioZ + speed * cos(anglePatricio * saltsAngle - M_PI / 2),
          sumaX = patricioX + speed * sin(anglePatricio * saltsAngle - M_PI / 2);
*/

    patricioZ += speed * cos(anglePatricio * saltsAngle - M_PI / 2);
    patricioX += speed * sin(anglePatricio * saltsAngle - M_PI / 2);

    modelTransformPatricio();
    viewTransform();
    projectTransform();

    break;
  }
  // PATRICIO MONTA AVIO!
  case Qt::Key_E:
  {
    PatricioAvionador = !PatricioAvionador;
    modelTransformPatricio();
    viewTransform();
    break;
  }

  case Qt::Key_Right:
  {
    if (PatricioAvionador)
      ++avionadorX;
    anglePatricio -= 1;
    modelTransformPatricio();
    viewTransform();
    break;
  }

  case Qt::Key_Left:
  {
    if (PatricioAvionador)
      --avionadorX;
    anglePatricio += 1;
    modelTransformPatricio();
    viewTransform();
    break;
  }

  case Qt::Key_Space:
  {
    if (!timerSaltON)
    {
      timerSaltON = true;
      copsCridat = 0;
      // refreshRate set at 16.67 so its 60fps
      timerSalt.start(refreshRate);
    }
    break;
  }

  case Qt::Key_H:
  {

    posFoc = glm::vec3(View * TGFarola * glm::vec4(0, 0, 0, 1));
    glUniform3fv(posfocusLoc, 1, &posFoc[0]);

    break;
  }

  default:
    ExamGLWidget::keyPressEvent(event);
    break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE))
  {
    // Fem la rotació
    if (!camera2)
    {
      angleY += (e->x() - xClick) * M_PI / ample;
      angleX -= (e->y() - yClick) * M_PI / alt;
    }

    if (camera2)
    {
      if (!PatricioAvionador)
      {
        anglePatricio -= DPI * (e->x() - xClick) * M_PI / ample;
        int newpatricioY = anglePatricioY - DPI * (e->y() - yClick) * M_PI / alt;
        // limites camaraY
        if (newpatricioY > -8 && newpatricioY < 8)
          anglePatricioY -= 0.5 * DPI * (e->y() - yClick) * M_PI / alt;

        cout << " angelPatricioY " << anglePatricioY << endl;
      }
      else
      {
        // NO VA
        avionadorY = 4 * (e->y() - yClick) * M_PI / alt;
        avionadorX = 4 * (e->x() - xClick) * M_PI / ample;
      }
    }

    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      !(e->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::canviCamara(bool c)
{
  makeCurrent();
  camera2 = c;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::canviAltura(int a)
{
  makeCurrent();
  alturaAvio = a;
  modelTransformAvio();
  update();
}

void MyGLWidget::animacioAvio()
{
  makeCurrent();
  angleAvio -= float((2 * M_PI) / 360.f);
  alturaAvio = 5;
  modelTransformAvio();
  viewTransform();
  emit signalAltura(5);

  update();
}

void MyGLWidget::animacioSol()
{
  makeCurrent();
  factorSol += 1;
  modelTransformSonic();
  viewTransform();
  update();
}

void MyGLWidget::animacioSalt()
{
  makeCurrent();
  copsCridat += 1;
  int endCall = FPS * timeJump;
  if (copsCridat == endCall)
  {
    copsCridat = 0;
    timerSaltON = false;
    timerSalt.stop();
  }
  else
  {
    patricioY = alturaSalt * sin(copsCridat * M_PI / endCall);
  }
  update();
}

void MyGLWidget::animacioMans()
{
  makeCurrent();
  angleMans += 2;
  update();
}

void MyGLWidget::creaBuffersSonic()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  sonic.load("./models/FakeSonicHigh.obj");
  // sonic.load("./models/TexturesSonic/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, sonic, escalaSonic, centreBaseSonic);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Sonic);
  glBindVertexArray(VAO_Sonic);

  // Creació dels buffers del model patr
  GLuint VBO_Sonic[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Sonic);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3 * 3, sonic.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3 * 3, sonic.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3 * 3, sonic.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3 * 3, sonic.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3 * 3, sonic.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Sonic[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sonic.faces().size() * 3, sonic.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersArbre()
{

  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Arbre.load("./models/firTree.obj");
  // Arbre.load("./models/TexturesArbre/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Arbre, escalaArbre, centreBaseArbre);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Arbre);
  glBindVertexArray(VAO_Arbre);

  // Creació dels buffers del model patr
  GLuint VBO_Arbre[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Arbre);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3 * 3, Arbre.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3 * 3, Arbre.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3 * 3, Arbre.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3 * 3, Arbre.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3 * 3, Arbre.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Arbre[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Arbre.faces().size() * 3, Arbre.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersHand()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Hand.load("./models/creepyhand.obj");
  // Hand.load("./models/TexturesHand/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Hand, escalaHand, centreBaseHand);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Hand);
  glBindVertexArray(VAO_Hand);

  // Creació dels buffers del model patr
  GLuint VBO_Hand[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Hand);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3 * 3, Hand.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3 * 3, Hand.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3 * 3, Hand.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3 * 3, Hand.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3 * 3, Hand.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Hand[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Hand.faces().size() * 3, Hand.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersFont()
{

  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Font.load("./models/dragonfountain.obj");
  // Font.load("./models/TexturesFont/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Font, escalaFont, centreBaseFont);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Font);
  glBindVertexArray(VAO_Font);

  // Creació dels buffers del model patr
  GLuint VBO_Font[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Font);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3 * 3, Font.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3 * 3, Font.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3 * 3, Font.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3 * 3, Font.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3 * 3, Font.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Font[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Font.faces().size() * 3, Font.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersGrua()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Grua.load("./models/Build01_Sm.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Grua, escalaGrua, centreBaseGrua);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Grua);
  glBindVertexArray(VAO_Grua);

  // Creació dels buffers del model patr
  GLuint VBO_Grua[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Grua);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3 * 3, Grua.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3 * 3, Grua.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3 * 3, Grua.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3 * 3, Grua.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3 * 3, Grua.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Grua[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Grua.faces().size() * 3, Grua.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersMax()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Max.load("./models/max.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Max, escalaMax, centreBaseMax);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Max);
  glBindVertexArray(VAO_Max);

  // Creació dels buffers del model patr
  GLuint VBO_Max[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Max);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3 * 3, Max.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3 * 3, Max.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3 * 3, Max.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3 * 3, Max.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3 * 3, Max.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Max[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Max.faces().size() * 3, Max.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersCruz()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Cruz.load("./models/savecross.obj");
  // Cruz.load("./models/TexturesCruz/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Cruz, escalaCruz, centreBaseCruz);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Cruz);
  glBindVertexArray(VAO_Cruz);

  // Creació dels buffers del model patr
  GLuint VBO_Cruz[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Cruz);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3 * 3, Cruz.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3 * 3, Cruz.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3 * 3, Cruz.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3 * 3, Cruz.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3 * 3, Cruz.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cruz[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Cruz.faces().size() * 3, Cruz.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersFarola()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Farola.load("./models/streetclock.obj");
  // Farola.load("./models/TexturesFarola/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Farola, escalaFarola, centreBaseFarola);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Farola);
  glBindVertexArray(VAO_Farola);

  // Creació dels buffers del model patr
  GLuint VBO_Farola[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Farola);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3 * 3, Farola.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3 * 3, Farola.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3 * 3, Farola.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3 * 3, Farola.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3 * 3, Farola.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Farola[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Farola.faces().size() * 3, Farola.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersTower()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Tower.load("./models/Building_M.obj");
  // Tower.load("./models/TexturesTower/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Tower, escalaTower, centreBaseTower);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Tower);
  glBindVertexArray(VAO_Tower);

  // Creació dels buffers del model patr
  GLuint VBO_Tower[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Tower);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3 * 3, Tower.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3 * 3, Tower.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3 * 3, Tower.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3 * 3, Tower.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3 * 3, Tower.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tower[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Tower.faces().size() * 3, Tower.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersHouse()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  House.load("./models/Monster House.obj");
  // House.load("./models/TexturesHouse/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, House, escalaHouse, centreBaseHouse);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_House);
  glBindVertexArray(VAO_House);

  // Creació dels buffers del model patr
  GLuint VBO_House[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_House);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3 * 3, House.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3 * 3, House.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3 * 3, House.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3 * 3, House.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3 * 3, House.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * House.faces().size() * 3, House.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersAcera()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  Acera.load("./models/VideoCamera.obj");
  // Acera.load("./models/TexturesAcera/env_fake_s.png");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(false, Acera, escalaAcera, centreBaseAcera);

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Acera);
  glBindVertexArray(VAO_Acera);

  // Creació dels buffers del model patr
  GLuint VBO_Acera[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Acera);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3 * 3, Acera.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3 * 3, Acera.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3 * 3, Acera.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3 * 3, Acera.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3 * 3, Acera.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Acera[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Acera.faces().size() * 3, Acera.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}