from PIL import Image
import numpy as np
import math
from tqdm import tqdm


def single_thresholding(image):
    pixel_data = list(Image.Image.getdata(image))
    new_pixel_data = []
    for pixel in pixel_data:
        avg = (pixel[0] + pixel[1] + pixel[2]) / 3
        if avg > 150:
            new_pixel_data.extend((255, 255, 255))
        else:
            new_pixel_data.extend((0, 0, 0))
    new_pixel_data = bytes(new_pixel_data)
    image = Image.frombytes('RGB', image.size, new_pixel_data)
    return image


def double_thresholding(image):
    pixel_data = list(Image.Image.getdata(image))
    new_pixel_data = []
    for pixel in pixel_data:
        avg = (pixel[0] + pixel[1] + pixel[2]) / 3
        if 200 > avg > 100:
            new_pixel_data.extend((255, 255, 255))
        else:
            new_pixel_data.extend((0, 0, 0))
    new_pixel_data = bytes(new_pixel_data)
    image = Image.frombytes('RGB', image.size, new_pixel_data)
    return image


def gray_scale(image):
    pixel_data = list(Image.Image.getdata(image))
    new_pixel_data = []
    for pixel in pixel_data:
        avg = int((pixel[0] + pixel[1] + pixel[2]) / 3)
        new_pixel_data.extend((avg, avg, avg))
    new_pixel_data = bytes(new_pixel_data)
    image = Image.frombytes('RGB', image.size, new_pixel_data)
    return image


def histogram_equalization(image):
    pixel_data = list(Image.Image.getdata(image))
    histogram = [0] * 256
    
    for pixel in pixel_data:
        histogram[pixel[0]] += 1

    for i in range(256):
        histogram[i] /= image.size[0] * image.size[1]

    sum = 0
    for i in range(256):
        sum += histogram[i]
        histogram[i] = sum

    for i in range(256):
        histogram[i] = math.floor(histogram[i] * 255)

    new_pixel_data = []

    for pixel in pixel_data:
        new_pixel = histogram[pixel[0]]
        new_pixel_data.extend((new_pixel, new_pixel, new_pixel))

    new_pixel_data = bytes(new_pixel_data)
    image = Image.frombytes('RGB', image.size, new_pixel_data)

    return image


def naive_filter(image, mask_size):
    pixel_data = np.array(image)
    new_pixel_data = pixel_data.copy()
    for j in tqdm(range(mask_size // 2, image.size[0] - mask_size // 2)):
        for i in range(mask_size // 2, image.size[1] - mask_size // 2):
            sum = np.sum(pixel_data[i - mask_size // 2: i + mask_size // 2 + 1, 
                                    j - mask_size // 2: j + mask_size // 2 + 1, 0])
            avg = sum / (mask_size**2)
            new_pixel_data[i, j] = avg
    image = Image.fromarray(new_pixel_data)
    return image


def table_filter(image, mask_size):
    pixel_data = np.array(image)
    new_pixel_data = pixel_data.copy()
    table = pixel_data.copy()
    table = (table.cumsum(axis=0).cumsum(axis=1))
    for j in tqdm(range(mask_size // 2, image.size[0] - mask_size // 2)):
        for i in range(mask_size // 2, image.size[1] - mask_size // 2):
            p1 = int(table[i - mask_size // 2, j - mask_size // 2, 0])
            p2 = int(table[i + mask_size // 2, j - mask_size // 2, 0])
            p3 = int(table[i + mask_size // 2, j + mask_size // 2, 0])
            p4 = int(table[i - mask_size // 2, j + mask_size // 2, 0])
            new_pixel_data[i, j] = (p3 - p4 - p2 + p1) / (mask_size**2)
    image = Image.fromarray(new_pixel_data)
    return image


def main():
    # Task 1 and 2
    yoda_image = Image.open("yoda.jpeg")
    bw1_image = single_thresholding(yoda_image)
    bw1_image.save("bw1_yoda.jpeg")
    bw2_image = double_thresholding(yoda_image)
    bw2_image.save("bw2_yoda.jpeg")

    # Task 3
    gray_yoda = gray_scale(yoda_image)
    gray_yoda.save("gray_yoda.jpeg")
    c_yoda = histogram_equalization(gray_yoda)
    c_yoda.save("contrast_yoda.jpeg")

    # Task 4
    road_image = Image.open("road.jpg")
    gray_road = gray_scale(road_image)
    gray_road.save("gray_road.jpg")
    n_road = naive_filter(gray_road, 71)
    n_road.save("n_road.jpg")
    t_road = table_filter(gray_road, 71)
    t_road.save("t_road.jpg")

if __name__ == "__main__":
    main()
