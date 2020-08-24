import cv2
import numpy as np
import argparse


def post_process_chip(chip, thresh=128):
    # threshold and invert
    garbage,ret_val = cv2.threshold(chip,thresh,255,cv2.THRESH_BINARY_INV)
    return ret_val

def chip_to_int_series(chip,style="col_major"):
    """
    Take a character chip and pack it into a series
    of ints. Default is col major, approach.
    """
    bits = 8
    chip = np.fliplr(chip)
    #chip = np.flipud(chip)
    #cv2.imwrite("Chip.png",chip)
    chip = chip / 255
    if style == "col_major":
        # flatten the chip col major
        flat = chip.flatten("F")
    else:
        # flatten the chip row major
        flat = chip.flatten("C")

    sz = int(flat.size / bits)
    int_series = []
    for idx in range(0,sz):
        start = idx*bits
        stop = (idx*bits)+bits
        b = flat[start:stop]
        bstr = ""
        for ab in b:
            bstr += str(int(ab))
        val = int(bstr,2)
        int_series.append(val)
    return int_series


def split_source_image(infile, block_size=[20,10]):
    img = cv2.imread(infile)
    sz = img.shape
    w = sz[0]
    h = sz[1]
    idx = 0
    retVal = {}
    # top to bottom, left to right through the source image.
    hc = int(w/block_size[0])-1
    vc = int(h/block_size[1])-1
    for hsz in range(0,hc):
        for vsz in range(0,vc):
            x_start = hsz*block_size[1]
            x_stop = (hsz*block_size[1])+block_size[1]
            y_start = vsz*block_size[0]
            y_stop = (vsz*block_size[0])+block_size[0]
            temp = img[y_start:y_stop,x_start:x_stop,0]
            #cv2.imwrite("./temp/{0}.png".format(hex(idx)),temp)
            retVal[idx] = chip_to_int_series(post_process_chip(temp))
            if idx == 255:
                t = post_process_chip(temp)
                print(t)
                print(chip_to_int_series(t))
            idx += 1

    return retVal


def int_series_to_c_string(int_series,variable_name):
    """
    Make a series of ints into a C style hex array
    """
    return_value =  "{0}[25] = {{ \n\t"
    return_value = return_value.format(variable_name)
    count = 0;
    for v in int_series[0:-1]:
        return_value += "0x{:02x}, ".format(v)
        count += 1
        # Break into chunks
        if (count % 5) == 0 :
            return_value += "\n\t"


    return_value += "0x{:02x}}},\n\n".format(int_series[-1])
    #print(return_value)
    return return_value

def chip_map_to_c_file(chip_map,fname):
    f = open(fname, "w")
    for k,v in chip_map.items():
        name = "[0x{:02x}]".format(k)
        c_def = int_series_to_c_string(v,name)
        f.write(c_def)
    return


parser = argparse.ArgumentParser()
parser.add_argument("input", type=str, help="Input File")
parser.add_argument("output", type=str, help="Output File")
args = parser.parse_args()


# convert the chips into a packed series of ints
chip_map = split_source_image(args.input)
# print the ints
chip_map_to_c_file(chip_map,args.output)
print("Wrote font file to {0}".format(args.output))
