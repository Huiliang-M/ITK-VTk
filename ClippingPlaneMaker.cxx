#include "ClippingPlaneMaker.h"
#include <vtkPlaneWidget.h>
#include <vtkPlanes.h>

// These vectors should always be parallel.
std::vector<vtkPlaneWidget*> ClippingPlaneMaker::planeWidgets;
std::vector<vtkPlane*> ClippingPlaneMaker::planes;

vtkPlaneWidget* ClippingPlaneMaker::AddClippingPlane(vtkRenderWindowInteractor *iren, vtkProp3D* prop, MapperType *mapper) {
	// Set up a clipping plane widget
	cout << planeWidgets.empty() << " -> " << planeWidgets.size() << " " << endl;
	vtkPlaneWidget *widget = vtkPlaneWidget::New();
	widget->SetInteractor(iren);
	widget->SetPlaceFactor(1.25);
	widget->SetProp3D(prop);
	widget->PlaceWidget();
	widget->On();


	// Store the widget and plane separately.
	// This is necessary so the plane can be removed from the mapper later.
	planeWidgets.push_back(widget);
	vtkPlane *plane = vtkPlane::New();
	widget->GetPlane(plane);
	planes.push_back(plane);
	return widget;
};

bool ClippingPlaneMaker::RemoveClippingPlane(vtkPlaneWidget *plane, MapperType *mapper) {
	cout << planeWidgets.empty() << " -> " << planeWidgets.size() << " " << endl;
	std::vector<vtkPlaneWidget*>::iterator itWidgets;
	std::vector<vtkPlane*>::iterator itPlanes;

	vtkPlaneWidget *targetPlane = plane;

	for (itWidgets = planeWidgets.begin(), itPlanes = planes.begin(); itWidgets != planeWidgets.end(); itWidgets++, itPlanes++) {
		vtkPlaneWidget *curPlane = *itWidgets;
		std::cout << curPlane << " < - > " << targetPlane << std::endl;

		if (curPlane == targetPlane) {
			(*itWidgets)->Off();
			mapper->RemoveClippingPlane(*itPlanes);
			(*itWidgets)->Delete();
			planeWidgets.erase(itWidgets);
			planes.erase(itPlanes);

			// TODO: Figure out a better way to do this!
			// A hack to get the mapper to actually stop using the clipping plane
			// We can reuse itPlanes because we're guaranteed to return before the next iteration of the exterior loop.
			// This shouldn't be prohibitively slow considering there will only be a handfull of planes, expecting
			// a maximum of around 6.
			mapper->RemoveAllClippingPlanes();
			for (itPlanes = planes.begin(); itPlanes != planes.end(); itPlanes++) {
				mapper->AddClippingPlane(*itPlanes);
			}

			mapper->Update();

			return true;
		}
	}

	// Could not find the plane, the user should know
	std::cout << "REMOVE FAILED" << std::endl;
	
	return false;
}

bool ClippingPlaneMaker::RemoveLastClippingPlane(MapperType *mapper) {
	cout << planeWidgets.empty() << " -> " << planeWidgets.size() << endl;
	bool ret = false;
	if (!planeWidgets.empty()) {
		cout << planeWidgets.empty() << " -> " << planeWidgets.size() << " " << planeWidgets.back() << endl;
		ret = RemoveClippingPlane(planeWidgets.back(), mapper);
	}

	return ret;
}

ClippingPlaneMaker::ClippingPlaneMaker() {
	//
}
