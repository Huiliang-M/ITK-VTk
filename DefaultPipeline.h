
// Establishes a pipeline to render CT images (from the algorithm given as input) by using
// opacity and gradient opacity transfer functions to render the scans in 3D while
// Emphasizing the skeletal structure.

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vector>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlaneWidget.h>
#include <vtkTrivialProducer.h>
#include "3Dtest.h"
#include <itkImageSource.h>

class DefaultPipeline {
public:
    DefaultPipeline(itk::ImageSource<ImageType> *input);
    ~DefaultPipeline();
    void addToRenderer(vtkRenderer *ren, vtkRenderWindowInteractor *iren);
    void removeFromRenderer(vtkRenderer *ren, vtkRenderWindowInteractor *iren);

private:
    ConnectorType::Pointer connector;
    vtkTrivialProducer *connectorPort;
    vtkVolume *volume;
    MapperType *mapper;
    ThresholdFilterType::Pointer thresholdFilter;
    vtkVolumeProperty *prop;

    // Transfer functions
    vtkColorTransferFunction *colorFun;
    vtkPiecewiseFunction *opacityFun;
    vtkPiecewiseFunction *gradientFun;
};
