/*******************************************************************************
*                                                                              *
*   PrimeSense NiTE 2.0 - User Viewer Sample                                   *
*   Copyright (C) 2012 PrimeSense Ltd.                                         *
*                                                                              *
*******************************************************************************/

#include "Viewer.h"

int main(int argc, char** argv)
{

	//Abre fichero para guardar el seguimiento de la persona

	openni::Status rc = openni::STATUS_OK;

	SampleViewer sampleViewer("User Viewer");
;
	rc = sampleViewer.Init(argc, argv);

	if (rc != openni::STATUS_OK)
	{
		return 1;
	}
	printf("Holi\n");
	sampleViewer.Run();
}
