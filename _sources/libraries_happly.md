# Reading and Writing PLY files (point cloud example)

It has been complicated and annoying to support a sensible subset of 3D file formats.
But modern C++ comes to the rescue, see how easy the

happily reading PLY files (happly)

header-only library makes reading and working (in this case using Eigen3) with point clouds.

`````{tab-set}
````{tab-item} Source
```cpp
#include "happly.h"
#include<algorithm>

#include<Eigen/Core>
#include<Eigen/Dense>
using namespace Eigen;


auto get_scaled_pointcloud(std::string filename)
{
    happly::PLYData plyIn(filename);
    std::vector<double> x = plyIn.getElement("vertex").getProperty<double>("x");
    std::vector<double> y = plyIn.getElement("vertex").getProperty<double>("y");
    std::vector<double> z = plyIn.getElement("vertex").getProperty<double>("z");
    double scaler=1.0;
    Eigen::MatrixXf m(x.size(),3);
    		       
    for (size_t i=0; i < x.size(); i++)
    {
	m(i,0) = x[i] / scaler;
	m(i,1) = y[i] / scaler;
	m(i,2) = z[i] / scaler;
    }

    
    return m;
}


int main(int argc, char **argv)
{
    auto pointcloud = get_scaled_pointcloud(argv[1]);
    Matrix3f rot;
    rot = AngleAxisf(0.25*M_PI, Vector3f::UnitX())
      * AngleAxisf(0.5*M_PI,  Vector3f::UnitY())
      * AngleAxisf(0.33*M_PI, Vector3f::UnitZ());
    std::cout << rot << std::endl;

    auto rotated = (rot * pointcloud.transpose()).transpose();
    
    for (size_t i=0; i< 10; i++){    
       std::cout << "X:"<<(rot * pointcloud.row(i).transpose()).transpose()  << std::endl;
       std::cout << "Y:" << rotated.row(i) << std::endl;
    }

    std::vector<double> x,y,z;
    x.resize(rotated.rows());
    y.resize(rotated.rows());
    z.resize(rotated.rows());
    std::cout << "Warper" << std::endl;
    for (size_t i=0; i < rotated.rows(); i++)
    {
	x[i] = rotated(i,0);
	y[i] = rotated(i,1);
	z[i] = rotated(i,2);
    }
    happly::PLYData plyOut;

   plyOut.addElement("vertex", x.size());

   plyOut.getElement("vertex").addProperty<double>("x", x);
   plyOut.getElement("vertex").addProperty<double>("y", y);
   plyOut.getElement("vertex").addProperty<double>("z", z);

   plyOut.write("out.ply", happly::DataFormat::ASCII); // or Binary

   return 0;
}
```
````
````{tab-item} Makefile
```
all: 
	g++ -Wall -march=native -Ofast -o libs_pcl_happly libs_pcl_happly.cpp  `pkg-config --cflags --libs eigen3`
run: 
	./libs_pcl_happly ../data/sofa_0007.off.ply
```
````
````{tab-item} Build Output
```
```
````
````{tab-item} Run Output
```
```
````
````` 
