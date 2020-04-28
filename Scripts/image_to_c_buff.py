import cv2
import numpy as np
import argparse


def split_source_image(infile, block_size=[20,10]):
    img = cv2.imread(infile)
    sz = img.shape
    w = sz[0]
    h = sz[1]
    idx = 0
    retVal = {}
    for hsz in range(0,int(w/block_size[1])):
        for vsz in range(0,int(h/block_size[0])):
            x_start = hsz*block_size[1]
            x_stop = (hsz*block_size[1])+block_size[1]
            y_start = vsz*block_size[0]
            y_stop = (vsz*block_size[0])+block_size[0]
            temp = img[y_start:y_stop,x_start:x_stop,0]
            cv2.imwrite("./temp/{0}.png".format(hex(idx)),temp)
            retVal[idx] = temp
            idx += 1
            print(hex(idx))


#    print(retVal[33])


parser = argparse.ArgumentParser()
parser.add_argument("input", type=str, help="Input File")
parser.add_argument("ouput", type=str, help="Output File")
args = parser.parse_args()
split_source_image(args.input)
