# Geospatial Raster Images - The GDAL Library

An image in a computer is typically either a vector-based drawing (e.g., consisting of geometric features like
points, polygons, polytopes, meshes, triangles) or a raster-based space representation.

Simply speaking, a raster is an image representation in which the image domain is cut into small equal-sized rectangular areas called the pixels and attributes are assigned to these pixels based on either representing some average (e.g., color is typically some average over the area of the pixel) or center point information.
In a computational representation, raster images are therefore 2D matrices. The shape is based on the number of
pixels in the subdivision and the total area covered by the image.

We have already seen RGB images as (N,M,3)-dimensional tensors, where the last tensor axis is for holding red, green, and blue. In spatial images, we will have the same tensor shape, but the three channels can be replaced with multiple or even many measurement channels.

Furthermore, the spatial nature of geospatial images is managed through additional attributes that fixes the relation between pixel coordinates (e.g., integer indices for M and N) and world coordinates in a given CRS. Hence, for a spatial image, we are given

- a projection (CRS)
- a basepoint and two axes in terms of the CRS (that will correspond to the X and Y axis of the tensors)
- a set of C tensors called image channels

More concretely, the basepoint and two axes are commonly given by
- giving the CRS coordinates of the pixel location (0,0) and
- giving increments in terms of the CRS in both axes for going one step to the right in the image

This data structure is called geotransform and embedded in many spatial image file formats.

Experienced spatial data scientists will immediately realize that the orthogonality of the pixel coordinate with the
possible non-orthogonality of the given CRS will lead to a linear increase in error along the axes such that
coordinate reference systems (CRS) are better to be chosen to be locally orthogonal like the UTM family of projections.

Enough theory, let us start exploring such imagery with Python:

We provide
- A Dockerfile to install GDAL in a data science environment to run Docker containers
- Spatial Images
  - an easy RGB cloudfree composite of Germany (10 GB) [Download](https://api.bgd.ed.tum.de/germany.tiff)
  - an 11-bands wildfire image in the U.S. (830 MB) [Download](https://api.bgd.ed.tum.de/martin_s2a_focus.tif)
  
# Learning Steps:
Try to follow up with the following task we demonstrate in the lecture:

- Explore data by installing QGIS and looking closely at the data.
- Load images, find coordinates, plot small fractions.
- Implement contrast adjustments to create well-readable images
- Implement domain-specific RGB composites (false-color images), therefore, read [Simple Sentinel 2 Composites](https://custom-scripts.sentinel-hub.com/custom-scripts/sentinel-2/composites/) 
- Find the fire (look at where the fire band is non-zero) and plot the surroundings
- Create random patches (fire or no fire) for deep learning, each patch should be 64 by 64 and written as a PNG
- Download Sentinel Products (e.g., L1A products); run sen2cor, understand the Scene Classification SCL
- Build a cloudfree composite of summer images in Europe
- Learn how to download from AWS usnig aws-cli (other tools are too slow in my experience)


# Reference Information beyond the scope of this lecture
## Installation

The installation for Windows and Mac users should be not too difficult with Anaconda (conda). For Linux,
install both gdal (system) and the python3 gdal package using pip similar to below Dockerfile

## Docker File

```
FROM jupyter/datascience-notebook
USER root 

RUN apt-get update && apt-get -y --no-install-recommends install python3-dev software-properties-common
RUN add-apt-repository ppa:ubuntugis/ubuntugis-unstable

RUN apt-get update && apt-get -y install gdal-bin libgdal-dev

RUN pip3 install gdal
```

## Container Run
The container has been built, pushed to Dockerhub and run as
```
 docker run  -p 8888:8888 mwernerds/spatialjupyter
```
You can install Docker to your system and just run this container if you have a Linux-enabled environment (including
Windows 11 Professional / Education, but typically not Windows Home).

For Windows Home, you can install a Virtual Machine. I propose
- VirtualBox for Virtualization (runs on Mac, Windows, and Linux)
- Ubuntu (beginners), Debian (more advanced)

