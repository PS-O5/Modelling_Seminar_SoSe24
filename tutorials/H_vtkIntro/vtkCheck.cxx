#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>

int main() {
    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);

    // Create a writer
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("sphere.vtp");
    writer->SetInputConnection(sphereSource->GetOutputPort());

    // Write the file
    writer->Write();

    std::cout << "VTK sphere file written successfully." << std::endl;

    return 0;
}
