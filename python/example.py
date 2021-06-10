import numpy
import cv2

import timeit

image = cv2.imread("image.jpg", cv2.IMREAD_COLOR)

begin_time = timeit.default_timer()
for y in range(image.shape[0]):
    for x in range(image.shape[1]):
        image[y, x, 0] = 255 - image[y, x, 0]
        image[y, x, 1] = 255 - image[y, x, 1]
        image[y, x, 2] = 255 - image[y, x, 2]

end_time = timeit.default_timer()
print(f"elapsed time: {end_time - begin_time} 秒")

cv2.imshow("image", image)
cv2.waitKey(0)
