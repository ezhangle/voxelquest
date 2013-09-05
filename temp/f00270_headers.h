// f00300_singleton.e
//

#ifndef LZZ_f00300_singleton_e
#define LZZ_f00300_singleton_e
#define LZZ_INLINE inline
class Singleton
{
public:
  E_OBJ activeObject;
  bool (keyDownArr) [MAX_KEYS];
  bool wsBufferInvalid;
  fVector4 mouseUpPD;
  fVector4 mouseDownPD;
  fVector4 mouseMovePD;
  fVector4 fActiveObjPos;
  float diskOn;
  GLuint volTris;
  GLuint grassTris;
  vector <string> shaderStrings;
  vector <string> fboStrings;
  vector <string> shaderTextureIDs;
  map <string, Shader*> shaderMap;
  map <string, FBOSet*> fboMap;
  string curShader;
  string allText;
  eProgramState programState;
  eProgramAction (progActionsDown) [E_PS_SIZE*256];
  eProgramAction (progActionsUp) [E_PS_SIZE*256];
  bool isFullScreen;
  int baseW;
  int baseH;
  int iRSize;
  int iPageSize;
  int unitSize;
  iVector3 igwSize;
  int extraRad;
  int defaultWinW;
  int defaultWinH;
  float currentFBOResolutionX;
  float currentFBOResolutionY;
  float mouseX;
  float mouseY;
  float mouseXUp;
  float mouseYUp;
  bool shiftPressed;
  bool ctrlPressed;
  bool altPressed;
  float cameraZoom;
  fVector3 fCameraPos;
  iVector3 iCameraPos;
  fVector3 fLightPos;
  iVector3 iLightPos;
  uint * lookup2to3;
  GLuint lookup2to3ID;
  int shadersAreLoaded;
  int readyToRecompile;
  int iBufferWidth;
  float fBufferWidth;
  bool lbDown;
  bool rbDown;
  bool mbDown;
  float seedX;
  float seedY;
  float seedZ;
  Timer myTimer;
  float curTime;
  float lastTime;
  E_GRASS_STATE grassState;
  float myDelta;
  int frameCount;
  bool changesMade;
  bool bufferInvalid;
  int maxH;
  int screenWidth;
  int screenHeight;
  bool mouseLeftDown;
  bool mouseRightDown;
  bool pboSupported;
  bool notQuit;
  bool timerNotSet;
  GameWorld * gw;
  int lastPosX;
  int lastPosY;
  static void qNormalizeAngle (int & angle);
  void setupLookups ();
  void perspectiveProjection ();
  void orthographicProjection ();
  Singleton ();
  ~ Singleton ();
  float genRand (float LO, float HI);
  void setProgAction (eProgramState ps, unsigned char kc, eProgramAction pa, bool isDown);
  void setProgActionAll (unsigned char kc, eProgramAction pa, bool isDown);
  void keySetup ();
  void createGrassList ();
  void drawCubeCentered (fVector3 origin, float radius);
  void drawBox (fVector3 minVec, fVector3 maxVec);
  void createVTList ();
  void init (int _defaultWinW, int _defaultWinH);
  void doShaderRefresh ();
  void setMatrices (int w, int h);
  void setWH (int w, int h);
  void sampleFBODirect (FBOSet * fbos, int offset = 0);
  void unsampleFBODirect (FBOSet * fbos, int offset = 0);
  void bindFBODirect (FBOSet * fbos);
  void sampleFBO (string fboName, int offset = 0);
  void unsampleFBO (string fboName, int offset = 0);
  FBOWrapper * getFBOWrapper (string fboName, int offset);
  void bindFBO (string fboName);
  void unbindFBO ();
  void bindShader (string shaderName);
  void unbindShader ();
  void setShaderFloat (string paramName, float x);
  void setShaderVec2 (string paramName, float x, float y);
  void setShaderVec3 (string paramName, float x, float y, float z);
  void setShaderfVec3 (string paramName, fVector3 * v);
  void setShaderVec4 (string paramName, float x, float y, float z, float w);
  void setShaderfVec4 (string paramName, fVector4 * v);
  void setShaderTexture (uint texID, int multitexNumber);
  void setShaderTexture3D (uint texID, int multitexNumber);
  void drawFSQuad (float zoom);
  void drawFSQuadOffset (float xOff, float yOff, float zoom);
  void drawFBO (string fboName, int ind, float zoom);
  void drawFBOOffsetDirect (FBOSet * fbos, int ind, float xOff, float yOff, float zoom);
  void drawFBOOffset (string fboName, int ind, float xOff, float yOff, float zoom);
  void moveObject (float dx, float dy, float zoom);
  void doAction (eProgramAction pa);
  void processSpecialKeys (int key, int x, int y);
  void processKey (unsigned char key, int x, int y, bool isPressed);
  void keyboardUp (unsigned char key, int x, int y);
  void keyboardDown (unsigned char key, int x, int y);
  int clamp (int val, int min, int max);
  void getPixData (fVector4 * toVector, int x, int y);
  void mouseMove (int x, int y);
  void worldToScreen (fVector2 * sc, fVector3 * wc);
  void screenToWorld (fVector2 * tc, fVector3 * wc);
  void mouseClick (int button, int state, int x, int y);
  void display ();
  void reshape (int w, int h);
  void idleFunc ();
};
#undef LZZ_INLINE
#endif
// f00350_gamepage.e
//

#ifndef LZZ_f00350_gamepage_e
#define LZZ_f00350_gamepage_e
#define LZZ_INLINE inline
class GamePage : public Poco::Runnable
{
public:
  int iDim;
  iVector3 iOff;
  int iVolumeSize;
  int iRenderSize;
  uint * volData;
  Singleton * singleton;
  FBOSet * fboSet;
  uint volID;
  uint volIDLinear;
  float unitSize;
  E_STATES curState;
  E_STATES nextState;
  fVector3 worldMin;
  fVector3 worldMax;
  E_FILL_STATE fillState;
  GamePage ();
  void init (Singleton * _singleton, int _iDim, iVector3 _iOff, int _iRenderSize);
  uint NumberOfSetBits (uint i);
  uint clamp (uint val);
  float sqrtFast (float x);
  void createSimplexNoise ();
  void copyToTexture ();
  void generateVolume ();
  ~ GamePage ();
  void run ();
};
#undef LZZ_INLINE
#endif
// f00380_gameworld.e
//

#ifndef LZZ_f00380_gameworld_e
#define LZZ_f00380_gameworld_e
#define LZZ_INLINE inline
class GameWorld
{
public:
  int pageCount;
  iVector3 iDim;
  int iPageSize;
  int iVolumeSize;
  int renderRad;
  int loadRad;
  int loadRadZ;
  int ((diagrams) [E_RENDER_LENGTH]) [E_STATE_LENGTH];
  int * curDiagram;
  int renderMethod;
  bool doDrawFBO;
  iVector3 minWithinLR;
  iVector3 maxWithinLR;
  Singleton * singleton;
  GamePage * * worldData;
  int iBufferSize;
  iVector3 origin;
  Poco::ThreadPool threadpool;
  int iRSize;
  GameWorld ();
  bool checkBounds (int i, int j, int k);
  void resetToState (E_STATES resState);
  void init (iVector3 _iDim, Singleton * _singleton, int _renderMethod);
  void update (bool changesMade, bool bufferInvalid, int maxH);
  bool processPages ();
  void renderPages (int maxH);
  void drawPage (GamePage * gp, int dx, int dy, int dz);
  void combineBuffers ();
  void renderGeom ();
  void renderWorldSpace ();
  void renderGrass ();
  void postProcess ();
  ~ GameWorld ();
};
#undef LZZ_INLINE
#endif
 
