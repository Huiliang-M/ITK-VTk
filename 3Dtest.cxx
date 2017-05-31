#include "3Dtest.h"
#include "ClippingPlaneMaker.h"
#include "DefaultPipeline.h"
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
using namespace std;
int main(int argc, char **argv) {

    // Define variables
    NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
    ReaderType::Pointer reader = ReaderType::New();

    // Kinda validate input to support both command line input and make debugger use simpler.
    // TODO: Improve checks on input
    if (argc == 4) {
        nameGenerator->SetSeriesFormat(argv[1]);
        nameGenerator->SetStartIndex(std::stoi(argv[2]));
        nameGenerator->SetEndIndex(std::stoi(argv[3]));
    }
    else {
        cout << "USAGE: " << endl;
        cout << "3Dtest.exe <File Path Template> <Start Index> <End Index>" << endl;
        cout << "For example: \n "<< endl;
        cout << "./3Dtest \"C:\\images\\img (%d).tif\" 1 404" << endl;
        cout << "To load files img (1).tif through img (404).tif \n" << endl;
    }

    // Generate file paths for the reader
    nameGenerator->SetIncrementIndex(1);
    std::vector<std::string> filePaths = nameGenerator->GetFileNames();

    // Load slice image files into memory with series reader.
    reader->SetFileNames(filePaths);
    reader->Update();

    // Set up VTK renderer and camera
    vtkRenderer *ren = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    vtkInteractorStyleTrackballCamera *istyle = vtkInteractorStyleTrackballCamera::New();
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(istyle);

    // Create pipelines
    DefaultPipeline regular = DefaultPipeline(reader);
    regular.addToRenderer(ren, iren);

    
	// Render the scene
	ren->SetBackground(0.1, 0.2, 0.4);
	renWin->SetSize(512, 512);
	ren->ResetCamera();
	renWin->Render();
	iren->Start();

	// Clean Up
	iren->Delete();
	ren->Delete();
	renWin->Delete();

	return 0;
}
