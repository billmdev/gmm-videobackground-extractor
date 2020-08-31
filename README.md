# gmm-videoforeground-extractor


Code and content for the research project work on the *Implementation of Video Foreground Detection based on GMM.*


**_Abstract_** ​:
This project implemented a foreground detection
algorithm GMM by using OpenCV. Firstly, a mixed Gaussians
model is used to simulate each background in each pixel of each
frame of the video. The number of mixed Gaussians of each
background can be adaptive. Then in the test phase, the new
coming pixel of new frame will be matched by using GMM. If the
pixel can match one of Gaussian, it is considered as the
background. Otherwise, it is detected as the foreground. Since
the GMM model is continuously updated and learned through
iterative process, it is robust to process dynamic backgrounds.
**_Keywords—_** ​ ​Mixed Gaussians model, GMM, Foreground detection.
