# IMPLEMENTATION CIFAR-10 WITH STM32F429 (STM32CubeAI)

The CIFAR-10 dataset (Canadian Institute For Advanced Research) is a collection of images that are commonly used to train machine learning and computer vision algorithms. It is one of the most widely used datasets for machine learning research.[1][2] The CIFAR-10 dataset contains 60,000 32x32 color images in 10 different classes.[3] The 10 different classes represent airplanes, cars, birds, cats, deer, dogs, frogs, horses, ships, and trucks. There are 6,000 images of each class.[4]

Computer algorithms for recognizing objects in photos often learn by example. CIFAR-10 is a set of images that can be used to teach a computer how to recognize objects. Since the images in CIFAR-10 are low-resolution (32x32), this dataset can allow researchers to quickly try different algorithms to see what works. Various kinds of convolutional neural networks tend to be the best at recognizing the images in CIFAR-10. (From Wikipedia)

And this project is the implementation the CIFAR-10 in STM32 Microcontroller. The CIFAR-10 is in Keras dataset and use STM32Cube.AI. The program will recognize the object from jpeg file (256x256 in size) that saved in USB flash disk and in a folder "media".
The program will open the folder "media" then read the jpeg files, decode it and resize to 128x128 and display to LCD using libjpeg library. The image also will resize to 32x32 for the input of AI network. Before send to AI network, it will convert to float type.

The AI output, in 32 bit float, then will sort the highest value and will display to LCD if the value >10%. This value is the prediction of the object.

As a result, the program can detect/recognize the object from the image with confidence value >50%.

Demo video
https://youtu.be/WcCLhHORZiY

Article (In Indonesian)
https://karedox.com/?p=271

