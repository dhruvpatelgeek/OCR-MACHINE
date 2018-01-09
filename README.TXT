CLICK ON THIS LINK TO SEE A PREVIEW (https://vimeo.com/250357652)
OR
CLICK ON THE .cpp FILE ABOVE TO VIEW THE SOURCE CODE
***********************************************************************************************************************************
INTRODUCTION
This is my first attempt at machine learning. The entire program is coded by me without the use of external libraries.
This program is a neural network that uses the MNIST database (http://yann.lecun.com/exdb/mnist/) to calibrate the software to 'read' digits from .jpeg type files.

WORKING
1)The .jpeg files are converted into .csv(comma seperated values) files, then saved as .txt.

2)The program then dynamically allocates structure arrays equal to the number of digits that are to be scanned.

3)The numeric value of each pixel is then 'scanned' to a 28 x 28 matrix .

4)The neural classes are invoked each having a particular 'brightness' and indices.

5)On the first layer there are 784 neurons that are directly initalized by the structure functions that contain the digits.

6)The first layer then invokes the second, and the second invokes the third, and so on.

7)The last layer (end layer) comprises of 10 neurons, which correspond to the digits 0-9.

8)The brightness of the neurons mentioned above would correspond to the probability of the digits.

9)The cost function is called to calibrate the weights of the connections so that the neural network is fit for training.

10)The test function uses these weights to identify the digits.

CLICK ON neural network ocr.cpp TO LOOK AT THE SOURCE CODE.
