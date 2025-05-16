#include "ExamGLWidget.h"
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
#include <QTimer>

class MyGLWidget : public ExamGLWidget
{
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent = 0) : ExamGLWidget(parent) {}
  ~MyGLWidget();

  // variables varies-----------------------------------------------------------------------------------

  glm::mat4 TGFarola;

  int tmp = 0;

  float patricioX = 15, patricioZ = 12, patricioY = 0;
  float anglePatricio, anglePatricioY = 1;

  float saltsAngle = M_PI * 2 / 32;
  
  float avionadorX, avionadorY = 0;
  float angleAvio;
  int alturaAvio;

  double DPI = 10;
  double speed = 0.1;
  
  float alturaSol = 20;

  float refreshRate = 16.66666666666667;
  float FPS = 1000/refreshRate;
  
  //glm::vec4 lila = //glm::vec4(0.4, 0.0, 1, 0);
  //glm::vec4 black = //glm::vec4(0.0, 0.0, 0.0, 0);
  //glm::vec4 white = //glm::vec4(1.0, 1.0, 1.0, 0);

  vector<double> lila = {0.4, 0.0, 1, 0};
  vector<double> black = {0.0, 0.0, 0.0, 0};
  vector<double> white = {0.7, 0.7, 0.7, 0};  
  vector<double> blue = {0.2, 0.0, 0.84, 0};

  //bool's-----------------------------------------------------------------------------------
  
  bool correr = false;
  bool focusModel;
  bool PatricioAvionador = false;

  //Parmaetres camara Patricio-----------------------------------------------------------------------------------
  glm::vec3 OBS, VRP, UP;
  float fov2, zn2, zf2;

  // Timers-----------------------------------------------------------------------------------

  QTimer timer;
  bool timerON = true;

  QTimer timerSol;
  bool timerSolON = true;
  float factorSol = 1;

  QTimer timerSalt;
  bool timerSaltON = false;
  int copsCridat = 0;
  int timeJump = 1;
  int alturaSalt = 2;

  QTimer timerMans;
  bool timerMansON = true;
  int angleMans = 0;
  


  // Models-----------------------------------------------------------------------------------
  Model Font;
  float escalaFont;
  glm::vec3 centreBaseFont;
  GLuint VAO_Font;

  Model Arbre;
  float escalaArbre;
  glm::vec3 centreBaseArbre;
  GLuint VAO_Arbre;

  Model sonic;
  float escalaSonic;
  glm::vec3 centreBaseSonic;
  GLuint VAO_Sonic;

  Model Hand;
  float escalaHand;
  glm::vec3 centreBaseHand;
  GLuint VAO_Hand;

  Model Tower;
  float escalaTower;
  glm::vec3 centreBaseTower;
  GLuint VAO_Tower;

  Model Grua;
  float escalaGrua;
  glm::vec3 centreBaseGrua;;
  GLuint VAO_Grua;

  Model Max;
  float escalaMax;
  glm::vec3 centreBaseMax;;
  GLuint VAO_Max;

  Model Cruz;
  float escalaCruz;
  glm::vec3 centreBaseCruz;;
  GLuint VAO_Cruz;

  Model Farola;
  float escalaFarola;
  glm::vec3 centreBaseFarola;;
  GLuint VAO_Farola;

  Model Acera;
  float escalaAcera;
  glm::vec3 centreBaseAcera;;
  GLuint VAO_Acera;

  Model House;
  float escalaHouse;
  glm::vec3 centreBaseHouse;;
  GLuint VAO_House;


protected:
  virtual void paintGL();
  
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mousePressEvent(QMouseEvent *e);
  virtual void mouseReleaseEvent(QMouseEvent *);

  virtual void modelTransformTerra(float angleX, float angleY, float angleZ, float x, float y, float z);
  virtual void modelTransformPatricio();
  virtual void modelTransformAvio();

  virtual void initializeGL();
  virtual void iniEscena();
  virtual void iniCamera();
  virtual void iniMaterialTerra();
  
  virtual void projectTransform();
  virtual void viewTransform();
  
  virtual void enviaPosFocus();

  //Models extres----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  virtual void modelTransformSonic();
  void creaBuffersSonic();

  virtual void modelTransformTower(float x, float y, float z);
  void creaBuffersTower();

  virtual void modelTransformHand(float angleX, float angleY, float angleZ, float x, float y, float z);
  virtual void modelTransformHand2(float angleX, float angleY, float angleZ, float x, float y, float z);
  void creaBuffersHand();

  virtual void modelTransformArbre(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersArbre();

  virtual void modelTransformFont(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersFont();

  virtual void modelTransformGrua(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersGrua();

  virtual void modelTransformMax(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersMax();

  virtual void modelTransformCruz(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersCruz();

  virtual void modelTransformFarola(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersFarola();

  virtual void modelTransformAcera(float anchoX, float anchoY, float anchoZ, float x, float y, float z, float angleY);
  void creaBuffersAcera();

  virtual void modelTransformHouse(float angleX, float angleY, float angleZ, float x, float y, float z, int scale);
  void creaBuffersHouse();

private:
  int printOglError(const char file[], int line, const char func[]);

public slots:
  void canviCamara(bool c);
  void canviAltura(int a);
  void animacioAvio();
  void animacioSol();
  void animacioSalt();
  void animacioMans();

signals:
  void signalCam(bool c);
  void signalAltura(int a);
};
