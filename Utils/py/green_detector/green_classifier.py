#!/usr/bin/python

import sys
import matplotlib.pyplot as plt
import matplotlib.lines as lines

import numpy as np
from PIL import Image
import cv2

from scipy import signal

# calculate th difference between angles a and b
def angle_diff(a,b):
    #return np.arctan2((np.sin(a)+np.sin(-b)), (np.cos(a)+np.cos(-b)))*2
    return np.arctan2((np.sin(a-b)), (np.cos(a-b)))

# simple color classification
class ColorClassifier:
    def __init__(self, bW, bB, bO, cC, cW):
        self.brightnessConeRadiusWhite = bW #70
        self.brightnessConeRadiusBlack = bB #15
        self.brightnessConeOffset = bO #20
        self.colorAngleCenter = cC #-1.25 # yellow
        self.colorAngleWith = cW #0.1

    # return true if the (y,u,v) have a low color part, i.e., white, gray, black
    def no_color(self, y, u, v):
        brightness_alpha = (self.brightnessConeRadiusWhite - self.brightnessConeRadiusBlack) / (255.0 - self.brightnessConeOffset)
        chroma_threshold = np.clip(self.brightnessConeRadiusBlack + brightness_alpha * (y - self.brightnessConeOffset), self.brightnessConeRadiusBlack, 255)
        chroma = np.hypot(u-128, v-128)
        return np.less(chroma, chroma_threshold)

    def is_chroma(self, y, u, v):
        color_angle = np.arctan2(v-128, u-128)
        diff = angle_diff(color_angle, self.colorAngleCenter)
        return np.abs(diff) < self.colorAngleWith

    def is_color(self, y, u, v):
        return np.logical_and(np.logical_not(self.no_color(y, u, v)), self.is_chroma(y, u, v))

# load png image and convert it into yuv
# returns image and each yuv-channel in a tuple
def loadImage(path):
    img = Image.open(path)
    ycbcr = img.convert('YCbCr')

    width = ycbcr.size[0]
    height = ycbcr.size[1]
    size = (height, width)
    print ("Image size: {}".format(size))

    # separate chanels
    img_y = np.array(list(ycbcr.getdata(band=0)))
    img_u = np.array(list(ycbcr.getdata(band=1)))
    img_v = np.array(list(ycbcr.getdata(band=2)))

    img_y = np.reshape(img_y, size)
    img_u = np.reshape(img_u, size)
    img_v = np.reshape(img_v, size)

    return (img, img_y, img_u, img_v)

def myhist(x, y, bins):
    hh = np.zeros((256/bins,256/bins))
    for i in range(0,x.shape[0]):
        for j in range(0,y.shape[1]):
            hh[x[i,j]/bins, y[i,j]/bins] += 1
    return hh

def main():
    # get ile name
    if len(sys.argv) < 2:
        print("usage: green_detector.py <png file|log file> [bins=256]")
        sys.exit(1)
    input_file = sys.argv[1]
    num_bins = 256
    if len(sys.argv) > 2:
        num_bins = int(sys.argv[2])
    print("using '{}' and {} bins".format(input_file, num_bins))
    
    (img, img_y, img_u, img_v) = loadImage(input_file)

    # u-v histogram
    hist_uv, _, _ = np.histogram2d(
            np.reshape(img_v, (img_v.size,)), # x coodrdinates
            np.reshape(img_u,(img_u.size,)), # y coodrdinates
            bins = num_bins,
            range=((0,255),(0,255)))
    
    # get most common value
    t = np.max(hist_uv)
    #hist_uv[np.where(hist_uv >= t)] = 0
    
    print("hist_uv.shape: {}".format(hist_uv.shape))
    (u,v) = np.unravel_index(np.argmax(hist_uv, axis=None), hist_uv.shape)

    # display diagram where the most common value is placed
    idx = np.where(np.logical_and(img_u == v, img_v == u))
    
    nimg = np.zeros(img_u.shape)
    nimg[0,0] = 2 # enforce 1 = grey, 2 = white
    nimg[np.where(img_u == u)] = 1
    nimg[np.where(img_v == v)] += 1
    
    f, ((plt_orig, plt_no_chroma, plt_common_color),
            (plt_green_hist, plt_uv_hist, plt_green)) = plt.subplots(2, 3) # sharex='col', sharey='row'
    plt_orig.set_title('Original image')
    plt_orig.imshow(img)

    plt_no_chroma.set_title('Pixel with too less chroma')
    no_chroma = np.zeros(img_y.shape)
    no_chroma[np.where(np.isin(img_y, [range(256)]))] = 2
    plt_no_chroma.imshow(no_chroma, cmap=plt.cm.gray)
    
    plt_common_color.set_title('Pixel with the most common color')
    plt_common_color.imshow(nimg, cmap=plt.cm.gray)
    plt_common_color.imshow(img_v)

    # plot diagram only in the green sector
    plt_green_hist.set_title('uv diagram in green sector')
    green_hist = np.copy(hist_uv)[num_bins//2:, :num_bins//2]
    plt_green_hist.pcolor(green_hist)
    plt_green_hist.set_aspect('equal', adjustable='box')

    # angle-frequency diagram
    '''
    freq = [0 for _ in range(90)] #np.zeros((90,))
    for y in range(1, len(green_hist)):
        for x in range(len(green_hist[y])):
            freq[np.arctan(x/y)] += green_hist[y][-x-1]
    print(freq)
    '''

    # plot with uv-diagram and line for the green spectrum
    plt_uv_hist.set_title('uv histogram with lines')
    plt_uv_hist.pcolor(hist_uv)
    
    (cx, cy) = (num_bins/2, num_bins/2)
    a = np.radians(235)
    x = np.cos(a)*cx+cx
    y = np.sin(a)*cy+cy
    print np.degrees(np.arctan2(np.sin(a), np.cos(a)))
    
    plt_uv_hist.plot([cx,x], [cy,y])
    plt_uv_hist.set_aspect('equal', adjustable='box')
    
    plt_green.set_title('Green pixels')
    # classify the whole image
    classifierGreen = ColorClassifier(50, 3, 40, a, np.radians(20)) # green
    img_green = classifierGreen.is_color(img_y, img_u, img_v)
    plt_green.imshow(img_green)

    plt.show()
    
if __name__ == "__main__":
    main()
    #print np.degrees(angle_diff(np.radians(170), np.radians(230)))

