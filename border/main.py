from Contour import Contour

def test():
    img = Contour("1.jpg")
    img.contour_convolution()
    img.contour_gradient()
    img = Contour("2.jpg")
    img.contour_convolution()
    img.contour_gradient()
    img = Contour("3.jpg")
    img.contour_convolution()
    img.contour_gradient()
    img = Contour("4.jpg")
    img.contour_convolution()
    img.contour_gradient()

if __name__ == "__main__":
    test()


