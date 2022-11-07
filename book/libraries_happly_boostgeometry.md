# happly and boost geometry - Load Point Clouds in C++11

The happly library is a nice header-only library for reading and writing PLY files.
The Boost Geometry library is an efficient OGC Simple Features comaptible spatial computing framework.

They can be bound together nicely as illustrated in the following snippet:

`````{tab-set}
````{tab-item} Source
```
/** \file Implementations related to Distance matrix

*/


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/algorithms/distance.hpp> 


#include<numeric>
#include <random>

#include<fstream>

#include "happly.h"
#include "tictoc.hpp"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


using point=bg::model::point<double, 3, bg::cs::cartesian>;
using pointcloud = bg::model::multi_point<point>;


  /** 
  *   @brief  Loads a PLY file and scales (aspect-correct into the unit cube).   
  *  
  *   @param  filename is the name of the file, at the moment PLY is supported
  *   @return the pointcloud
  */  

pointcloud get_scaled_pointcloud(std::string filename)
{
    happly::PLYData plyIn(filename);
    std::vector<double> x = plyIn.getElement("vertex").getProperty<double>("x");
    std::vector<double> y = plyIn.getElement("vertex").getProperty<double>("y");
    std::vector<double> z = plyIn.getElement("vertex").getProperty<double>("z");
    // translate to origin
    const auto minx = *std::min_element(x.begin(), x.end());
    for (auto &ix : x)
       ix  -= minx;
    const auto miny = *std::min_element(y.begin(), y.end());
    for (auto &iy : y)
       iy  -= miny;
    const auto minz = *std::min_element(z.begin(), z.end());
    for (auto &iz : z)
       iz  -= minz;
    // scale to unit cube
    auto scaler = std::max ({
		       *std::max_element(x.begin(),x.end()),
		       *std::max_element(y.begin(),y.end()),
		       *std::max_element(z.begin(),z.end()),
		       });
    pointcloud m;
    m.resize(x.size());
    		       
    for (size_t i=0; i < x.size(); i++)
    {
	m[i] = point{x[i] / scaler,y[i] / scaler,z[i] / scaler};
    }
    
    return m;
}

  /** 
  *   @brief  Instantiates an affine matrix for rotation around the X axis.   
  *  
  *   @param  angle in radians
  *   @return matrix_transformer (the matrix is accessible from .matrix())
  */  
bg::strategy::transform::matrix_transformer<double,3,3> xrot(double angle)
{
    return bg::strategy::transform::matrix_transformer<double, 3, 3> (
            1,0,0,0,
	    0,cos(angle), sin(angle), 0,
	    0,-sin(angle),  cos(angle), 0,
	    0,0,0,1); 
}


  /** 
  *   @brief  Instantiates an affine matrix for rotation around the Y axis.   
  *  
  *   @param  angle in radians
  *   @return matrix_transformer (the matrix is accessible from .matrix())
  */  
bg::strategy::transform::matrix_transformer<double,3,3> yrot(double angle)
{
    return bg::strategy::transform::matrix_transformer<double, 3, 3> (
            cos(angle),  0.0, -sin(angle), 0.0,
	    0,1,0,0,
            sin(angle),  0,cos(angle),   0.0,
	    0,0,0,1);
}

  /** 
  *   @brief  Instantiates an affine matrix for rotation around the Z axis.   
  *  
  *   @param  angle in radians
  *   @return matrix_transformer (the matrix is accessible from .matrix())
  */  

bg::strategy::transform::matrix_transformer<double,3,3> zrot(double angle)
{
    return bg::strategy::transform::matrix_transformer<double, 3, 3> (
            cos(angle), -sin(angle),  0.0, 0.0,
            sin(angle),  cos(angle),  0.0, 0.0,
            0.0,          0.0,        1.0,  0.0,
	    0,0,0,1); 
}

// let us apply a rotation
namespace trans = bg::strategy::transform;



  /** 
  *   @brief  Returns a rotated copy of the given point cloud given three angles for X, Y, Z
  *  
  *   @param in is the point cloud to be copied from
  *   @param  xAngle is the angle around the X-axis in radians
  *   @param  yAngle is the angle around the Y-axis in radians
  *   @param  xAngle is the angle around the Z-axis in radians
  *   @return the rotated point cloud
  */  

pointcloud rotated(const pointcloud &in, double xAngle,
double yAngle,double zAngle)
{
   bg::strategy::transform::matrix_transformer<double,3,3>
    tr (
	xrot(xAngle).matrix() *
	yrot(yAngle).matrix() *
	zrot(zAngle).matrix() 
	);	    
  pointcloud dst;
  boost::geometry::transform(in, dst, tr);
  return dst;
}



  /** 
  *   @brief  Stores a point cloud into a binary PLY file.   
  *  
  *
  *   More concretely, it takes the given point cloud, creates vectors (memcopy, inefficient, 
  *   but at the moment okay) and for each of those vectors creates an element "vertex"
  *   with attributes X, Y, and Z holding double values as typical. 
  *
  *   @param  filename is the name of the file
  *   @param  pcl is the point cloud 
  *   @return void
  */  

void writePly(std::string filename, const pointcloud &pcl)
{
    std::vector<double> x,y,z;
    x.reserve(pcl.size());
    y.reserve(pcl.size());
    z.reserve(pcl.size());
    for (const auto &p:pcl)
    {
	x.push_back(bg::get<0> (p));
	y.push_back(bg::get<1> (p));
	z.push_back(bg::get<2> (p));
    }
    
    happly::PLYData plyOut;
    plyOut.addElement("vertex", x.size());

    plyOut.getElement("vertex").addProperty<double>("x", x);
    plyOut.getElement("vertex").addProperty<double>("y", y);
    plyOut.getElement("vertex").addProperty<double>("z", z);

    plyOut.write(filename, happly::DataFormat::Binary); // or ASCII

}


template<typename benchmark_strategy=notictoc>
std::vector<double> distanceMatrix(const pointcloud &A,const pointcloud &B) 
{
    std::vector<double> dm (A.size() * B.size());
    { benchmark_strategy bench("DistanceMatrix for "+std::to_string(A.size()) + " and " + std::to_string(B.size()));
    for (size_t i=0; i<A.size(); i++)
    {
      dm[i*B.size()+i] = 0;
      for (size_t j=i+1; j<B.size(); j++)
        dm[j*B.size()+i]=dm[i*B.size()+j] = bg::distance(A[i],B[j]);
    }
    }
    return dm;
}

namespace strategy{
/// The strategy for taking the mean of the distance matrix
  class mean{};
};


  /** 
  *   @brief  Compute Distance with given strategy
  *  
 * @param A a point cloud
 * @param B a point cloud
  *   @return the distance
  */  
template<typename strategy>
double pcl_dist(const pointcloud &A, const pointcloud &B){
    throw std::runtime_error("Not specific enough. Give a distance");
    return 0;
}


   

/**
 * @brief Implement the distance using mean strategy
 *
 * @param A a point cloud
 * @param B a point cloud
 */
template<>
double pcl_dist<strategy::mean>(const pointcloud &A, const pointcloud &B)
{
    auto dm = distanceMatrix(A,B);
    double v = std::accumulate(dm.begin(),dm.end(),0);
    return v / dm.size();
}


```
````
````` 
