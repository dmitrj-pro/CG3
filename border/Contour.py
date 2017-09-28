from PIL import Image, ImageDraw
from scipy.ndimage import convolve
import numpy as np
import math


def to_gray(rgb):
    return rgb[2] * 0.3 + rgb[1] * 0.59 + rgb[0] * 0.11


class Contour:

    def __init__(self, img):
        self.__name = img.split("/")[-1] if "/" in img else img.split("\\")[-1]
        self.__img = Image.open(img)
        self.__width = self.__img.size[0]
        self.__height = self.__img.size[1]
        self.__draw = ImageDraw.Draw(self.__img)
        self.__pixels = self.__img.load()


    def contour_convolution(self, to="./", name=None):
        if name is None:
            name = ".".join(self.__name.split(".")[:-1]) + "_contour_convolution" + ".jpg"
        data = np.asarray(self.__img).sum(axis=2) / 3
        kernel = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]])
        res = convolve(data, kernel)
        res = res.T
        img = Image.new("RGB", (self.__width, self.__height))
        draw = ImageDraw.Draw(img)
        for i in range(self.__width - 1):
            for j in range(self.__height - 1):
                r = 0 if res[i, j] == 0 else 255
                g = 0 if res[i, j] == 0 else 255
                b = 0 if res[i, j] == 0 else 255
                draw.point((i, j), (r, g, b))
        img.save(to + name, "JPEG")


    def contour_gradient(self, to="./", name=None, threshold=20):
        if name is None:
            name = ".".join(self.__name.split(".")[:-1]) + "_contour_gradient" + ".jpg"
        gradient = [[0 for i in range(self.__height)] for j in range(self.__width)]
        for i in range(1, self.__width - 1):
            for j in range(1, self.__height - 1):
                gradh = to_gray(self.__pixels[i, j]) - to_gray(self.__pixels[i + 1, j])
                gradv = to_gray(self.__pixels[i, j]) - to_gray(self.__pixels[i, j + 1])
                gradient[i][j] = math.sqrt(gradh ** 2 + gradv ** 2)
        for i in range(self.__width):
            for j in range(self.__height):
                if (gradient[i][j] > threshold):
                    r,g,b = 255, 255, 255
                else:
                    r,g,b = 0, 0, 0

                self.__draw.point((i, j), (r, g, b))
        self.__img.save(to + name, "JPEG")