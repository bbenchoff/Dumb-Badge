import cv2
import numpy as np
import argparse


def post_process_chip(chip, thresh=128):
    # threshold and invert
    garbage,ret_val = cv2.threshold(chip,thresh,255,cv2.THRESH_BINARY_INV)
    return ret_val

def chip_to_packed_char(chip):
    bits = 8
    chip = chip / 255
    flat = chip.flatten("C")
    sz = int(flat.size / bits)
    int_series = []
    for idx in range(0,sz):
        start = idx*bits
        stop = (idx*bits)+bits
        b = flat[start:stop]
        print(b)
        bstr = ""
        for ab in b:
            bstr += str(int(ab))
        print(bstr)
        val = int(bstr,2)
        int_series.append(val)
    print(int_series)
    print([hex(h) for h in int_series])
    return int_series


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
            #cv2.imwrite("./temp/{0}.png".format(hex(idx)),temp)
            retVal[idx] = post_process_chip(temp)
            idx += 1

            if idx == 98:
                t = post_process_chip(temp)
                print(t)
                print(chip_to_packed_char(t))


    return retVal



#    print(retVal[33])


parser = argparse.ArgumentParser()
parser.add_argument("input", type=str, help="Input File")
parser.add_argument("ouput", type=str, help="Output File")
args = parser.parse_args()
split_source_image(args.input)
