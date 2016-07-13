#include <OpenNI.h>
#include <iostream>
#include "Viewer.h"

using namespace std;
using namespace openni;

int main(int argc, char *argv[]){
    Status estado=OpenNI::initialize();
    if(estado!=STATUS_OK){
      printf("Fallo de inicialización\n%s\n",OpenNI::getExtendedError());
      return 1;
    }
    printf("Inicializado:\n%s\n", openni::OpenNI::getExtendedError());

    Device kinect;    //Declaración de dispositivo para la kinect
    VideoStream depth,color;  //Flujo de video de profundidad y color
    const char* dispositivoURI = openni::ANY_DEVICE;
    if(argc>1){
      dispositivoURI=argv[1];
    }

    //Inicialización de kinect
    estado=kinect.open(dispositivoURI);
    if(estado != STATUS_OK){
      printf("FAllo al abrir el dispositivo:\n%s\n",OpenNI::getExtendedError());
      OpenNI::shutdown();
      return 1;
    }

    //Inicializa desde el sensor de profundidad un flujo de imágenes
    estado=depth.create(kinect,SENSOR_DEPTH);
    if( estado==STATUS_OK ){
      //Inicia el flujo de profundidad
      estado=depth.start();
      if( estado != STATUS_OK ){
        printf("No se puede iniciar flujo de profundidad:\n%s\n",OpenNI::getExtendedError());
        depth.destroy();
      }
    }
    else{
      printf("No se puede encontrar el flujo de profundidad:\n%s\n",OpenNI::getExtendedError());
    }

    //Inicializa desde el sensor de color un flujo de imágenes
    estado=color.create(kinect,SENSOR_COLOR);
    if(estado==STATUS_OK){
      //Inicia el flujo de color
      estado=color.start();
      if(estado!=STATUS_OK){
        printf("No se puede iniciar el flujo de color:\n%s\n",OpenNI::getExtendedError());
        color.destroy();
      }
    }
    else{
      printf("No se puede encontrar el flujo de color:\n%s\n",OpenNI::getExtendedError());
    }

    if(!depth.isValid() || !color.isValid()){
      printf("Flujos no validos. Saliendo\n");
      OpenNI::shutdown();
      return 2;
    }

    SampleViewer sampleViewer("Kinect", kinect,depth,color);

    estado=sampleViewer.init(argc,argv);
    if(estado!=STATUS_OK){
      OpenNI::shutdown();
      return 3;
    }

    sampleViewer.run();

}
