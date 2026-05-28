# Seam-Carving

Introduction

Seam carving is a content-aware image resizing technique that reduces the size of an image by removing seams of pixels with the lowest energy. This technique helps preserve the most important features of the image while resizing.
Features

<h2><strong>Features</strong></h2>

    Energy Calculation: Computes the energy of each pixel in the image, enabling effective seam identification.
    Seam Identification: Identifies the seam (path of pixels) with the lowest energy to minimize distortion.
    Seam Removal: Removes the identified seam from the image to achieve the desired dimensions.
    Resizing: Continuously removes seams until the image reaches the specified size.
    User Input: Allows users to specify the desired width or height for resizing.
    Multiple Energy Functions: Supports different methods for calculating energy, such as gradient magnitude and color histograms.

<h2><strong>Demonstration</strong></h2>

Before and after images showcasing the seam carving effect.

The input image is on the left and the result of the algorithm is on the right.

<img src="https://github.com/user-attachments/assets/a5fd7851-9a96-49bb-a0a9-60b8972aff66" alt="Description of image" height="400"/>

<img src="https://github.com/user-attachments/assets/c4277ee1-de84-40f8-8e04-36216566b1d8" alt="Resized Image" height="300"/>

<img src="https://github.com/user-attachments/assets/1420848c-34c3-48de-a5de-2cad5600bb8d" alt="Image 1" width="400"/>

<img src="https://github.com/user-attachments/assets/becca250-4f0c-4b67-be7d-e3f1f1896741" alt="Image 2" width="300"/>



---

## Build Instructions

### Requirements
- C++17 or higher
- OpenCV
- CMake

### Build Steps

```bash
git clone https://github.com/Archit-10/content-aware-image-resizing.git
cd content-aware-image-resizing

mkdir build
cd build

cmake ..
make
```

## Run the Program

```bash
./seam_carver

You will be prompted to enter target dimensions:

width height

Example input:

400 300

Output is saved to:

assets/output/resized.png
```

<h2><strong>Performance Metrics</strong></h2>

    Time Complexity: O(NM) for finding the optimal seam, where N is the height and M is the width of the image.
    Memory Usage: Memory usage is proportional to the size of the image, as additional space is required for energy and cost matrices.

## Challenges Faced

Handling complex textures and preserving important edges during seam detection.


## Improvement

Used gradient-based energy to better preserve key visual structures like edges and objects.

## QA 

- Verified energy computation on sample images
- Tested seam removal across multiple resizing iterations
- Visually inspected output quality after resizing

## Tech Stack

    Programming Language: C++
    Libraries: OpenCV

<h2><strong>Contributions</strong></h2>

Contributions are welcome! If you would like to contribute to this project, please follow these guidelines:

    Fork the repository.
    Create a new branch for your feature or bug fix.
    Submit a PR detailing your changes.    



