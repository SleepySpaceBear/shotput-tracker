import tensorflow as tf
import cv2
import matplotlib.pyplot as plt
import cvlib as cv
from cvlib.object_detection import draw_bbox
import numpy as np

loop_count = 0

# lots of tutorial code in here from sites listed on the discord


from keras.layers import Dense, Dropout, Activation, Flatten
from keras.layers import Convolution2D, MaxPooling2D
from keras.utils import np_utils
from numpy import loadtxt
from keras.models import Sequential
from keras.layers import Dense
from keras.datasets import mnist

def ok():
    print('')
    print('')
    print('')
    print('')
    print('ok')

(X_train, y_train), (X_test, y_test) = mnist.load_data()
#plt.imshow(X_train[0])

#ok()
#print(X_train.shape)

X_train = X_train.reshape(X_train.shape[0], 1, 17, 17)
X_test = X_test.reshape(X_test.shape[0], 1, 17, 17)
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
#ok()
#print(X_train.shape)

X_train /= 255
X_test /= 255

Y_train = np_utils.to_categorical(y_train, 5)
Y_test = np_utils.to_categorical(y_test, 5)
#ok()
#print(Y_train.shape)

#cv2.waitKey(1)
# (60000, 28, 28)




np.random.seed(0)




cap = cv2.VideoCapture('assets/vid.mp4')

while (cap.isOpened()):

    # Capture frame-by-frame
    ret, frame = cap.read()
    if ret == True:

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        gray = cv2.medianBlur(gray, 5)

        rows = gray.shape[0]
        circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, rows / 8,
                                  param1=100, param2=30,
                                  minRadius=15, maxRadius=25)

        if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                center = (i[0], i[1])
                # circle center
                cv2.circle(frame, center, 1, (0, 100, 100), 3)
                # circle outline
                radius = i[2]
                cv2.circle(frame, center, radius, (255, 0, 255), 3)

        cv2.imshow("detected circles", frame)



        # Display the resulting frame
        #cv2.imshow('Frame', frame)

        cv2.imwrite('assets/hey.jpg', frame)
        im = cv2.imread('assets/hey.jpg')

        img_rgb = cv2.imread('assets/hey.jpg')
        #img_rgb = cv2.imread(frame)
        img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)

        template = cv2.imread('assets/ball.png', 0)
        w, h = template.shape[::-1]
        res = cv2.matchTemplate(img_gray, template, cv2.TM_CCORR_NORMED)
        threshold = 0.8
        loc = np.where(res >= threshold)


        cv2.imshow('Detected', img_rgb)









        img = frame
        #bbox, label, conf = cv.detect_common_objects(img, confidence=0.01, model='yolov3-tiny')
        bbox, label, conf = cv.detect_common_objects(img, confidence=0.01)
        output_image = draw_bbox(img, bbox, label, conf)
        #print(bbox, label, conf)

        cv2.imshow('Detected', output_image)


        # Press Q on keyboard to  exit
        if cv2.waitKey(1) & 0xFF == ord('q'):
            print('Quitting...')
            break

    # Break the loop
    else:
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
        loop_count += 1
        print(loop_count)
        #break

print('Done!')
